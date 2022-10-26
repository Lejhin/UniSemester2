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

class sharedPointer{

private:
  Noisy* p;
  int* counter;
public:

    sharedPointer(Noisy* p) : p(p){
        counter = new int(1);
    }
    sharedPointer(const sharedPointer& other): p(other.p), counter(other.counter){
        (*counter)++;
    }

    ~sharedPointer(){
        (*counter)--;
        if(*counter == 0){
            delete p;
            delete counter;
        }
    }




};

int main(){

    Noisy* a = new Noisy("a");
    uniqueNoisy b(new Noisy("B"));
    sharedPointer c(new Noisy("z"));
    sharedPointer d(new Noisy("c"));
    d = c;
}


