//
// Created by Julius on 07.12.2022.
//

#ifndef SEMESTER_2_LINKEDQUEUE_H
#define SEMESTER_2_LINKEDQUEUE_H

#include <iostream>
template<typename T>
class LinkedQueue{
private:
    struct Node{
        T element;
        Node* next;
    };
    Node* head;
    Node* tail;

public:
    LinkedQueue(){
        head = nullptr;
        tail = nullptr;
    }

    ~LinkedQueue(){
        while(head != nullptr){
            Node* next = head->next;
            delete head;
            head = next;
        }
    }



    void push(const T& element){
        Node* newNode = new Node;
        newNode->element = element;
        newNode->next = nullptr;
        if(head == nullptr){
            head = newNode;
            tail = newNode;
        }else{

            tail->next = newNode;
            tail = newNode;
        }
    }

    T pop(){
        if(head != nullptr){
            T& ElementToPop= head->element;
            Node* deleteItem = head;
            head = head->next;
            delete deleteItem;
            return ElementToPop;
        }else{
            throw std::runtime_error("nothing to pop out of queue");
        }
    }

    bool isEmpty(){if(head == nullptr){return true;}else{return false;}}

    size_t size(){
        size_t i = 0;
        Node* curr = head;
        while(curr!= nullptr){
            i++;
            curr = curr->next;
        }
        return i;
    }
};

#endif //SEMESTER_2_LINKEDQUEUE_H
