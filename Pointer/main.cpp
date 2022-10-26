//
// Created by Julius on 26.10.2022.
//
#include "noisy.h"

class uniqueNoisy{
private:
    Noisy* p;

public:

    uniqueNoisy(Noisy* p): p(p){};
    uniqueNoisy(const uniqueNoisy&) = delete;
    uniqueNoisy&operator=(const uniqueNoisy&) = delete;
    Noisy& operator*(){
            return *p;
    }
    Noisy* operator->(){
        return p;
    }
    ~uniqueNoisy(){
        delete p;
    }
};


int main(){

    Noisy* a = new Noisy("a");
    uniqueNoisy b(new Noisy("B"));
}


