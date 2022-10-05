#include <iostream>
#include "date.h"

 void print(date* d){

    std::cout << d << std::endl;
}


static int m30[4] {4,6,9,11};
static int m31[7] {1,3,5,7,8,10,12};

void init_date(date* d, int day, int month, int year){
    d-> day = day;
    d-> month = month;
    d-> year = year;

}

void add_day(date* d, int days){


    d-> day = d->day+ days;

    if(d-> day == 4 || d-> day == 6 || d->day == 9 || d->day == 11){
        if(d-> day > 30){


            d->day = d->day/30;
            d->month+= d->day%30;
            if(d->month == 12){

                d->month = 1;
                d->year +=1;
            }
        }

    }else{
        if(d-> day > 31){
            d->day = d->day/31;
            d->month+=d->day%30;
            if(d->month == 12){

                d->month = 1;
                d->year +=1;
            }
        }
}