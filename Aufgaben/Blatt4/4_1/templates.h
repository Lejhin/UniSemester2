//
// Created by juliu on 27.10.2022.
//

#ifndef SEMESTER_2_TEMPLATES_H
#define SEMESTER_2_TEMPLATES_H

template<typename T>
T Max(T array, unsigned int len){
    T currentMax;
    for(int i = 0; i < len; ++i){
        if(*(array+i) > *currentMax){
            *(array+i) = currentMax;
        }
    }
    return *currentMax;
}

#endif //SEMESTER_2_TEMPLATES_H
