//
// Created by juliu on 24.09.2022.
//
#include <iostream>
#include <vector>

size_t finde(std::vector<int> vec, int a){
    size_t idx = 0;
    while(idx < vec.size()){
        if(vec[idx] == a){
            return idx;
        }
        idx++;
    }
    return vec.size();
}