/*
 * IntVector.cpp
 *
 *  Created on: 06.10.2022
 *      Author: n2210657
 */

#include "IntVector.h"






IntVector::IntVector(int* array, size_t len){

	this->array = new int[len];
	for(size_t i= 0; i < len; i++){
		this->array[i] = array[i];
	}
	this->len = len;

}

IntVector& IntVector::operator=(const IntVector& newVec){
	if(this->array != newVec.array){
		delete this->array;
		len =newVec.len;
		array = new int[newVec.len];
		array = newVec.array;
		return *this;
	}else{
		throw 0;
	}
}
IntVector::IntVector(size_t len){

	this->array = new int[len];
	for(size_t i= 0; i < len; i++){
		this->array[i] = i;
	}
	this->len = len;
}

IntVector::~IntVector(){
	delete(array);

}


std::size_t IntVector::size()const{
	return len;
}

int& IntVector::at(size_t idx){
	if(idx < len){
		return array[idx];
	}
	else{
		throw 0;
		std::runtime_error("index out of range");
	}
}

int& IntVector::operator [](const int idx){
	if(idx < len){
		return array[idx];
	}
	else{
		throw 0;
		std::runtime_error("index out of range");
	}
}

void IntVector::out()const{

	for(size_t i = 0; i < len; i++){
		std::cout << array[i]<< std::endl;
	}

}
