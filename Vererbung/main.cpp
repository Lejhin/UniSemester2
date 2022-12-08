//
// Created by Julius on 08.12.2022.
//
#include <iostream>
class A{
protected:
    int* a;
public:
    A(int val=17){a = new int(val); std::cout << "A() = " << *a  << std::endl;}
    ~A(){delete a;  std::cout << "~A()" << std::endl; }
};

class B :public A{
protected:
    long* b;
public:
    B(long val= 42){b = new long(val + *a); std::cout << "B() = " << *b << std::endl;}
    ~B(){delete b; std::cout << "~B()" << std::endl;}

};
class C: B{
protected:
    double* c;
public:
    C(): B(5){c = new double(1.2); std::cout << "C()" << std::endl;}
    ~C(){delete c; std::cout << "~C()" << std::endl;}
};


int main(){
   C bobj;
}
