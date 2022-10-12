#include <iostream>
#include "date.h"


void date::normalisieren(){

    //...
}



date::date( int day, int month, int year){
    this->day = day;
    this-> month = month;
    this-> year = year;
}

void date::add_day(int day){

    this->day += day;
}

void date::print() const{
    std::cout << this->day << "." << this->month << "." << this->year << std::endl;
}




