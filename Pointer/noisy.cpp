#include "noisy.h"

int Noisy::counter = 0;

Noisy::Noisy(std::string name){

    this->name = name;
    counter++;

}
Noisy::Noisy(const Noisy &other) {
    counter++;
    name = other.name;
}
Noisy::~Noisy(){
    counter--;
    std::cout << counter << std::endl;
}

int Noisy::get_counter(){

    return counter;
}