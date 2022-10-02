#include <iostream>
#include <cstdio>

void tausche (int& a, int& b){
    int h = a;
    a = b;
    b = h;

}
int main(){
    //CONST
    // const int a -> a ist konstant und darf nicht verändert werden
    // const int* p ist ein zeiger der auf eine Konstante zeigt und der wert darf auch nicht verändert werden
    // int* const p ist ein Zeiger der nicht verändert werden darf aber der wert darf geändert werden


    //REF
    int val = 10;
    int b = 5;
   
   // int*p = &val;
   // int& ref = val;
   //& kann als referenz benutzt werden;
    tausche(val,b)
;    

    std::cout << val << b << std::endl;







}