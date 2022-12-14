//
// Created by Julius on 13.12.2022.
//

#ifndef SEMESTER_2_COMMON_H
#define SEMESTER_2_COMMON_H
#include <iostream>
#include <vector>
#include <fstream>
class Key{
private:
    int value;
public:
    Key(char input=3){

        if(input<= 122 && input >=97){
            value = input%97;
        }else{
            value = 3;
            std::cerr << "wrong key input. Standart key was used.";
        }

    }
    Key(Key& other){
        this->value = other.value;
    }

    void operator=(Key& other){
        this->value = other.value;
    }
    void operator=(int other){
        this->value = other;
    }


    long getKey(){return value;}


    //Aufgabe 1
    char encrypt(char ToEncrypt){
        int newValue = ToEncrypt;
        //91 / 123 so Z (which would be 122/122 = 1) spill to the other side
        if(ToEncrypt <= 90 && ToEncrypt >= 65){//Großbuchstaben
            newValue = ((ToEncrypt+value)/91)*65 + (ToEncrypt+value)%91;
        }else if(ToEncrypt <= 122 && ToEncrypt >=97){ //kleine Buchstaben
            newValue = ((ToEncrypt+value)/123)*97+ (ToEncrypt+value)%123;
        }
        return newValue;
    }

    //Aufgabe 2;
    char decrypt(char ToDecrypt){

        int newValue = ToDecrypt;
        if(ToDecrypt <= 90 && ToDecrypt >= 65){//Großbuchstaben
            newValue = (ToDecrypt-value)+ (64/(ToDecrypt-value))*26;
        }else if(ToDecrypt <= 122 && ToDecrypt >=97){ //kleine Buchstaben
            newValue = (ToDecrypt-value) + (96/(ToDecrypt-value))*26;
        }
        return newValue;
    }
};


//Aufgabe 3
class Frequency{
private:
    int* Array;
    size_t size;
    size_t totalCharCount = 0;

    int round(double value)const{
        int Ergebnis;
        if(double(value-int(value)) >= 0.5){
           Ergebnis = value+1;
        }else{
           Ergebnis = value;
        }
        return Ergebnis;
    }

public:
    Frequency( size_t size): size(size){
        Array = new int[size]{};
    }
    Frequency(): size(26){
        Array = new int[26]{};
    }
    ~Frequency(){
        delete[] Array;
    }
    void operator=(Frequency& other){
        this->size = other.size;
        this->totalCharCount = other.totalCharCount;
        delete[] Array;
        Array = new int[other.size];
        for(int i = 0; i < size; ++i){
            Array[i] = other.Array[i];
        }
    }

    int* getArray()const{return Array;}
    size_t Size()const{return size;}
    void calculateRelativeFrequency(std::vector<char>& message){

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

    double calcPercent(size_t index)const{
        if(index > totalCharCount ){
            std::cerr << "index too high";
            throw "b";
        }
        return double(Array[index])/double(totalCharCount)*100;
    }


    void printFrequency()const{
        std::cout <<calcPercent(0)<< " " << Array[0] << std::endl;
        for(int i = 0; i < size; ++i){
            int starCount = round(calcPercent(i));
            std::cout << char(i+97) << ":   ";
            for(int j = 0; j < starCount; ++j){
                std::cout << "*";
            }
            std::cout << std::endl;
        }
    }
};


void encrypt(std::vector<char>& keyVector, std::vector<char>& message, std::vector<char>& outPut);
void decrypt(std::vector<char>& keyVector, std::vector<char>& message, std::vector<char>& outPut);
//appending to outputfile
void WriteToFile(std::vector<char>& input, std::fstream& file);
void print(std::vector<char>& message);

inline int breakCeaser(std::vector<char>& message, std::vector<double>& reffreq){
    int bestIndex = 0;
    Frequency CurrentBestFreq;
    CurrentBestFreq.calculateRelativeFrequency(message);

    std::vector<char> localEncryption;
    std::vector<char> localKeyVec;
    for(int i = 97; i < 122; ++i ){
        Frequency localFreq;
        localKeyVec.push_back(i);
        decrypt(localKeyVec, message, localEncryption);
        localKeyVec.pop_back();
        localFreq.calculateRelativeFrequency(localEncryption);
        if(localFreq.calcPercent(i%97)-reffreq[i%97] > CurrentBestFreq.calcPercent(i%97)-reffreq[i%97]){
            CurrentBestFreq = localFreq;
            bestIndex =i;
        }


    }

    return bestIndex;
}

template<typename T>
inline void sort(std::vector<T>& vec);

#endif //SEMESTER_2_COMMON_H
