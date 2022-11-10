//
// Created by Julius on 09.11.2022.
//NOTIZ FÜR PATRICIA:
// Throw Statements nicht vollständig implementiert, da Übungsblatt nicht mehr vorhanden
// und genaue Instruktionen fehlen

// das erste Element gibt nicht sich selbst an (z.B. [5,1,2,3,4,5])

#include <initializer_list>
#include <iostream>

class IntVector{

private:
    int* array;
public:
    //nicht im Testat; nur zur initialisierung des Intvectors und zum Testen der Testat Funktionen
    IntVector(std::initializer_list<int> l){
        array = new int[l.size()+1];
        for(int i = 0; i < l.size()+1; ++i){
            array[i] = *(l.begin()+i);
        }
    }
    int& getlen(){
        return array[0];
    }
    //end


    //Standart Konstruktor um Freispeicher freizulegen
    IntVector(int l = 0){
        array = new int[l+1];
        array[0] = l;
    }
    //Kopier-Konstruktor
    IntVector(IntVector& other){
        array = new int[other.array[0]+1];
        for(int i = 0; i <= other.array[0]; ++i){
            array[i] = other.array[i];
        }
    }

    //Operator Überladung
    IntVector& operator=(IntVector& other){
        delete[] array;
        array = new int[other.array[0]+1];
        for(int i = 0; i <= other.array[0]; ++i){
            array[i] = other.array[i];
        }
        return *this;
    }

    int& at(int idx)const{
        if(idx < array[0] && idx >= 0){
            return array[idx+1];
        }else{
            throw std::runtime_error("index out of bounds");
        }
    }
    int max(){
        if(array[0] > 0){
            int max = array[1];
            for(int i = 2; i <= array[0]; ++i){
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
        array = new int[temp.array[0]+2];
        for(int i = 0; i <= temp.array[0]; ++i){
            array[i] = temp.array[i];
        }
        array[0] += 1;
        array[array[0]] = ele;
    }

    void addTwoArrays(IntVector& other){
        IntVector temp = *this;
        delete[] array;
        array = new int[temp.array[0]+other.array[0]+1];
        for(int i = 0; i <= temp.array[0]; ++i){
            array[i] = temp.array[i];
        }
        for(int i = array[0]+1; i <= array[0]+other.array[0]; ++i ){
            array[i] = other.array[i-array[0]];
        }
        array[0] = temp.array[0]+other.array[0];
    }
};

std::ostream& operator<<(std::ostream& out, IntVector other){
    for(int i = 0; i < other.getlen(); ++i){
        out <<  other.at(i) << " ";
    }
   return out;
}

int main() {
    int A = 5;
    IntVector a = {4, 1, 2, 3,4};
    IntVector b(a);


    //Testet Kopier Konstrukor und = Operator
    std::cout << "Input Array A:    " << a << std::endl;
    std::cout <<"Copied Array B:    "<< b << std::endl;
    IntVector c{5,1,2,5,6,8};
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