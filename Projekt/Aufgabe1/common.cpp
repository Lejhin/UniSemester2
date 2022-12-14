//
// Created by juliu on 13.12.2022.
//

#include "common.h"



void encrypt(std::vector<char>& keyVector, std::vector<char>& message, std::vector<char>& outPut) {
    int i = 0;
    for (char character: message) {
        if (i >= keyVector.size()) {
            i = 0;
        }
        Key k1(keyVector.at(i));
        i++;
        char decrypted = k1.encrypt(character);
        outPut.push_back(decrypted);
    }
}



void decrypt(std::vector<char>& keyVector, std::vector<char>& message, std::vector<char>& outPut){
    int i = 0;
    for (char character: message) {
        if (i >= keyVector.size()) {
            i = 0;
        }
        Key k1(keyVector.at(i));
        i++;
        char decrypted = k1.decrypt(character);
        outPut.push_back(decrypted);
    }
}

void WriteToFile(std::vector<char>& input, std::fstream& file){

    for(char character:input){
        file << character;
    }
}

void print(std::vector<char>& message){
    for(char character:message){
        std::cout<< character;
    }
    std::cout << std::endl;
}