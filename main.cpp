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

        bool addNode(Node *newNode, int x, int y){
            //cout << "Node " << data << " trying to add - " << newNode->data << " - couter is at " << x << endl;
            if(isOpen() && x != y){
                sons->pushBack(newNode);
                newNode->prev = this;
                return true;
            }
            else{
                for(int i = 0; i < sons->cant; i++){
                    if(sons->index(i)->addNode(newNode, x + 1, y))
                        return true;
                }
            }
            //cout << "Returning false " << endl;
            return false;
        }

        void addLeft(Node *newNode){
            //cout << "Adding to the left - " << newNode->data << endl;
            if(isOpen()){
                sons->pushBack(newNode);
            }
            else{
                sons->index(0)->addLeft(newNode);
            }
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
            //cout << "Node-" << data << " numer of sons ->" << sons->cant << endl;
            for(int i = 0; i < sons->cant; i++){
                sons->index(i)->printOrden();
            }
            cout << data << endl;
        }

    private:
        int maxCant;

        bool isOpen(){
            return sons->cant >= 0 && sons->cant < maxCant;
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
            else{
                if(!root->addNode(newNode, 0, root->getHeight() - 1))
                    root->addLeft(newNode);
            }
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
    Tree *arbol = new Tree(2);
    arbol->add(11);
    arbol->add(5);
    arbol->add(8);
    arbol->add(3);
    arbol->add(7);
    arbol->add(4);
    arbol->add(15);

    arbol->printOrden();

    //cout << arbol->root->data << endl;
    //cout << arbol->root->sons->index(0)->data << endl;
    //cout << arbol->root->sons->index(1)->data << endl;
    //cout << arbol->root->sons->index(0)->sons->index(0)->data << endl;



    return 0;
}
