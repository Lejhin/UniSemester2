//
// Created by Julius on 08.12.2022.
//

#include "Widerstand.h"
#include <iostream>
#include <vector>


int main(){

    std::vector<float> Netz_time;

    Resistor r1(100), r2(200), r3(300);
    Poti p1(0);



    for(int i = 0; i < 21; ++i){
        p1.set_ohm(i*30);
        Parallel Netz2(&p1, &r2);
        Serial net(&Netz2, &r3);
        Netz* Hauptnetz = &net;
        Netz_time.push_back(Hauptnetz->ohm());
    }

    for(int i = 0; i < Netz_time.size(); ++i){
        std::cout << Netz_time[i] << std::endl;
    }








}
const void foo();