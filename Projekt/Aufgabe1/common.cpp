//
// Created by juliu on 13.12.2022.
//

#include "common.h"

void encrypt(int key, std::vector<char>& message, std::vector<char>& outPut){

    Key k1(key);
    for(char character: message){
        char encryptedChar = k1.encrypt(character);
        outPut.push_back(encryptedChar);
    }
}


void encrypt(std::vector<char>& keyVector, std::vector<char>& message, std::vector<char>& outPut) {
    int i = 0;
    for (char character: message) {
        if (i >= keyVector.size()) {
            i = 0;
        }

        Key k1(keyVector.at(i));
        std::cout << k1.getKey() << " ";
        i++;
        char decrypted = k1.encrypt(character);
        outPut.push_back(decrypted);
    }
}

void decrypt(int key, std::vector<char>& message, std::vector<char>& outPut){
    Key DecryptKey(key);
    for(char character: message){
        char decryptedChar = DecryptKey.decrypt(character);
        outPut.push_back(decryptedChar);
    }
}

void decrypt(std::vector<char>& keyVector, std::vector<char>& message, std::vector<char>& outPut){
    int i = 0;
    for (char character: message) {
        if (i >= keyVector.size()) {
            i = 0;
        }
        Key k1(keyVector.at(i));
        std::cout << i;
        i++;
        char decrypted = k1.decrypt(character);
        outPut.push_back(decrypted);
    }
}

void WriteToFile(std::vector<char>& input, std::fstream& file){
    file << "\n\n";
    for(char character:input){
        file << character;
    }


}