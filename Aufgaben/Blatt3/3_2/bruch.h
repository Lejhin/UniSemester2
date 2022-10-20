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
    int findeGemeinsamenTeiler(int a, int b){
        while (a != 0){
            std::swap(a,b);
            a%=b;
        }
        return b;
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

    Bruch(int Zaehler, int Nenner = 1) :Zaehler{Zaehler}, Nenner{Nenner}{

        int normal = findeGemeinsamenTeiler(this->Nenner, this->Zaehler);

        this->Nenner = this->Nenner/normal;
        this->Zaehler = this->Zaehler/normal;
        normalisieren();
    }


    Bruch(const Bruch& bruch){
        this->Zaehler = bruch.Zaehler;
        this->Nenner = bruch.Nenner;
    }

    int zaehler()const{
        return Zaehler;
    }
    int nenner()const {
        return Nenner;
    }



    bool operator==( const Bruch& bruch)const{
        if(bruch.Nenner == this->Nenner){
            if(bruch.Zaehler == this->Zaehler){
                return true;
            }
        }
        return false;
    }

    bool operator!=( const Bruch& bruch)const{
        if(bruch.Nenner != this->Nenner){
            return true;
        }
        if(bruch.Zaehler != this->Zaehler) {
            return true;
        }
        return false;
    }
    Bruch& operator*=(const Bruch& bruch){
        this->Zaehler *= bruch.Zaehler;
        this->Nenner *= bruch.Nenner;
        return *this;
    }

    Bruch operator*(const Bruch& bruch){
        int Zaehler = this->Zaehler * bruch.Zaehler;
        int nenner = this->Zaehler * bruch.Nenner;

        return Bruch(Zaehler, nenner);
    }
    Bruch operator*(const int Zahl) {
        int Zaehler = this->Zaehler * Zahl;
        int nenner = this->Zaehler * Zahl;

        return Bruch(Zaehler, nenner);
    }

};

std::ostream& operator<<(std::ostream& out,Bruch a){
    if(a.nenner() == 1){
     return out << a.zaehler();
    }
    return out << a.zaehler() << "/" << a.nenner();
}

inline Bruch operator*(const int Zahl,const Bruch b){
    return Bruch(b.zaehler()*Zahl);
}


#endif //SEMESTER_2_BRUCH_H
