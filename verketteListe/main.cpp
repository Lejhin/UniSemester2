//
// Created by Julius on 01.12.2022.
//
#include "linked_list.h"
#include <vector>

class stack{
    Linked_list<int> stack;
public:
    void push(int ele){
        stack.insert(0, ele);
    }
    int pop(){
        int ret = stack[0];
        stack.remove((0));
        return ret;
    }
};
int main(){
    Linked_list<int> l;

    for(int i = 0; i < 10000; ++i){
        l.insert(0,i);
    }

    for(auto element: l){

    }
    for(Linked_list<int>::iterator curr = l.begin(); curr!= l.end(); ++curr){

        std::cout << *curr << std::endl;
    }

}
