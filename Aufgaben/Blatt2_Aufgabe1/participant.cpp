/*
 * participant.cpp
 *
 *  Created on: 05.10.2022
 *      Author: n2210657
 */
#include "participant.h"
unsigned int Participant::AnzahlTeilnehmer = 0;


Participant::Participant(std::string name)
{
	AnzahlTeilnehmer++;
	this->name = name;
}

Participant::Participant(std::string name, Time time){

	AnzahlTeilnehmer++;

	this->name = name;
}

Participant::~Participant(){

	AnzahlTeilnehmer--;
}

std::string Participant::get_name(){

	return this->name;
}

Time Participant::get_time(){
	return this->time;
}











