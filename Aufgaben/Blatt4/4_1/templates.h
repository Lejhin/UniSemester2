//
// Created by juliu on 27.10.2022.
//

#ifndef SEMESTER_2_TEMPLATES_H
#define SEMESTER_2_TEMPLATES_H
#include <iostream>
#include <cstring>



template<typename T>
T Max(T* array, size_t len){
    T maxIdx;
    for(int i = 0; i < len; ++i){
        if(*(array+i) > maxIdx){
            maxIdx = *(array+i);
        }
    }
    return maxIdx;
}

template<>
const char* Max<const char*>(const char** array, size_t _len){
   /*
    * gibt den längsten String zurück
    * const char** currentMaxidx = array;
    int tempCompare = 0;
    for(int i = 0; i < _len; ++i){
        if(std::strlen(*(array+i)) > tempCompare){

            tempCompare = std::strlen(*(array+i));
            currentMaxidx = array+i;
        }
    }
    return *currentMaxidx;*/

   // gibt den alphabestisch am größten string an (der am nächsten an Z)

   const char* currentMaxIdx = *array;

   for(int i = 0; i < _len; ++i){
       if(*(array+i) < currentMaxIdx){
           currentMaxIdx = *(array+i);
       }
   }
   return currentMaxIdx;

}



#endif //SEMESTER_2_TEMPLATES_H
