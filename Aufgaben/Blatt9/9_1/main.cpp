//
// Created by Julius on 05.12.2022.
//
#include "IntVector.h"
#include <iostream>


int main(int argc, char** argv){
    int begin = 0;
    int end = 10000;

    if(argc > 1 ){
        if(argc > 2){
            begin = atoi(argv[1]);
            end = atoi(argv[2]);
        }else{
            end = atoi(argv[1]);

        }
    }

    IntVector main(end-begin);

    int sum = 0;


   /* for(auto element : main){
        sum+= element;
    }*/

    for(IntVector::iterator curr = main.begin(); curr != main.end(); ++curr){
       sum += *curr;
    }

    std::cout << "von: " << begin << " bis: " << end << " sum: " << sum << std::endl;
}
