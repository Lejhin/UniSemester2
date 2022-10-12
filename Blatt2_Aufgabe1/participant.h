/*
 * participant.h
 *
 *  Created on: 05.10.2022
 *      Author: n2210657
 */

#ifndef PARTICIPANT_H_
#define PARTICIPANT_H_

#include <iostream>
#include "time.h"

class Participant{

private:
	std::string name;
	Time time;
	static unsigned int AnzahlTeilnehmer;

public:
	Participant(std::string name);
	Participant(std::string name, Time time);
	~Participant();


	std::string get_name();
	Time get_time();
};



#endif /* PARTICIPANT_H_ */
