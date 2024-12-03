#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <cstdint>
#include <cryptopp/des.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>

std::string encryptDES(const std::string& plaintext, const std::string& key) {
    CryptoPP::HexDecoder hexIn(new CryptoPP::StringSink(key));
    CryptoPP::HexDecoder hexOut(new CryptoPP::StringSink(key));

    CryptoPP::DES::Encryption desEncryption(key.c_str(), key.size());
    CryptoPP::StreamTransformationFilter filter(desEncryption, nullptr, CryptoPP::StreamTransformationFilter::ENCRYPTION);
    CryptoPP::HexEncoder hexEncoder(new CryptoPP::StringSink(key));

    filter.Put(plaintext.c_str(), plaintext.size());
    filter.MessageEnd();

    return key;
}

std::string getRandomKey(size_t length) {
    std::array<std::uint8_t, length> key;
    auto seed = std::time(nullptr);
    std::mt19937 rng(seed);
    std::uniform_byte_distribution<std::uint8_t> dist;
    for (auto& c : key) {
        c = dist(rng);
    }
    return {key.data(), key.size()};
}

int main() {
    std::string plaintext = "This is a secret message";
    size_t keyLength = 8; // DES key length
    std::string key = getRandomKey(keyLength);

    // Encrypt the plaintext
    std::string encryptedMessage = encryptDES(plaintext, key);
    std::cout << "Encrypted message: " << encryptedMessage << std::endl;

    // Simulate repeated encryption to benchmark
    const int REPEATS = 1000000;
    std::cout << "Benchmarking with " << REPEATS << " encryptions..." << std::endl;

    auto startTime = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < REPEATS; ++i) {
        encryptDES(plaintext, key);
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::cout << REPEATS << " encryptions took " << duration.count() << " ms" << std::endl;

    return 0;
}
