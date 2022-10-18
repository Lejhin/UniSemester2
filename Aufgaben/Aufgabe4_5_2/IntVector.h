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
	IntVector(int *array, size_t len);
	IntVector& operator=(const IntVector& newVec);
	int& operator[] (const int idx);
	IntVector(size_t len);
	~IntVector();
	int& at(size_t idk);
	void out()const;
	size_t size()const;



};



#endif /* INTVECTOR_H_ */
