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
    IntVector& operator= (const IntVector& newVector); //Zuweisungsoperator
    IntVector(const IntVector& newVector); //Kopierkonstruktor
    ~IntVector();
    size_t size();
    int& at(size_t idx);
    void out();
};

// Intvector a;
//Intvector b(a);


#endif //SEMESTER_2_INTVECTOR_H
