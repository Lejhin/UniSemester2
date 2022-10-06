//
// Created by juliu on 06.10.2022.
//

#include "IntVector.h"


IntVector::IntVector(size_t len) {
    array = new int[len];
    for(size_t i = 0; i < len; i++){
        array[i] = i;
    }
    this->len = len;
}

IntVector::~IntVector() {
    delete(array);
}

size_t IntVector::size() {
    return len;
}

int& IntVector::at(size_t idx){
    if(idx < len){
        return array[idx];
    }else{
        throw std::runtime_error("index out of range");

    }
}

void IntVector::out() {
    for(size_t i = 0; i < len; i++){
        std::cout << array[i] <<  " ";
    }
}


