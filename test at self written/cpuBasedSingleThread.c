#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitcoin/bitcoin.hpp> // Assuming libbitcoin is installed

bool testPrivateKey(const bc::ec_secret& secret_key, const std::vector<bc::ec_point>& public_keys) {
    bc::ec_compressed compressed_public_key;
    bc::secret_to_public(compressed_public_key, secret_key);

    for (const auto& public_key : public_keys) {
        if (public_key == compressed_public_key) {
            return true; // Match found
        }
    }
    return false; // No match found
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

    // Test the generated private key against the set of public keys
    bool key_matches = testPrivateKey(private_key, wallet_public_keys);

    if (key_matches) {
        std::cout << "Generated private key matches one of the wallet public keys." << std::endl;
    } else {
        std::cout << "Generated private key does not match any of the wallet public keys." << std::endl;
    }

    return 0;
}