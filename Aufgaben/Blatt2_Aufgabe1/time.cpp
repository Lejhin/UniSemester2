/*
 * time.cpp
 *
 *  Created on: 05.10.2022
 *      Author: n2210657
 */

#include <iostream>
#include "time.h"


Time::Time(){
	this->seconds = 0;
	this->minutes = 0;
	this->hours = 0;

}


Time::Time(unsigned int seconds, unsigned int minutes,unsigned  int hours){

	this->seconds = seconds%60;
	this->minutes = minutes%60+seconds/60;
	this->hours = hours+minutes/60;

}


void Time::time_print(){

	std::cout << hours << "." << minutes << "." << seconds << std::endl;
}


unsigned int Time::just_seconds(){

	return this->calculateSeconds();
}

unsigned int Time::calculateSeconds(){

	return this->seconds + (this->minutes*60) + (this->hours*60*60);
}


void Time::add_seconds( int seconds){
	if(this->calculateSeconds()+seconds > 0){
		this->seconds += seconds;

	}else{
		this->error_message(1);
	}
}

void Time::add_minutes(int minutes){
	if(this->calculateSeconds()+minutes*60> 0){
		this->seconds += minutes;
	}else{
		this->error_message(2);
	}

}
void Time::add_hours(int hours){
	if(this->calculateSeconds()+hours*60*60> 0){
		this->seconds += hours;
	}else{
		this->error_message(3);
	}
}

void Time::error_message(int Fehlercode){

	std::cout << "Error:" << Fehlercode << std::endl;
}

unsigned int  Time::get_seconds(){
	return this->seconds;
}

unsigned int  Time::get_minutes(){
	return this->minutes;
}

unsigned int  Time::get_hours(){
	return this->minutes;
}




