#include "noisy.h"

int Noisy::counter = 0;

Noisy::Noisy(std::string name){

    this->name = name;
    counter++;

}
Noisy::~Noisy(){
    counter--;
}

int Noisy::get_counter(){

    return counter;
}