//
// Created by Julius on 02.11.2022.
//

#include "commonVector.h"

int main(){
    CommonVector<int, 10> vec = {1,2,4,9,16,32,64,128, 265,512, 1024};
    CommonVector<char, 25> charVec = ("Hallo tolle c++ Welt");
    CommonVector<const char*, 4> stringVec =  {"Hallo", "Tolle", "C++", "Welt"};

}

