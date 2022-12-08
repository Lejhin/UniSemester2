/*
 * IntVector.h
 *
 *  Created on: 06.10.2022
 *      Author: n2210657
 */

#ifndef INTVECTOR_H_
#define INTVECTOR_H_

#include <vector>
#include <iostream>



class IntVector{

private:
	int* array;
	size_t len;


public:
    class iterator{
    private:
        int* current;
    public:
        iterator(int* current): current(current){
        }
        bool operator!=(iterator other){
            return current != other.current;
        }
        iterator& operator++(){
            current ++;
            return *this;
        }
        int& operator*(){
            return *current;
        }

    };
	IntVector(int *array, size_t len);
	IntVector& operator=(const IntVector& newVec);
	int& operator[] (const int idx);
	IntVector(size_t len = 10000);
	~IntVector();
	int& at(size_t idk);
	void out()const;
	size_t size()const;
    int* begin(){return array;}
    int* end(){return array+len;}


};



#endif /* INTVECTOR_H_ */
