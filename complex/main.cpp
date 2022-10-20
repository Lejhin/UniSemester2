//
// Created by Julius on 20.10.2022.
//
#include "complex.h"


int main(){
    Complex a(3,2);
    Complex b(1,2);

    Complex c;
    c = Complex(1,2);

    c = a + a*b + Complex(5,6);
    a+=b;


    std::cout << a << std::endl;




}
