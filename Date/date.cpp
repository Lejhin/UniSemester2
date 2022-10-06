#include <iostream>
#include "date.h"

 void print(date* d){

    std::cout << d << std::endl;
}


static int m30[4] {4,6,9,11};
static int m31[7] {1,3,5,7,8,10,12};

date::date( int day, int month, int year){
    this->day = day;
    this-> month = month;
    this-> year = year;

}


