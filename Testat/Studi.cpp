#include "Studi.h"
using namespace std;

Studi::Studi(): _matnr(0){

}

Studi::Studi(long matnr, string vorname, string nachname): _matnr(matnr), _vorname(vorname), _nachname(nachname) {
}

Studi::Studi(const Studi &other) {
    _vorname = other._vorname;
    _nachname = other._nachname;
    _image = new char[other.get_image_size()];
    for(int i = 0; i < other.get_image_size(); ++i){
        _image[i] = other.get_image()[i];
    }
    _image_size = other._image_size;
    _matnr = 0;
}

Studi::~Studi() {
    delete[] _image;
}

long Studi::matnr() const {
	return _matnr;
}

string Studi::vorname() const {
	return _vorname;
}

string Studi::nachname() const {
	return _nachname;
}

bool Studi::set_matnr(long matnr) {
    if(matnr > 999999 && matnr < 10000000){
        _matnr = matnr;
        return true;
    }else{
        return false;
    }
}

void Studi::set_image(char *img, int size) {
    _image = new char[size];
    for(int i = 0; i < size; ++i){
        _image[i] = img[i];
    }
    delete[] img;
}
