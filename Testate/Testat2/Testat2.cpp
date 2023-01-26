//
// Created by Julius on 11.01.2023.
//
#include <iostream>
class LinkedList{
private:
    struct Node{
        int element;
        Node* next;
    };
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

    LinkedList(): root(nullptr){
    }

    void append(int item){
        Node* newNode = new Node;
        newNode->element = item;
        newNode->next = nullptr;
        Node* current = root;
        if(root == nullptr){
            root = newNode;
        }else{
            while(current != nullptr){
                if(current->next == nullptr){
                    current->next = newNode;
                    break;
                }
                current = current->next;
            }


        }
    }
    ~LinkedList(){
        Node* current = root;
        while(current->next!= nullptr){
            current = current->next;
            delete root;
            root = current;
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

    size_t OddCount(){
        int OddCount = 0;
        Node* current = root;
        while(current != nullptr){
            if(current->element%2){
                OddCount++;
            }
            current = current->next;
        }
        return OddCount;
    }
    int* first_Odd(){
        if(OddCount() == 0){
            throw std::runtime_error("no Odd number");
        }
        Node* current = root;
        while(current != nullptr){
            current = current->next;
            if(current->element&2){
                return &current->element;
            }
        }

        std::runtime_error( "no Odd number");
        return nullptr;
    }
    int* last_Odd(){
        if(OddCount() == 0){
            throw std::runtime_error("no Odd number");
        }
        Node* lastOdd = nullptr;
        Node* current = root;
        while(current != nullptr){
            if(current->element %2 == 1){
                lastOdd = current;
            }
            current = current->next;
        }
            if(lastOdd == nullptr){
                return nullptr;
            }else{
                return &lastOdd->element;

            }

    }
    bool delete_first(){
        Node* current = root;
        Node* last = root;
        if(OddCount() >= 1){
            while (current->element%2 == 0){
                last = current;
                current= current->next;
                if(current == nullptr){
                    return false;
                }
            }
            if(current == root){
                delete root;
                root = current->next;
            }else{
                last->next = last->next->next;
                delete current;

            }

        }
        return true;

    }
    bool delete_last(){
        if(OddCount() >= 1){
            Node* current = root;
            Node* Odd = nullptr;
            Node* oddBefore = nullptr;
            Node* last = nullptr;
            while(current != nullptr){
                if(current->element%2){
                    oddBefore = last;
                    Odd = current;
                }
                last = current;
                current = current->next;
            }
            oddBefore->next = oddBefore->next->next;
            delete Odd;
            return true;


        }else{
            return false;
        }


    }
    void delete_all(){
        Node* current = root;
        while(current != nullptr){
            delete_first();
            current = current->next;
        }
    }
};

int main(){
    LinkedList Liste;
    Liste.append(2);
    Liste.append(3);
    Liste.append(4);
    Liste.append(7);
    Liste.append(9);
    Liste.append(10);


    for(auto element:Liste){
        std::cout << element << std::endl;
    }


    std::cout << Liste.OddCount() << "  " << *Liste.first_Odd() << "    " << *Liste.last_Odd() << " "<<std::endl;

}



