/*
 * time.h
 *
 *  Created on: 05.10.2022
 *      Author: n2210657
 */

#ifndef TIME_H_
#define TIME_H_




class Time{


private:
	unsigned int seconds;
	unsigned int minutes;
	unsigned int hours;
	unsigned int calculateSeconds() const;
public:

	Time(unsigned int seconds = 0, unsigned int minutes = 0, unsigned int hours = 0);
	void time_print() const;
	void add_seconds( int seconds);
	void add_minutes(int minutes);
	void add_hours(int hours);
	unsigned int get_seconds();
	unsigned int get_minutes();
	unsigned int get_hours();
	unsigned int just_seconds() const;
	void error_message(int Fehlercode);
    int diff(const Time& other)const;


};


#endif /* TIME_H_ */
