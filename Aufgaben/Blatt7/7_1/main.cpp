//
// Created by Julius on 24.11.2022.
//
#include <iostream>
#include "ooptool.h"
#include "fstream"


int MaximumSubArray(std::vector<int> vector){
    int CurrentMax= 0;
    int localMax = 0;
    for(int i = 0; i < vector.size(); ++i){
        for(int j = vector.size(); j > i; --j){
            for(int m = i; m < j; m++){
                localMax += vector[m];
            }
            if(localMax > CurrentMax){
                CurrentMax = localMax;
            }
        }
    }
    return CurrentMax;
}

int MaxSubArrayImproved(std::vector<int> ints){
    int CurrentMax = 0;
    int localMax = 0;


    return CurrentMax;
}

int MaxSubArrayRekursiv(std::vector<int> vector){
    if(vector.size() == 1){
        return vector[0];
    }

    int currentMax = 0;
    std::vector<int> links;
    std::vector<int> rechts;
    for(int i = 0; i < vector.size()/2; i++){
        links.push_back(vector[i]);
    }
    for(int i = vector.size()/2+1; i < vector.size(); ++i){
        rechts.push_back(vector[i]);
    }

    int MaxLinks = MaxSubArrayRekursiv(links);
    int MaxRechts = MaxSubArrayRekursiv(rechts);
    if(MaxLinks+MaxRechts > MaxLinks && MaxLinks+MaxRechts > MaxRechts){
        currentMax = MaxLinks+MaxRechts;
    }else{
        if(MaxLinks > MaxRechts){
            currentMax = MaxLinks;
        } else{
            currentMax = MaxRechts;
        }
    }
    return currentMax;
}

int main(){
    std::vector<int> vec;
    std::ifstream file;
    file.open("Aufgaben/Blatt7/7_1/data/maxsub.dat")  ;
    int element;

    while( file >> element){
             vec.push_back(element);
    }


    std::cout<< MaxSubArrayRekursiv(vec);
}