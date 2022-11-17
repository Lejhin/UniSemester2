//
// Created by Julius on 16.11.2022.
//

#include <vector>
#include <iostream>
#include <bits/stdc++.h>
#include "ooptool.h"

void SelectionSort(std::vector<int>& a){
    Timer time;
    int SwapCount = 0;
    for(int i = 0; i < a.size()-1; ++i){
        size_t minPos = i;
        for(int j = i+1; j < a.size(); ++j){
            if(a[minPos] > a[j]){
                minPos = j;
            }
        }
        if(minPos != i){
            SwapCount++;
            std::swap(a[minPos], a[i]);
        }
    }
}

void InsertionSort(std::vector<int>& a){
    Timer time;
    int SwapCount = 0;

    for(int idx = 1; idx < a.size(); ++idx) {
        int j = idx;
        while((j > 0) && (a[j-1] > a[j])){
            SwapCount++;
            std::swap(a[j-1], a[j]);
            j--;
        }
    }

}


int main(){

//std::vector<int> a = create_randints(10,0,100);
    //SelectionSort(a);
    check_sort(SelectionSort, true);

}
