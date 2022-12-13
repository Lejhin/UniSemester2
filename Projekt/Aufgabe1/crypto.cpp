//
// Created by Julius on 13.12.2022.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "ooptool.h"
#include "common.h"

int main(int argc, char** argv){

    //information extraction and encryption/decryption
    char ReadBuffer;
    char InputKey;
    std::vector<char> message;
    std::vector<char> encryptedMessage;
    argsp_t programmArguments(argc, argv);
    std::ifstream Readfile;
    std::fstream Appendfile;
    Frequency F1;

    //

    if(argc < 2){
        std::runtime_error("not enough arguments");
    }

    Readfile.open(programmArguments.pos(0));


    if(!Readfile.is_open()){
        std::runtime_error("incorrect Path was set");
    }


    //Extracting file information
    //doesn't skip the white spaces anymore
    Readfile >> std::noskipws;
    while(Readfile >> ReadBuffer){
        message.push_back(ReadBuffer);
    }
    Readfile.close();

    Appendfile.open("Projekt/Aufgabe1/encrypt.txt", std::fstream::app);
/*
    std::cout << "Key: ";
    std::cin >> InputKey;
    std::cout << std::endl;

    key key(InputKey);



    std::cout << message.size() << std::endl;
    //encrypting message
    for(char character: message){
        char encryptedChar = key.encrypt(character);
        encryptedMessage.push_back(encryptedChar);
        Appendfile << encryptedChar;

    }
    std::cout << "correctly encrypted" << std::endl;

    Appendfile << "\n";
    for(char character: encryptedMessage){
        char decryptedChar = key.decrypt(character);
        Appendfile << decryptedChar;
    }*/


    F1.calculateRelativeFrequency(message);
    F1.printFrequency();

    std::cout << "correctly decrypted" << std::endl;

    Appendfile.close();
}
