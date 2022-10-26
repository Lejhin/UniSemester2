//
// Created by Julius on 20.10.2022.
//

#include "studi.h"
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;
int main() {

    std::ifstream file;
    std::vector<Studi> Uni;


    file.open("Aufgaben/Blatt3/3_5/studis.txt");

    std::string buffer;

    Studi temp;

    while (file >> temp) {
        Uni.push_back(temp);
    }


    for(int i = 0; i < Uni.size(); ++i){
        std::cout << Uni.at(i) << std::endl;
    }
}