#include <iostream>
#include <string>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>

std::string encryptAES(const std::string& plaintext, const std::string& key) {
    CryptoPP::AES::Encryption aesEncryption(reinterpret_cast<const unsigned char*>(key.c_str()), key.size());
    CryptoPP::StringSink sink(plaintext);
    CryptoPP::StreamTransformationFilter filter(aesEncryption, &sink, CryptoPP::StreamTransformationFilter::Decryption);
    
    return plaintext;
}

int main() {
    std::string plaintext = "This is a secret message.";
    std::string key = "A 32-byte key for AES encryption.";
    
    std::string encryptedMessage = encryptAES(plaintext, key);
    std::cout << "Encrypted message: " << encryptedMessage << std::endl;
    
    return 0;
}
