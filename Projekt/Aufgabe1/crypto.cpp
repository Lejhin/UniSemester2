//
// Created by Julius on 13.12.2022.

//
#include <iostream>
#include <vector>
#include <algorithm>
#include "ooptool.h"
#include "common.h"


int main(int argc, char** argv){

    if(argc < 2){
        std::runtime_error("not enough arguments");
    }
    //information extraction and encryption/decryption
    std::string EnFreqLocation = "Projekt/Aufgabe1/en_freq.txt";
    char ReadBuffer;
    std::vector<char> message;
    std::vector<char> encryptedMessage;
    std::vector<double> refFreq;
    std::map<char, double> myMap;
    argsp_t programmArguments(argc, argv);
    std::string Input;
    Frequency F1;

    //filestream to Read the given files
    std::ifstream Readfile;
    std::ifstream RefFile;


    //

    //Keyhandling
    if(programmArguments.has_option("key")){
        Input = programmArguments.option("key" );
        for(int i = 0; i < Input.size(); ++i){
            if(Input[i] >= 65 && Input[i] <= 90){
                Input[i] += 32; //All keys are converted to lower case to prevent false user input
            }
        }
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


    //Programhandling

    //Task 5
    if(programmArguments.flag("c")){
        if(programmArguments.has_option("cfreq")){
            RefFile.open(programmArguments.option("cfreq"));
        }else{
            RefFile.open(EnFreqLocation);
        }
        char temp1;
        double temp2;
        while(RefFile >> temp1 >> temp2){
            myMap.insert(std::make_pair(temp1, temp2));
        }

        for(auto element:myMap){
            refFreq.push_back(element.second);
        }



        KeyVector.clear();
        KeyVector.push_back(breakCeaser(message,refFreq));

    }

    //Task 1, 2 and 3
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


}


