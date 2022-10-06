#include <iostream>
#include "date.h"


int main(){

    date event_date(5,10,2022);
    const date feiertag(3,10,2022);

    feiertag.print();

    event_date.add_day(4);

    event_date.print();

 

    

}