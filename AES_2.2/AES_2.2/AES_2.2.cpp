 

#include <iostream>
#include <iostream>
#include <string>
#include <openssl/aes.h>

 
std::string encryptAES(const std::string& text, const std::string& key) {
    AES_KEY aesKey;
    AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(key.c_str()), 128, &aesKey);

    std::string encryptedText;

     
    int padding = AES_BLOCK_SIZE - text.length() % AES_BLOCK_SIZE;
    std::string paddedText = text + std::string(padding, static_cast<char>(padding));

    for (size_t i = 0; i < paddedText.length(); i += AES_BLOCK_SIZE) {
        unsigned char encryptedBlock[AES_BLOCK_SIZE];
        AES_encrypt(reinterpret_cast<const unsigned char*>(paddedText.c_str() + i),
            encryptedBlock, &aesKey);
        encryptedText.append(reinterpret_cast<char*>(encryptedBlock), AES_BLOCK_SIZE);
    }

    return encryptedText;
}

 
std::string decryptAES(const std::string& encryptedText, const std::string& key) {
    AES_KEY aesKey;
    AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(key.c_str()), 128, &aesKey);

    std::string decryptedText;

    for (size_t i = 0; i < encryptedText.length(); i += AES_BLOCK_SIZE) {
        unsigned char decryptedBlock[AES_BLOCK_SIZE];
        AES_decrypt(reinterpret_cast<const unsigned char*>(encryptedText.c_str() + i),
            decryptedBlock, &aesKey);
        decryptedText.append(reinterpret_cast<char*>(decryptedBlock), AES_BLOCK_SIZE);
    }

    // Видаляємо додатковий padding
    decryptedText.erase(decryptedText.end() - decryptedText.back(), decryptedText.end());

    return decryptedText;
}

int main() {
    std::string text = "Це текст, який потрібно зашифрувати.";
    std::string key = "0123456789abcdef"; // Ключ повинен мати розмір 128 біт  

    std::string encryptedText = encryptAES(text, key);
    std::cout << "Зашифрований текст: " << encryptedText << std::endl;

    std::string decryptedText = decryptAES(encryptedText, key);
    std::cout << "Розшифрований текст: " << decryptedText << std::endl;

    return 0;
}
