/*
 * main.cpp
 *
 *  Created on: 29.09.2022
 *      Author: n2210657
 */
#include <iostream>



int& at(int* vec, int len, int i){

	if( i >= len){
		std::cerr <<  "index overflow" << std::endl;
		throw 0;

	}else{

		return vec[i];
	}
}








