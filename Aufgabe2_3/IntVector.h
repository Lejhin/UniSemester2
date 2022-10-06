//
// Created by juliu on 06.10.2022.
//

#ifndef SEMESTER_2_INTVECTOR_H
#define SEMESTER_2_INTVECTOR_H
#include <iostream>

class IntVector{
private:
    int* array;
    size_t len;

public:
    IntVector(size_t len);
    ~IntVector();
    size_t size();
    int& at(size_t idx);
    void out();
};

#endif //SEMESTER_2_INTVECTOR_H
