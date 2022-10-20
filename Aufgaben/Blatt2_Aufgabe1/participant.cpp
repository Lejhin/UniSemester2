/*
 * participant.cpp
 *
 *  Created on: 05.10.2022
 *      Author: n2210657
 */
#include "participant.h"
unsigned int Participant::AnzahlTeilnehmer = 0;


Participant::Participant(std::string name): name(name){
	AnzahlTeilnehmer++;
}

Participant::Participant(std::string name, Time time) : name(name), time(time){
	AnzahlTeilnehmer++;
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

void Participant::set_Time(int seconds, int minutes, int hours) {
    time.add_seconds(seconds);
    time.add_minutes(minutes);
    time.add_hours(hours);

}











