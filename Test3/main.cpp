//
// Created by Julius on 19.01.2023.
//
#include <iostream>

int func(int x){return x;}
int main(){

    int x = 3;

    std::cout << func(::x) << std::endl;
}