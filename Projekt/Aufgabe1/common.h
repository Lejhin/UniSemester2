//
// Created by Julius on 13.12.2022.
//

#ifndef SEMESTER_2_COMMON_H
#define SEMESTER_2_COMMON_H
#include <iostream>
class key{
private:
    int value;
public:
    key(char input=3){
        if(input <= 122 && input >=97){
            value = (int)input%96;
        }else{
            value = 3;
            std::cerr << "wrong key input. Standart key was used.";
        }
    }
    long getKey(){return value;}
    //Aufgabe 1
    char encrypt(char ToEncrypt){
        int newValue = ToEncrypt;

        if(ToEncrypt <= 90 && ToEncrypt >= 65){//Großbuchstaben
            newValue = ((ToEncrypt+value)/90)*65 + (ToEncrypt+value)%90;
        }else if(ToEncrypt <= 122 && ToEncrypt >=97){ //kleine Buchstaben
            newValue = ((ToEncrypt+value)/122)*97 + (ToEncrypt+value)%122;

        }
        return newValue;
    }

    //Aufgabe 2;
    char decrypt(char ToDecrypt){
        int newValue = ToDecrypt;
        if(ToDecrypt <= 90 && ToDecrypt >= 65){//Großbuchstaben
            newValue = (ToDecrypt-value)+ (64/(ToDecrypt-value))*25;
        }else if(ToDecrypt <= 122 && ToDecrypt >=97){ //kleine Buchstaben
            newValue = (ToDecrypt-value) + (96/(ToDecrypt-value))*25;


        }
        return newValue;
    }
};


#endif //SEMESTER_2_COMMON_H
