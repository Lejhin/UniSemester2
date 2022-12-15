//
// Created by Julius on 13.12.2022.
// Matrikelnummer: 2210657
//

#ifndef SEMESTER_2_COMMON_H
#define SEMESTER_2_COMMON_H
#include <iostream>
#include <vector>
#include <map>

class Key{
private:
    int value;
public:
    Key(char input=3){
        if(input<= 122 && input >=97){
            value = input%97;
        }else{
            value = 3;
            std::cerr << "Key must only contain letters from the english alphabet -> standard key was assigned";
        }
    }
    //for potential use
    void operator=(Key& other){
        this->value = other.value;
    }
    void operator=(int other){
        this->value = other;
    }

    long getKey(){return value;}

    //Task 1
    //encrypts one char
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
    //decrypts one char
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
        int tempValue;
        if(double(value-int(value)) >= 0.5){
           tempValue = value+1;
        }else{
           tempValue = value;
        }
        return tempValue;
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
        if(index > size ){
            throw std::runtime_error("index out of bounds");
        }
        return double(Array[index])/double(totalCharCount)*100;
    }


    void printFrequency()const{
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

double diff(double value1, double value2);

int breakChiffre(std::vector<char>& message, std::map<char, double>& reffreq);

void print(std::vector<char>& message);

#endif //SEMESTER_2_COMMON_H
