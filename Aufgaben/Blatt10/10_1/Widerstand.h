//
// Created by Julius on 08.12.2022.
//

#ifndef SEMESTER_2_WIDERSTAND_H
#define SEMESTER_2_WIDERSTAND_H
#include <iostream>
class Netz{
public:
    virtual float ohm () const{return 0;};
};

class Resistor: public Netz{
protected:
    float value;
public:
    Resistor(float val){
        value = val;
    }
    float ohm() const override{return value;}
};


class Serial: public Netz{
protected:
    Netz* a;
    Netz*b;
public:
    Serial(Netz* value, Netz* value2) {
        a = value;
        b = value2;
    }
    float ohm() const override{
        return a->ohm()+b->ohm();
    }
    void recalculate(Netz* val, Netz* val1){
        this->a = val;
        this-> b = val1;
    }

};

class Parallel: public Netz{
protected:
    Netz* a;
    Netz* b;

public:
    Parallel(Netz* value, Netz* value2){
        a = value;
        b = value2;
    }
    void recalculate(Netz* val, Netz* val1){
        this->a = val;
        this-> b = val1;
    }
    float ohm() const override{
        return ((a->ohm()*b->ohm())/(a->ohm()+b->ohm()));
    }
};

class Poti: public Resistor{
public:
    Poti(int value): Resistor(value){}
    void set_ohm(double ohm) {
        value = ohm;
    }
};

#endif //SEMESTER_2_WIDERSTAND_H
