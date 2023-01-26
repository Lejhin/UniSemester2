//
// Created by Julius on 01.12.2022.
//

#ifndef SEMESTER_2_LINKED_LIST_H
#define SEMESTER_2_LINKED_LIST_H
#include <iostream>
#include <stddef.h>

template<typename T>
class Linked_list {
private:
    struct Node {
        T element;
        Node *nextElement;
    };
    Node *_head;
public:
    class iterator {
        Node *curr;
    public:
        iterator(Node *c) : curr(c) {
        }

        bool operator!=(iterator other) {
            return curr != other.curr;
        }

        iterator &operator++() {
            curr = curr->nextElement;
            return *this;
        }

        T &operator*() {
            return curr->element;
        }
    };

    Linked_list() { //leere Liste
        _head = nullptr;
    }

    ~Linked_list() {
        while (_head != nullptr) {
            Node *next = _head->nextElement;
            delete _head;
            _head = next;
        }
    }

    void push_back(T element) {
        Node *curr = _head;
        while (curr->nextElement != nullptr) {
            curr = curr->nextElement;
        }
        Node *newNode = new Node;
        newNode->element = element;
        newNode->nextElement = curr->nextElement;
        curr->nextElement = newNode;
    }

    void insert(size_t idx, const T element) {
        if (idx == 0) {
            Node *newNode = new Node;
            newNode->element = element;
            newNode->nextElement = _head;
            _head = newNode;
        } else {
            Node *_curr = _head;
            for (int i = 0; i < idx - 1; ++i) {
                _curr = _curr->nextElement;
            }
            Node *newNode = new Node;
            newNode->element = element;
            newNode->nextElement = _curr->nextElement;
            _curr->nextElement = newNode;
        }
    }

    T &operator[](size_t idx) {
        Node *_current = _head;
        for (size_t i = 0; i < idx; ++i) {
            _current = _current->nextElement;
            if (_current == nullptr) {
                throw std::runtime_error("out of bounds");
            }
        }
        return _current->element;
    }

    void out() {
        Node *current = _head;
        while (current != nullptr) {
            std::cout << current->element << std::endl;
            current = current->nextElement;
        }
    }

    void remove(size_t idx) {
        if (idx >= size()) {
            throw std::runtime_error("out of bounds");
        }
        if (idx == 0) {
            Node *todel = _head;
            _head = _head->nextElement;
            delete todel;
            return;
        }
        size_t i = 0;
        Node *curr = _head;
        while (i < idx - 1) {
            i++;
            curr = curr->nextElement;
        }
        Node *todel = curr->nextElement;
        curr = curr->nextElement;
        delete todel;
        return;
    }


    size_t size() const{
        size_t ret = 0;
        Node* _curr = _head;

        while(_curr != nullptr){
            _curr = _curr->nextElement;
            ret+=1;
        }
        return ret;
    }
    iterator begin()const {return _head;}
    iterator end()const{return nullptr;}
};
#endif //SEMESTER_2_LINKED_LIST_H
