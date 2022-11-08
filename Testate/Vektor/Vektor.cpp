// Name:
// Marikelnummer: 
#include "Vektor.h"
#include <iostream>
using namespace std;

Vektor::Vektor(unsigned len) {
  _len = len;
  _vek = new double[_len];
  for (unsigned i = 0; i < _len; ++i) {
    _vek[i] = 0;
  }
}

// Ab hier implementieren
Vektor::Vektor(): _len(3) {
   _vek = new double[_len];

}

Vektor::~Vektor() {
    delete[] _vek;

}

Vektor::Vektor(const Vektor &other) {
    _len = other._len;
    _vek = new double[_len];
    for (unsigned i = 0; i < _len; ++i) {
        _vek[i] = other._vek[i];
    }
}

Vektor &Vektor::operator=(const Vektor &other) {
    _vek = new double[other._len];
    _len = other._len;
    for(int i = 0; i < _len; ++i){
        _vek[i] = other._vek[i];
    }
}

Vektor operator+(Vektor left, Vektor right) {

    if(left.get_len() == right.get_len()){
        Vektor temp(left.get_len());
        for(int i = 0; i < left.get_len(); ++i){
            temp[i] = left[i] += right[i];
        }
        return temp;
    }else{
        std::runtime_error("Vektoren haben nicht die gleiche Länge");
        throw 0;
    }

}

void Vektor::resize(unsigned l) {
    Vektor temp(l);
    for(int i = 0; i < l; ++i){
        if(_len >= i){
            temp._vek[i] = _vek[i];
        }else{
            temp._vek[i] = 0;
        }
    }
    delete[] _vek;
    _vek = new double[l];
    for(int i = 0; i < l; ++i){
        _vek[i] = temp._vek[i];
    }
    _len = l;

}
