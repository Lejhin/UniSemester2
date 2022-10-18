/*
 * main.cpp
 *
 *  Created on: 05.10.2022
 *      Author: n2210657
 */

#include <iostream>
#include <vector>
#include "time.h"
#include "participant.h"


int main(int argc, char** argv){

	std::vector<Participant> teilnehmer;

	for(int i = 1; i < argc; i++){
		Participant newparticipant(argv[i]);

		teilnehmer.push_back(newparticipant);

	}






	Time zeit(10,0,0);


	std::cout << zeit.just_seconds() << std::endl;

}




