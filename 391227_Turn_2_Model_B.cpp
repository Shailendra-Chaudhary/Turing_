#include <iostream>
#include <string>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <cryptopp/modes.h>

std::string encryptAES(const std::string& plaintext, const std::string& key, const std::string& iv) {
    std::string ciphertext;
    
    try {
        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryption;
        encryption.SetKeyWithIV(reinterpret_cast<const unsigned char*>(key.c_str()), key.size(), 
                                reinterpret_cast<const unsigned char*>(iv.c_str()));
        
        CryptoPP::StringSource ss(plaintext, true, 
            new CryptoPP::StreamTransformationFilter(encryption,
                new CryptoPP::StringSink(ciphertext)
            )
        );
    } catch (const CryptoPP::Exception& e) {
        std::cerr << "Encryption error: " << e.what() << std::endl;
    }

    return ciphertext;
}

int main() {
    std::string plaintext = "This is a secret message.";
    std::string key = "0123456789abcdef0123456789abcdef"; // 32 bytes key
    std::string iv = "abcdef9876543210"; // 16 bytes IV
    
    std::string encryptedMessage = encryptAES(plaintext, key, iv);
    std::cout << "Encrypted message: " << encryptedMessage << std::endl;
    
    return 0;
}
