//
// Created by Julius on 09.11.2022.
//NOTIZ FÜR PATRICIA:
// Throw Statements nicht vollständig implementiert, da Übungsblatt nicht mehr vorhanden
// und genaue Instruktionen fehlen

#include <initializer_list>
#include <iostream>

class IntVector{

private:
    int* array;
public:

    //nicht im Testat; nur zur initialisierung des Intvectors und zum Testen der Testat Funktionen
    IntVector(std::initializer_list<int> l){
        array = new int[l.size()];
        for(int i = 0; i < l.size(); ++i){
            array[i] = *(l.begin()+i);
        }
    }
    int& getParameter(int idx)const{
        return array[idx];
    }
    //end


    //Standart Konstruktor um Freispeicher freizulegen
    IntVector(int l = 0){
        array = new int[l+1];
        array[0] = l;
    }
    //Kopier-Konstruktor
    IntVector(IntVector& other){
        array = new int[other.array[0+1]];
        for(int i = 0; i < other.array[0]; ++i){
            array[i] = other.array[i];
        }
    }

    //Operator Überladung
    IntVector& operator=(IntVector& other){
        delete[] array;
        array = new int[other.array[0]+1];
        for(int i = 0; i < other.array[0]; ++i){
            array[i] = other.array[i];
        }
        return *this;
    }

    int max(){
        if(array[0] > 0){
            int max = array[1];
            for(int i = 2; i < array[0]; ++i){
                if(array[i] > max){
                    max = array[i];
                }
            }
            return max;
        }else{
            throw 0;
        }
    }
    void push_back(const int& ele){
        IntVector temp = *this;
        delete[] array;
        array = new int[temp.array[0]+1];
        array[0] = temp.array[0] + 1;
        for(int i = 0; i < temp.array[0]; ++i){
            array[i] = temp.array[i];
        }
        array[0] += 1;
        array[array[0]-1] = ele;
    }

    void addTwoArrays(IntVector& other){
        IntVector temp = *this;
        delete[] array;
        array = new int[temp.array[0]+other.array[0]-1];
        for(int i = 0; i < temp.array[0]; ++i){
            array[i] = temp.array[i];
        }
        for(int i = array[0]; i < array[0]+other.array[0]; ++i ){
            array[i] = other.array[i+1-array[0]];
        }
        array[0] = temp.array[0]+other.array[0]-1;
    }
};

std::ostream& operator<<(std::ostream& out, IntVector other){
    for(int i = 0; i < other.getParameter(0); ++i){
        out <<  other.getParameter(i) << " ";
    }
   return out;
}

int main() {
    int A = 5;
    IntVector a = {4, 1, 2, 3};
    IntVector b(a);


    //Testet Kopier Konstrukor und = Operator
    std::cout << "Input Array A:    " << a << std::endl;
    std::cout <<"Copied Array B:    "<< b << std::endl;
    IntVector c{6,1,2,5,6,8};
    std::cout << "Copy über Operator= :     " << c;
    c = a;
    std::cout <<" -> " << c << std::endl;
    //Testet Push_back Funktion
    a.push_back(A);
    std::cout << "Array A + " << A << ":    " << a << std::endl;

    //Testet MaxValue Funktion
    std::cout << "Max Value:    " << a.max() << std::endl;
    //Testet die Addition von zwei Arrays;
    a.addTwoArrays(b);
    std::cout << "A + B:     "<< a << std::endl;

}