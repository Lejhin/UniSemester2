//
// Created by Julius on 24.11.2022.
//
#include <iostream>

template<typename T>
class sequence{
private:
    size_t len;
    size_t cap;
    T* array;

public:
    sequence(size_t cap): len(cap), cap(cap){
        array = new T[cap]{};
    }
    ~sequence(){delete[] array;}
    size_t getCap()const{return cap;}
    size_t size() const{return len;}

    T& operator[](size_t idx){
        return *(array+idx);
    }

    T operator[](size_t idx)const {
        return *(array+idx);
    }
    bool is_full(){return cap == len;}
    void remove(size_t idx);
    void insert(size_t idx, T ele);
    void push_back(T ele){ insert(len, ele);}
    void pop_back(){remove(len-1);}
};


//removing
template<typename T>
void sequence<T>::remove(size_t idx) {
    if(idx >= len){
        throw std::runtime_error("out of bound");
    }

    for(int i = idx; idx < len-1; ++i){
        array[i] = array[i+1];
    }
    len--;

}

template<typename T>
void sequence<T>::insert(size_t idx, T element) {
    if(is_full()){
        throw std::runtime_error("full");
    }
    if(idx > len) {
        throw std::runtime_error("out of bound");
    }
    for(size_t i = len; i > idx; --i){
        array[i] = array[i-1];
    }
    array[idx] = element;
    len++;
}

//printing
template<typename T>
void print(const sequence<T>& vec){
    std::cout<< "Size: " << vec.size() << "/" <<vec.getCap() << "Elemente: ";
    for(auto element: vec){std::cout << " " << element;}
    std::cout << std::endl;
}

int main(){
}