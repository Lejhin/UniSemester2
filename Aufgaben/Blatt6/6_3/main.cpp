//
// Created by Julius on 17.11.2022.
//
#include <vector>
#include "ooptool.h"
void BucketSort(std::vector<int>& a){
    int min = a.at(0);
    int max = a.at(0);
    //find min and Max value in array
    for(auto element: a){
        if(element < min){
            min = element;
        }
        if(element > max){
            max = element;
        }
    }

    std::vector<int> Array(max-min+1, 0);
    for(auto element: a){
        Array[element-min]+= 1;
    }
    a.clear();

    //push every element into the A vector with the offset of min
    for(int i = 0; i < Array.size() ; ++i){
        for(int j = 0; j < Array[i]; ++j){
            a.push_back(i+min);
        }
    }
}

int main(){
    check_sort(BucketSort, true, true, true);
}

