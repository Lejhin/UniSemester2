//
// Created by Julius on 20.10.2022.
//

#ifndef SEMESTER_2_STUDI_H
#define SEMESTER_2_STUDI_H

#include <iostream>

class Studi{

private:
    long matnr;
    std::string vorname;
    std::string nachname;

public:

    Studi(long matnr = 0, std::string vorname = "Max", std::string nachname = "Mustermann"): matnr(matnr), vorname(vorname), nachname(nachname){}
    long getMatNr(){return matnr;}
    std::string getVorname(){return vorname;}
    std::string getNachname(){return nachname;}

};

std::ostream& operator<<(std::ostream& out, Studi a){
    return out << a.getMatNr() << " " << a.getVorname() << "" <<  a.getNachname();

}



#endif //SEMESTER_2_STUDI_H
