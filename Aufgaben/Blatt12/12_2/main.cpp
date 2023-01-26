//
// Created by Julius on 18.01.2023.
//

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

int main(){

    std::vector<int> Vector;
    for(int i = 0; i < 10; ++i){
        Vector.push_back(rand() %50);
    }

    for(auto element:Vector){
        std::cout << element << " ";
    }

    std::cout << std::endl;
    sort(Vector.begin(), Vector.end(), [](int& left, int& right)  {return left  > right;});



    for(auto element:Vector){
        std::cout << element << " ";

    }
    std::cout << std::endl;




}
