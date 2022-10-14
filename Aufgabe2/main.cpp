/*
 * main.cpp
 *
 *  Created on: 28.09.2022
 *      Author: n2210657
 */

#include <iostream>
#include <vector>
#include "ooptool.h"



std::vector<int> convert(std::vector<int> vek, int SW){

	std::vector<int> outvek;

	outvek.push_back(vek.at(0));
	outvek.push_back(vek.at(1));
	outvek.push_back(1);



	for(size_t i = 3; i < vek.size(); i++){



		if(vek.at(i) < SW*vek.at(2)/100.0){

			outvek.push_back(0);
		}else{
			outvek.push_back(1);
		}


	}


	return outvek;


}
int main(int argc, const char** argv){



	argsp_t argsp(argc, argv);


	std::vector<int> values = read_pgm(argsp.pos(0));


	std::cout << values.size() << std::endl;




	save_pgm(argsp.pos(1), convert(values, argsp.int_pos(2)));










}




