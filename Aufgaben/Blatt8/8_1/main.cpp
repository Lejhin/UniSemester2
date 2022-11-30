//
// Created by Julius on 30.11.2022.
//
#include "Sequence.h"
#include "studi.h"
#include <fstream>


int main(){
    Sequence<Studi> Array(1);



    std::ifstream file;
    file.open("Aufgaben/Blatt3/3_5/studis.txt");

    std::string buffer;
    Studi temp;

    while (file >> temp) {
        Array.push_back(temp);
    }


    for(int i = 0; i < Array.size(); ++i){
        std::cout << Array[i] << std::endl;
    }

}
