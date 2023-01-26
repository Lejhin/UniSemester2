//
// Created by juliu on 24.09.2022.
//
#include <iostream>
#include <vector>
#include "at.h"


int& at(int* vec, int len, int i){

    if( i >= len){
        std::cerr <<  "index overflow" << std::endl;
        throw 0;

    }else{

        return vec[i];
    }
}