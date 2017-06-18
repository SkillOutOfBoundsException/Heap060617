#include <iostream>
#include "Lista.h"

using namespace std;

class Node{
    public:
        int data;
        Node* prev;
        Lista<Node*> *sons;
        Node(int x, int y){
            data = x;
            maxCant = y;
            prev = 0;
            sons = new Lista<Node*>();
        }

        void addNode(Node *newNode){
            //if(isFull())

        }

        int getHeight(){
            int highH = 0;
            for(int i = 0; i < sons->cant; i++){
                int sonH = sons->index(i)->getHeight();
                if(sonH > highH || i == 0)
                    highH = sonH;
            }
            return highH + 1;
        }

        int countLeaves(){
            return 0;
        }

        void printOrden(){

        }

    private:
        int maxCant;
        int getMax(int x, int y){
            return 0;
        }

        bool isFull(){
            return sons->cant >= maxCant;
        }
};

class Tree{
    public:
        int cant;
        Node* root;
        Tree(int x){
            cant = 0;
            root = 0;
            maxCant = x;
        }
        void add(int x){
            Node *newNode = new Node(x, maxCant);
            if(root == 0)
                root = newNode;
            else
                root->addNode(newNode);

            cant++;
        }

        Node* elim(int x){
            return 0;
        }

        void printOrden(){
            root->printOrden();
        }
    private:
        int maxCant;
        void fix(Node *node){
            if(node->prev == 0)
                return;
            if(node->data > node->prev->data){
                int tempP = node->prev->data;
                int tempN = node->data;
                node->prev->data = tempN;
                node->data = tempP;
                fix(node->prev);
            }
        }
};



int main(){
//    Tree *arbol = new Tree(2);
//    arbol->add(11);
//    arbol->add(5);
//    arbol->add(8);
//    arbol->add(3);
//    arbol->add(7);
//    arbol->add(4);
//    arbol->add(15);
//
//    arbol->printOrden();

    Lista<int>* rip = new Lista<int>();
    rip->pushBack(0);
    rip->pushBack(1);
    cout << rip->index(1) << endl;

    return 0;
}
