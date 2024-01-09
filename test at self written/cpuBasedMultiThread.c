#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitcoin/bitcoin.hpp> // Assuming libbitcoin is installed
#include <thread>
#include <mutex>

std::mutex mtx; // Mutex for protecting shared output

bool testPrivateKey(const bc::ec_secret& secret_key, const std::vector<bc::ec_point>& public_keys, bool& key_matches) {
    bc::ec_compressed compressed_public_key;
    bc::secret_to_public(compressed_public_key, secret_key);

    for (const auto& public_key : public_keys) {
        if (public_key == compressed_public_key) {
            key_matches = true; // Match found
            return true;
        }
    }
    return false; // No match found
}

void processKeys(const std::vector<bc::ec_point>& wallet_public_keys, const bc::ec_secret& private_key) {
    bool key_matches = false;
    testPrivateKey(private_key, wallet_public_keys, key_matches);

    std::lock_guard<std::mutex> lock(mtx); // Lock the output
    if (key_matches) {
        std::cout << "Generated private key matches one of the wallet public keys." << std::endl;
    } else {
        std::cout << "Generated private key does not match any of the wallet public keys." << std::endl;
    }
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

    // Generate a random private key
    bc::ec_secret private_key;
    bc::data_chunk seed(32, 0x00); // Replace with a secure random seed
    bc::pseudo_random_fill(seed);
    bc::secret_from_seed(private_key, seed);

    // Determine the number of threads based on hardware concurrency
    const int num_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    // Create threads to test the generated private key against the set of public keys
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(processKeys, std::ref(wallet_public_keys), std::ref(private_key));
    }

    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
