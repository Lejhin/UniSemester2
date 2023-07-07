#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

class Baum{
private:

    struct Node{ Node* left; int val; Node* right;};
    Node* root;

    void del(Node* n);
    int height(Node* n);
    void incOdd1(Node* n){
        if(n == nullptr){
            return;
        }
        if(n->val % 2 == 1){
            n->val++;
        }
        incOdd1(n->left);
        incOdd1(n->right);
    }
    void complete(Node* n, size_t height){
        if(n->left == nullptr && n->right == nullptr && height == 0){return;}
        if(n->left == nullptr){
            Node* Add = new Node{nullptr, 0, nullptr};
            n->left = Add;
        }
        if(n->right == nullptr){ 
            Node* Add = new Node{nullptr, 0, nullptr};
            n->right= Add;
        }
        complete(n->left, height--);
        complete(n->right, height--);
    }
public:
    Baum(): root(nullptr){}
    ~Baum() { del(root);}

    int height(){return height(root);}
    void incOdd1(){
        incOdd1(root);
    }
    void complete(){

        complete(root, height());
    }
};
