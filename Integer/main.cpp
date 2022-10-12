#include "Integer.h"
#include <iostream>


    Integer t(){
        Integer c(3);
        return c;
    }

int main(){

    Integer a;
    Integer b;

    std::cout << sum(t(),10) << std::endl;

}