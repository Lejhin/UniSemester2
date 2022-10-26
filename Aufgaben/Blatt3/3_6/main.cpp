//
// Created by Julius on 24.10.2022.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "ooptool.h"

int main(int argc, char **argv) {

    argsp_t arg(argc, argv);


    std::ifstream file;

    file.open(arg.pos(0));

    int tempInt;
    std:
    std::vector<unsigned int> Values;

    unsigned int currentMax = 0;


    if (file.is_open()) {


        while (file >> tempInt) {
            Values.push_back(tempInt);
        }

        for (int i = 0; i < Values.size(); ++i) {
            if (Values.at(i) > currentMax) {
                currentMax = Values.at(i);
            }
        }
            std::cout << "amount of Values: " << Values.size() << "\n"
                      << "Max Value = " << currentMax << std::endl;
    } else {
        std::cerr << "Wrong path" << std::endl;
    }

}
