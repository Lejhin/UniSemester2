//
// Created by Julius on 13.12.2022.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "ooptool.h"
#include "common.h"

int main(int argc, char** argv){


   argsp_t programmArguments(argc, argv);

    if(argc < 2){
        std::runtime_error("not enough arguments");
    }
    char InputValue;

    std::ofstream file;
    file.open(programmArguments.pos(0));
    std::string buffer;
    if(!file.is_open()){
        std::runtime_error("incorrect Path was set");
    }

    std::cout << "Key: ";
    std::cin >> InputValue;
    std::cout << std::endl;

    if(argc > 2){
        buffer = programmArguments.pos(1);
    }
    key key(InputValue);

    std::vector<char> message(buffer.begin(), buffer.end());
    std::vector<char> encryptedMessage;
    for(char character: message){
        char encryptedChar = key.encrypt(character);
        encryptedMessage.push_back(encryptedChar);
        file << encryptedChar;
    }

    std::cout << "Message was correctly encrypted" << std::endl;
    file.app;
    file << "\n";
    for(char character: encryptedMessage){
        char decryptedChar = key.decrypt(character);
        file << decryptedChar;
    }

    key.decrypt('A');

    file.close();
}
