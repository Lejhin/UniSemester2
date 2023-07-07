//
// Created by Julius on 21.12.2022.
//

#include <iostream>

class Baum{
private:
    struct Node{
        int val;
        Node* links;
        Node* rechts;
    };

    Node* root;

    void add_leave(Node*& target,int value){
        target = new Node;
        target->val = value;
        target->rechts = nullptr;
        target->links = nullptr;
    }

public:
    Baum(): root(nullptr){
    }
    Node* get_Node(const int& key){
        Node* n = root;
        Node* last = nullptr;
        while (n != nullptr) {
            if (key == n->val) {
                return last;
            } else if (key < n->val) {
                last = n;
                n = n->links;
            } else { // k > n->key
                last = n;
                n = n->rechts;
            }
        }
        return last;

    }

    void IncOdd1(){
        IncOdd1(root);
    }
    void IncOdd1(Node* n){
        if(n == nullptr){
            return;
        }
        IncOdd1(n->links);
        IncOdd1(n->rechts);
        if(n->val% 2 == 1){
            n->val +=1;
        }
    }

    void insert(size_t value){
        if(root == nullptr){
            add_leave(root, value);
            return;
        }

        Node* current = get_Node(value);
        if(value < current->val){
            add_leave(current->links,value);
        }else if(value > current->val){
            add_leave(current->rechts,value);
        }else{
            return;
        }


    }
    void print(Node* Node){
        if(Node == nullptr){
            return;
        }
        print(Node->links);
        std::cout << Node->val << std::endl;
        print(Node->rechts);
    }

    Node* begin(){return root;}
};



/*void inorder(node* n){
    if(n == nullptr){
        return;
    }
    inorder(n->links);
    std::cout << n->val;
    inorder(n->rechts);
}

char* suche(node* n, const char& i){
    if(n == nullptr){return nullptr;}
    if(i > n->val){return suche(n->rechts, i);}
    if(i < n->val){return suche(n->links, i);}
    if(i == n->val){return &n->val;}
}
*/

int main(){

    Baum Tree;
    for(int i = 0; i < 10; ++i){
        Tree.insert(rand() %  100);
    }
    Tree.IncOdd1();
    Tree.print(Tree.begin());



}
