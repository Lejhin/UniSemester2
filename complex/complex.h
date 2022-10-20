//
// Created by Julius on 20.10.2022.
//

#ifndef SEMESTER_2_COMPLEX_H
#define SEMESTER_2_COMPLEX_H

#include <iostream>
class Complex{

private:
    double real;
    double imag;

public:
    Complex(double real = 0, double imag = 0) : real(real), imag(imag){
    }



    Complex& operator=(double _real){
        this->real = _real;
        this->imag = 0;
        return *this;
    }

    Complex& operator+=(Complex right){
        this->real += right.real;
        this-> imag += right.imag;
        return *this;

    }

    Complex operator*(Complex right)const{
        double tempReal = real*right.getReal() - imag*right.getImag();
        double tempImag = imag*right.getImag() - real*right.getReal();
        return Complex(tempReal, tempImag);
    }



    double getReal()const{return real;}
    double getImag()const{return imag;}






};

inline Complex operator+(Complex left, Complex right){
    double tempReal = left.getReal() + right.getReal();
    double tempImag = left.getImag() + right.getImag();
    return Complex(tempReal, tempImag);
}


std::ostream& operator<<(std::ostream& out, Complex a){
    return out << '(' << a.getReal() << '+' << a.getImag() << "i)";

}


//nur einen Implementieren, da compiler nicht weiß, welche Funktion er aufrufen soll
/*inline Complex operator*(Complex left, Complex right){
    double tempReal = left.getReal()*right.getReal() - left.getImag()*right.getImag();
    double tempImag = left.getImag()*right.getImag() - left.getReal()*right.getReal();
    return Complex(tempReal, tempImag);
}*/



#endif //SEMESTER_2_COMPLEX_H
