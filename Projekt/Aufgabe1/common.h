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

    int calcPercent(size_t index)const{
        if(index > size){
            std::cerr << "index too high";
            throw "b";
        }
        return int(double(Array[index])/double(totalCharCount)*100);
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

    void printFrequency()const{

        for(int i = 0; i < size; ++i){
            int starCount = calcPercent(i);
            std::cout << char(i+97) << ":   ";
            for(int j = 0; j < starCount; ++j){
                std::cout << "*";
            }
            std::cout << std::endl;
        }
    }
};

//single ceasar encryption
void encrypt(int key, std::vector<char>& message, std::vector<char>& outPut);
//multiple encryption with string of keys
void encrypt(std::vector<char>& keyVector, std::vector<char>& message, std::vector<char>& outPut);
//single ceasar decryption
void decrypt(int key, std::vector<char>& message, std::vector<char>& outPut);
//multiple decryption with string of keys
void decrypt(std::vector<char>& keyVector, std::vector<char>& message, std::vector<char>& outPut);
//appending to outputfile
void WriteToFile(std::vector<char>& input, std::fstream& file);

#endif //SEMESTER_2_COMMON_H
