//
// Created by juliu on 06.10.2022.
//
#include "IntVector.h"

void klappt(){
    IntVector test1(17);
    test1.out();
    std::cout << test1.size() << std::endl;

    for(size_t i = 0; i < 17; i++){
        if(i%2 == 0){
            test1.at(i) += 42;
        }
    }

    test1.out();
    std::cout << test1.size() << std::endl;


}

void crash(){

    IntVector test2(17);
    test2.at(42) = 0;
}

int main(int argc, char** argv){

   // if(argv[1] == "c"){
        crash();
   // }else{
       // std::cout<< argv[1] << std::endl;
       // klappt();
    //}
}
