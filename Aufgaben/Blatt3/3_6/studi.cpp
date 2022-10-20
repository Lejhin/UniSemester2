//
// Created by Julius on 20.10.2022.
//

#include "studi.h"
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;
int main(){

    std::ifstream file;
    std::vector<Studi> Uni;


    file.open("Aufgaben/Blatt3/3_6/studis.txt");

    char buffer;
    int count = 0;
    std::string localMatr;
    std::string localVorname;
    std::string localNachname;

    while(file >> buffer){
        if(buffer != '\n'){
            if(buffer != ' ' && count == 0){
                localMatr.push_back(buffer);
            }
            if(buffer != ' ' && count == 1){
                localVorname.push_back(buffer);
            }
            if(buffer != ' ' && count == 2){
                localNachname.push_back(buffer);
            }
            count++;
        }else{

            Uni.push_back(Studi(std::stof(localMatr), localVorname, localNachname));
            count = 0;
        }

    }


    for(size_t i = 0; i < Uni.size(); ++i){
        std::cout << Uni.at(i) << std::endl;
    }






}
