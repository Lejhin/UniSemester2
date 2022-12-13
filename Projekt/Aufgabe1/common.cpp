//
// Created by juliu on 13.12.2022.
//
#include "common.h"

void Frequency::calculateRelativeFrequency( std::vector<char>& message){
    for(char character: message){
        if(character <= 90 && character >= 65){
            Array[character%65]++;
            totalCharCount++;
        }
        if(character <= 122 && character >= 97){
            Array[character%97]++;
            totalCharCount++;
        }

    }
}




