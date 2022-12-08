//
// Created by Julius on 30.11.2022.
//

#ifndef SEMESTER_2_SEQUENCE_H
#define SEMESTER_2_SEQUENCE_H

#include <iostream>
template<typename T>
class Sequence{
private:
    T* array;
    int cap;
    int len;

    bool fitsInArray() {
        if (len < cap) {
            return true;
        }
        return false;

    }

public:
    Sequence(size_t cap): cap(cap){
        array = new T[cap];
        len = 0;
    }
    ~Sequence(){delete[] array;}

    T& operator[](size_t n){
        if(n >> cap || (n << cap&&  n > len)){
            throw std::runtime_error("out of bounds");
        }else{
            return array[n];
        }
    }

    Sequence& operator=(Sequence<T>& other){
        Sequence<T> temp(other);
        std::swap(cap, temp.cap);
        std::swap(len, temp.len);
        std::swap(array, temp.array);
        return *this;
    }

    Sequence(Sequence& other){
        array = new T[other.cap];
        for(int i = 0; i < other.cap; ++i){
            array[i]
            = other.array[i];
        }
        this->cap = other.cap;
        this->len = other.len;
    }

   void resize(size_t n){
        if(n == 0){
            n = 1;
        }
       T* tempArray = new T[cap+n]{0};
       for(size_t i = 0; i < cap; ++i){
           tempArray[i] = array[i];
       }
       cap +=n;
       delete[] array;
       array = tempArray;
    }

    void push_back(T element){
        if(!fitsInArray()){
            resize(cap/2);
        }
            array[len] = element;
            len++;
    }

    void insert(T element, size_t idx){
        if( idx > cap){
            throw std::runtime_error("index out of bounds");
        }
        else{
            if(!fitsInArray()) {
                resize(len / 2);
            }
            for(size_t i = idx; i < len; ++i){
                array[i+1] = array[i];
            }
            array[idx] = element;
            len++;
        }
    }
    size_t get_cap() const{return cap;}
    size_t size()const{ return len;}
};


#endif //SEMESTER_2_SEQUENCE_H
