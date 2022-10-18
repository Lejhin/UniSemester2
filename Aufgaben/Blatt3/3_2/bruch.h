//
// Created by Julius on 18.10.2022.
//

#ifndef SEMESTER_2_BRUCH_H
#define SEMESTER_2_BRUCH_H

#include <iostream>


class Bruch{

private:
    int Zähler;
    int Nenner;
    int findeGemeinsamenTeiler(){

    }

    void switchVorzeichen(){
        Nenner = -Nenner;
        Zähler = -Zähler;
    }

    void normalisieren(){
        if(Nenner < 0 || Zähler < 0){
            if(!(Zähler < 0 && Nenner > 0)){
                switchVorzeichen();
            }
        }
    }
public:

    Bruch(int Zähler, int Nenner) :Zähler{Zähler}, Nenner{Nenner}{

        this->Nenner = this->Nenner/findeGemeinsamenTeiler();
        this->Zähler = this->Zähler/findeGemeinsamenTeiler();
        normalisieren();
    }


    Bruch(const Bruch& bruch){
        this->Zähler = bruch.Zähler;
        this->Nenner = bruch.Nenner;
    }

    void out(){
        std::cout << Zähler << "/" << Nenner << std::endl;
    }

    int zaehler()const{
        return Zähler;
    }
    int nenner()const {
        return Nenner;
    }



    bool operator==( const Bruch& bruch){
        if(bruch.Nenner == this->Nenner){
            if(bruch.Zähler == this->Zähler){
                return true;
            }
        }
        return false;
    }

    bool operator!=( const Bruch& bruch){
        if(bruch.Nenner != this->Nenner){
            return true;
        }
        if(bruch.Zähler != this->Zähler) {
            return true;
        }
        return false;
    }
    Bruch operator*=(const Bruch& bruch){
        this->Zähler *= bruch.Zähler;
        this->Nenner *= bruch.Nenner;
        return *this;
    }

    Bruch operator*(const Bruch& bruch){
        int Zähler = this->Zähler * bruch.Zähler;
        int nenner = this->Zähler * bruch.Nenner;

        return Bruch(Zähler, Nenner);
    }
    Bruch operator*(const int Zahl){
        int Zähler = this->Zähler * Zahl;
        int nenner = this->Zähler * Zahl;

        return Bruch(Zähler, Nenner);
    }








};

#endif //SEMESTER_2_BRUCH_H
