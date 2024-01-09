#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitcoin/bitcoin.hpp> // Assuming libbitcoin is installed
#include <sqlite3.h>
#include <chrono>
#include <thread>
#include <atomic>

std::atomic<int> keysChecked(0); // Atomic variable to track keys checked

// Function to display the speed (keys per second checked) every 10 seconds
void displaySpeed() {
    while (true) {
        int keys = keysChecked.exchange(0); // Reset and get the current number of keys checked
        std::cout << "Keys per second checked: " << keys / 10 << std::endl; // Calculate and display keys per second
        std::this_thread::sleep_for(std::chrono::seconds(10)); // Wait for 10 seconds
    }
}

// Function to save last processed private key to a file
void saveLastProcessedPrivateKey(const bc::ec_secret& private_key) {
    std::ofstream progressFile("progress.txt");
    if (!progressFile.is_open()) {
        std::cerr << "Error opening progress file for writing!" << std::endl;
        return;
    }

    progressFile << bc::encode_base16(private_key); // Save the last processed private key in hexadecimal format
    progressFile.close();
}

// Function to load last processed private key from a file
bc::ec_secret loadLastProcessedPrivateKey() {
    std::ifstream progressFile("progress.txt");
    if (!progressFile.is_open()) {
        std::cerr << "Progress file not found. Starting from the beginning." << std::endl;
        return bc::null_hash;
    }

    std::string hex_private_key;
    progressFile >> hex_private_key; // Read the last processed private key in hexadecimal format
    progressFile.close();

    if (hex_private_key.empty()) {
        std::cerr << "No progress saved. Starting from the beginning." << std::endl;
        return bc::null_hash;
    }

    return bc::decode_hex(hex_private_key);
}

// Function to test private key against public keys
bool testPrivateKey(const bc::ec_secret& secret_key, const std::vector<bc::ec_point>& public_keys, std::ofstream& matchFile, sqlite3* db) {
    bc::ec_compressed compressed_public_key;
    bc::secret_to_public(compressed_public_key, secret_key);

    for (const auto& public_key : public_keys) {
        if (public_key == compressed_public_key) {
            // Match found, save to Match.txt
            bc::wallet::ec_private private_key(secret_key);
            std::string wif = private_key.encoded();

            matchFile << "WIF: " << wif << "\nPrivate Key: " << bc::encode_base16(secret_key) << "\n\n";

            return true;
        }
    }

    // No match found, save to SQLite database
    std::string private_key_hex = bc::encode_base16(secret_key);
    std::string insert_query = "INSERT INTO NonMatchingKeys (private_key) VALUES ('" + private_key_hex + "');";

    sqlite3_exec(db, insert_query.c_str(), nullptr, 0, nullptr);
    return false;
}

int main() {
    std::ifstream file("public_keys.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    std::vector<bc::ec_point> wallet_public_keys;
    std::string line;
    while (std::getline(file, line)) {
        bc::ec_point public_key;
        if (!bc::decode_base16(public_key, line)) {
            std::cerr << "Error decoding public key: " << line << std::endl;
            continue;
        }
        wallet_public_keys.push_back(public_key);
    }
    file.close();

    // Open Match.txt for writing matching keys
    std::ofstream matchFile("Match.txt", std::ios::app);
    if (!matchFile.is_open()) {
        std::cerr << "Error opening Match.txt for writing!" << std::endl;
        return 1;
    }

    // Open or create SQLite database and create a table
    sqlite3* db;
    int db_open_result = sqlite3_open("NonMatchingKeys.db", &db);
    if (db_open_result != SQLITE_OK) {
        std::cerr << "Error opening SQLite database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    const char* create_table_query = "CREATE TABLE IF NOT EXISTS NonMatchingKeys (private_key TEXT);";
    sqlite3_exec(db, create_table_query, nullptr, 0, nullptr);

    // Load the last processed private key
    bc::ec_secret last_processed_private_key = loadLastProcessedPrivateKey();

    // Generate a random private key and start testing from the last processed key
    bc::ec_secret private_key;
    if (last_processed_private_key != bc::null_hash) {
        private_key = last_processed_private_key;
    } else {
        bc::data_chunk seed(32, 0x00); // Replace with a secure random seed
        bc::pseudo_random_fill(seed);
        bc::secret_from_seed(private_key, seed);
    }

    // Create a thread to display speed every 10 seconds
    std::thread speedDisplayThread(displaySpeed);

    // Main loop for testing private keys against public keys
    bool found_match = false;
    while (!found_match) {
        found_match = testPrivateKey(private_key, wallet_public_keys, matchFile, db);
        private_key = bc::increment(private_key); // Increment to the next private key
        saveLastProcessedPrivateKey(private_key); // Save progress after each iteration
        keysChecked++; // Increment keys checked
    }

    // Close resources and join the speed display thread
    sqlite3_close(db);
    matchFile.close();
    speedDisplayThread.join();

    return 0;
}
