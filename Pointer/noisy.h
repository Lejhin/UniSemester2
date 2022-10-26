#ifndef NOISY
#define NOISY

#include <iostream>

class Noisy{

private:
    std::string name;
    static int counter;
public:

    Noisy(std::string name);
    ~Noisy();
    static int get_counter();

};


#endif