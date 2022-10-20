//
// Created by Julius on 18.10.2022.
//

#ifndef SEMESTER_2_BRUCH_H
#define SEMESTER_2_BRUCH_H

#include <iostream>


class Bruch{

private:
    int Zaehler;
    int Nenner;
    int findeGemeinsamenTeiler(){

    }

    void switchVorzeichen(){
        Nenner = -Nenner;
        Zaehler = -Zaehler;
    }

    void normalisieren(){
        if(Nenner < 0 || Zaehler < 0){
            if(!(Zaehler < 0 && Nenner > 0)){
                switchVorzeichen();
            }
        }
    }
public:

    Bruch(int Zaehler, int Nenner) :Zaehler{Zaehler}, Nenner{Nenner}{

        this->Nenner = this->Nenner/findeGemeinsamenTeiler();
        this->Zaehler = this->Zaehler/findeGemeinsamenTeiler();
        normalisieren();
    }


    Bruch(const Bruch& bruch){
        this->Zaehler = bruch.Zaehler;
        this->Nenner = bruch.Nenner;
    }

    void out() const{
        std::cout << Zaehler << "/" << Nenner << std::endl;
    }

    int zaehler()const{
        return Zaehler;
    }
    int nenner()const {
        return Nenner;
    }



    bool operator==( const Bruch& bruch){
        if(bruch.Nenner == this->Nenner){
            if(bruch.Zaehler == this->Zaehler){
                return true;
            }
        }
        return false;
    }

    bool operator!=( const Bruch& bruch){
        if(bruch.Nenner != this->Nenner){
            return true;
        }
        if(bruch.Zaehler != this->Zaehler) {
            return true;
        }
        return false;
    }
    Bruch operator*=(const Bruch& bruch){
        this->Zaehler *= bruch.Zaehler;
        this->Nenner *= bruch.Nenner;
        return *this;
    }

    Bruch operator*(const Bruch& bruch){
        int Zähler = this->Zaehler * bruch.Zaehler;
        int nenner = this->Zaehler * bruch.Nenner;

        return Bruch(Zähler, Nenner);
    }
    Bruch operator*(const int Zahl) {
        int Zähler = this->Zaehler * Zahl;
        int nenner = this->Zaehler * Zahl;

        return Bruch(Zähler, Nenner);
    }

};

#endif //SEMESTER_2_BRUCH_H
