//
// Created by Julius on 27.10.2022.
//

#ifndef SEMESTER_2_TEMPLATES_H
#define SEMESTER_2_TEMPLATES_H

#include <iostream>


template<typename T, typename W>

T log_consume( T base, W to_consume){
    std::cout << "base " << typeid(base).name() << base;
    std::cout << " to_consume: " << typeid(to_consume).name() << to_consume << std::endl;
    base += to_consume;
    return base;
}

template<typename T>
int find(T* vec, int len, const T& val){
    int idx = 0;
    while(idx < len){
        if(vec[idx] == val){
            return idx;
        }
        idx += 1;
    }
    return -1;
}

template<typename T>
void tausche(T& x, T& y) {
    T temp = x;
    x = y;
    y = temp;
}

#endif //SEMESTER_2_TEMPLATES_H
