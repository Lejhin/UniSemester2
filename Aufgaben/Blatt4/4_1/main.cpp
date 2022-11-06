//
// Created by juliu on 27.10.2022.
//

#include <iostream>
#include "templates.h"

int main() {


    int vec[] = {1, 2, 3, 4};
    const char* charvec[] = {"zgv", "deef", "abcdefghji",  "a"};
    std::cout << Max(charvec, 4) << std::endl;
    std::cout << Max(vec, 4) << std::endl;


}

