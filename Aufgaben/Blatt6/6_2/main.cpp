//
// Created by Julius on 16.11.2022.
//
#include <vector>
#include <iostream>
#include "ooptool.h"


void out(std::vector<int>& a){
    if(a.size() == 0){
        std::cout << " 0";
    }else{

        for(auto element: a){
            std::cout << " "<<element;
        }
    }
    std::cout << std::endl;
}


//eigene Lösung (aber ineffizient mit einem Faktor 10)
 void QuickSort(std::vector<int>& a){
    //nimmt nicht die Mitte des Vektors als Pivot, sondern den letzten index der momentanen Vektorinstanz
    // (Leichter in der Schleife zu verarbeiten da keine exceptions eingeworfen werden müssen)
   int Pivot = a.size()-1;
   std::vector<int> links;
   std::vector<int> rechts;

   if(a.size()> 1){
       for(int i = 0; i < Pivot; ++i){
           if(a[i] <= a[Pivot]){
               links.push_back(a[i]);
           }
           if(a[i] > a[Pivot]){
               rechts.push_back(a[i]);
           }
       }
       QuickSort(links);
       QuickSort(rechts);
   }else{
       return;
   }
   //cleared die Listenreferenz und pushed die nach links und rechts sortierten Vektoren auf die Liste;
   // der Pivot muss in die Mitte: kleiner Pivot - Pivot - größer Pivot
   a.clear();
   for(auto element: links){
       a.push_back(element);
   }
   a.push_back(a[Pivot]);
   for(auto element: rechts){
       a.push_back(element);
   }
}


//Skript Lösung:
void QuickSortSkript(std::vector<int>& a, size_t li, size_t re){
    if(li == re){
        return;
    }
    size_t start = li, end = re;
    size_t m = li+(re-li)/2;
    int pivot = a[m];
    do{
        while(a[li] <pivot){
            li++;
        }
        while(a[re] > pivot){
            re++;
        }
        if(li < re){
            swap(a, li++, re--);
        }else if(li == re){
            if(li == start ){
                li+=1;
            }else{
                re-=1;
            }
        }else{
        }
    }while(li <= re);
    QuickSortSkript(a, start, re);
    QuickSortSkript(a, li, end);
}



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
    //std::cout << "min: " << min << "    " << "max: "<< max << std::endl;
    std::vector<int> Array(max-min+1, 0);

      for(auto element: a){
          Array[element-min]+= 1;
      }

    /*for(int element: Array){
        std::cout << " " << element;
    }*/
    a.clear();

    for(int i = 0; i < Array.size() ; ++i){
        for(int j = 0; j < Array[i]; ++j){
            a.push_back(i+min);
        }
    }
}

int main() {


  /*  std::vector<int> a{1,2, -1};
    BucketSort(a);

    for (auto element: a) {
        std::cout << element << " ";

    }*/
     check_sort(BucketSort, true, true);
}