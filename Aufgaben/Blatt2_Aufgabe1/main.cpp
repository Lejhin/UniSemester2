/*
 * main.cpp
 *
 *  Created on: 05.10.2022
 *      Author: n2210657
 */

#include <iostream>
#include <vector>
#include "time.h"
#include "participant.h"


int main(int argc, char** argv) {

    std::vector<Participant> teilnehmer;

    for (int i = 1; i < argc; i+=3) {

        Participant newparticipant(argv[i]);
        teilnehmer.push_back(newparticipant);
        teilnehmer.at(0).set_Time(atoi(argv[i+1]), atoi(argv[i+2]), atoi(argv[i+3]));

    }
    for (int i = 0; i < teilnehmer.size(); ++i) {
        std::cout << teilnehmer[i].get_name() << std::endl;



    }

    std::cout << teilnehmer.size() << std::endl;

}




