/*
 * main.cpp
 *
 *  Created on: 28.09.2022
 *      Author: n2210657
 */

#include <iostream>
#include "ooptool.h"


double heron(double x, double presicion){
	float erg = float((1+x)/2);
	float oldErg = 0;

	while(abs(oldErg-erg) > presicion){

		oldErg = erg;
		erg = (oldErg + x/oldErg) / 2;

	}


	return erg;
}
int main(int argc, const char** argv){

	argv[1] = "10";

	argsp_t argsp(argc, argv);

	std::cout << heron(argsp.double_pos(0, 10), argsp.double_pos(1, 10e-6)) << std::endl;


}




