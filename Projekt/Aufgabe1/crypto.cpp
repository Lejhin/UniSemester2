//
// Created by Julius on 13.12.2022.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "ooptool.h"
#include "common.h"


int main(int argc, char** argv){

    if(argc < 2){
        std::runtime_error("not enough arguments");
    }
    //information extraction and encryption/decryption
    char ReadBuffer;
    std::vector<char> message;
    std::vector<char> encryptedMessage;
    std::vector<std::string> refFreq;
    argsp_t programmArguments(argc, argv);

    std::ifstream Readfile;
    std::fstream AppendFile;
    std::ifstream RefFile;

    Frequency F1;
    std::string Input;
    //

    //Keyhandling
    if(programmArguments.has_option("key")){
        Input = programmArguments.option("key" );
    }else{
        Input = 'c';
    }


    std::vector<char> KeyVector(Input.begin(), Input.end());


    Readfile.open(programmArguments.pos(0));

    //Extracting file information
    //doesn't skip the white spaces anymore
    Readfile >> std::noskipws;
    while(Readfile >> ReadBuffer){
        message.push_back(ReadBuffer);
    }

    Readfile.close();

    AppendFile.open("Projekt/Aufgabe1/encrypt.txt", std::fstream::app);



    if(programmArguments.has_option("cfreq")){
        RefFile.open(programmArguments.option("cfreq"));
        std::vector<char> Buchstaben;
        std::vector<double> values;
        std::string localDouble;
        int i = 0;
        while(RefFile >> localDouble){
            if(i%2){
                values.push_back(std::stof(localDouble));
            }else{
                std::cout << localDouble;
                Buchstaben.push_back(localDouble[0]);
            }

            refFreq.push_back(localDouble);
        }



        KeyVector.clear();
        //KeyVector.push_back(breakCeaser(message,refFreq));


    }


    //Programmhandling
    if(programmArguments.flag("d")){
        decrypt(KeyVector,message, encryptedMessage);
    }else{
        encrypt(KeyVector, message, encryptedMessage);
    }

    if(programmArguments.flag("f")){
        F1.calculateRelativeFrequency(message);
        F1.printFrequency();
    }

    print(encryptedMessage);
    //WriteToFile(encryptedMessage, AppendFile);
    //AppendFile.close();
}


