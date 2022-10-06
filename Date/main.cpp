#include <iostream>
#include "date.h"
#include "noisy.h"


int main(){

    date event_date(5,10,2022);
    const date feiertag(3,10,2022);

    Noisy a("a");
    Noisy b("b");

    std::cout << Noisy::get_counter() << std::endl;

    feiertag.print();

    event_date.add_day(4);

    event_date.print();

}