//
// Created by Julius on 02.11.2022.
//

#ifndef SEMESTER_2_COMMONVECTOR_H
#define SEMESTER_2_COMMONVECTOR_H
#include <iostream>
#include <cstring>
#include <initializer_list>
template<typename T, size_t len >
class CommonVector{
private:
    T* vector;


public:

    CommonVector(): vector(new T[len]{}){
    }
    //für char array;
    CommonVector(const T* temp): vector(new T[len]{}){
       for(int i = 0; i < len; ++i){
            if(i < std::strlen(temp)){
                vector[i] = temp[i];
            }else{
                vector[i] = 0;
            }
        }
    }
    //für alle anderen arrays;
   CommonVector(std::initializer_list<T> l): vector(new T[len]) {
       for (int i = 0; i < len; ++i) {
           if(i < l.size()){
               vector[i] = *(l.begin()+i);

           }else{
               vector[i] = 0;
           }
       }
   }

    ~CommonVector(){
        delete[] vector;
    }
    size_t size() const{
        return len;
    }

    T& operator[](size_t idx){
        if(idx < len && idx >= 0){
            return vector[idx];
        }
        else{
            std::cerr << "out of bounds" << std::endl;
            throw 0;
        }
    }

    void out(void) const {
        std::cout << "[ ";
        for (std::size_t i=0; i < len; i+=1)
        {
            if(vector[i] != 0){
                std::cout << vector[i] << " ";
            }
        }
        std::cout << "]" << std::endl;
    }


    T* getVector(){
        return vector;
    }


};



#endif //SEMESTER_2_COMMONVECTOR_H
