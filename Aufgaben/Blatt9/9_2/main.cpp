//
// Created by Julius on 07.12.2022.
//
#include "LinkedQueue.h"
#include <iostream>

int main(){
    LinkedQueue<int> Stack;

    Stack.push(1);
    Stack.push(1);


    for(int i = 0; i < 6; ++i){
        Stack.push(i);
        std::cout << Stack.size() << std::endl;
    };

   for(auto element: Stack){
       std::cout << element << std::endl;
   }
    Stack.pop();
    //std::cout << Stack.size() << std::endl;



}
