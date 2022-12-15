//
// Created by Julius on 13.12.2022.
// Matrikelnummer: 2210657
//

#include "common.h"
#include <map>
#include <fstream>


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


//Task 5
// -> if the difference between the Reference and current character-Frequency is smaller than the current best one,
//the current character gets a point. If the entire character Frequency has more points than the current best one, the current
//Frequency becomes best one. After all Loops, the index of the best one gets returned

//BUG -- needs at least 56 characters to correctly break the ceaser encryption.
int breakChiffre(std::vector<char>& message, std::map<char ,double>& reffreq){
    int index=0;
    Frequency CurrentBestFreq;
    int BestSumMax= 0;
    CurrentBestFreq.calculateRelativeFrequency(message);
    std::vector<char> localEncryption;
    std::vector<char> localKeyVec;
    //Decrypts with all possible keys and generates their corresponding Frequencies
    for(int i = 97; i < 122; ++i ){
        Frequency localFreq;
        localKeyVec.push_back(i);
        decrypt(localKeyVec, message, localEncryption);
        localKeyVec.clear();
        localFreq.calculateRelativeFrequency(localEncryption);
        //temporary Sum of all moments in which the current Frequency was closer to the Reference than the current best one
        int localSumMax = 0;
        for(int j = 97; j < 122; ++j){
            if(diff(localFreq.calcPercent(j%97), reffreq[j]) <diff(CurrentBestFreq.calcPercent(j%97),reffreq[j])){
                localSumMax++;
            }
        }
        if(!i){
            //sets the first Frequency as the currently best one
            BestSumMax = localSumMax;
        }else{
            //only works on large texts. If the text is too small, the differences are too small
            //to differentiate between 26 different encryptions
            if(localSumMax > BestSumMax){
                BestSumMax = localSumMax;
                index = i;
            }
        }
        //the local encryption only appends -> clear the old encrypted vector to make space for the new one
        localEncryption.clear();
    }
    return index;
}


//outputs the positive difference of two values
double diff(double value1, double value2){
    if(value1-value2 < 0){
        return value2-value1;
    }else{
        return value1-value2;
    }
}
