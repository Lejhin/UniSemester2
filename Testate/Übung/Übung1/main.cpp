//
// Created by Julius on 10.01.2023.
//
#include <iostream>
class LinkedList{
private:
    struct Node{
        int element;
        Node* next;
        Node* previous;
    };
    Node* tail;
    Node* root;

public:
    class iterator{
    private:
        Node* current;
    public:
        iterator(Node* cu): current(cu){}
        bool operator!=(iterator other){
            return current != other.current;
        }
        iterator& operator++(){
            current = current->next;
            return *this;
        }
        int& operator*(){
            return current->element;
        }
    };
    LinkedList(size_t length){
        root = nullptr;
        tail = nullptr;
        for(int i = 0; i < length; ++i){
            if(i == 0){
                Node* newNode = new Node;
                newNode->element = 0;
                newNode->next = nullptr;
                newNode->previous = tail;
                root = newNode;
                tail = newNode;
            }
            Node* newNode = new Node;
            newNode->element = 0;
            newNode->previous= tail;
            newNode->next = nullptr;
            tail = newNode;
        }
    }
    LinkedList(): root(nullptr), tail(nullptr){
    }

    void append(int item){
        Node* newNode = new Node;
        newNode->element = item;
        newNode->next = nullptr;
        newNode->previous = tail;
        if(root == nullptr && tail == nullptr){
            root = newNode;
            tail = newNode;
        }else{
            tail->next = newNode;
            tail = newNode;
        }
        std::cout << "appended: " << item << std::endl;
    }
    ~LinkedList(){
        Node* current = root;
        while(current->next!= nullptr){
            current = current->next;
            delete root;
            root = current;
        }

    }

    void pop(){
        if(tail != nullptr){
            Node* newTailNode = tail;
            tail = tail->previous;
            tail->next = nullptr;
            delete newTailNode;
        }else{
            std::cout << "nothing to pop" << std::endl;
        }
    }

    int& operator[](size_t index){
        Node* current = root;
        for(int i = 0; i < index;++i){
            if(current == nullptr){
                std::runtime_error("index out of bounds");
            }
            current= current->next;
        }
        return current->element;
    }

    iterator begin() const{return iterator(root);}
    iterator end() const{return iterator(nullptr);}
};

void print(LinkedList& Liste){
    for(auto element: Liste){
        std::cout << element << std::endl;
    }
}

int main(){
    LinkedList Liste;
    Liste.append(2);
    Liste.append(3);
    Liste.append(4);
    Liste.append(1);
    print(Liste);

    Liste.pop();
    std::cout << std::endl;
    print(Liste);


}