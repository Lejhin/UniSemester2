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
    char InputKey = 3;
    std::vector<char> message;
    std::vector<char> encryptedMessage;
    argsp_t programmArguments(argc, argv);
    std::ifstream Readfile;
    std::fstream AppendFile;
    Frequency F1;

    std::vector<char> secret = {'s','e', 'c','r', 'e','t'};
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

    AppendFile.open("Projekt/Aufgabe1/encrypt.txt", std::fstream::app);


    decrypt('j', message, encryptedMessage);

    //F1.calculateRelativeFrequency(message);
    //F1.printFrequency();


    WriteToFile(encryptedMessage, AppendFile);
    AppendFile.close();
}


