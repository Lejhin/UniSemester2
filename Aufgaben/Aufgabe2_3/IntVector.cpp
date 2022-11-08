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
    std::cout << std::endl;
}

IntVector& IntVector::operator=( const IntVector& newVector) {
    if(this->array != newVector.array){
        delete this->array;
        len = newVector.len;
        array = new int[newVector.len];
        array = newVector.array;
        return *this;
    }else{
        throw 0;
    }
}
//Kopierkonstruktor
IntVector::IntVector(const IntVector &newVector) {
    this->array = new int[newVector.len];
    len = newVector.len;
    array = newVector.array;
}




