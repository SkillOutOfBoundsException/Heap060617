#include <iostream>
#include "Lista.h"

using namespace std;

//by Diego Montes
//special thanks to La Salsa

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
            return false;
        }

        void addLeft(Node *newNode){
            if(isOpen()){
                sons->pushBack(newNode);
                newNode->prev = this;
            }
            else{
                sons->index(0)->addLeft(newNode);
            }
        }

        Node* getLast(){
            if(sons->cant == 0)
                return this;
            int sonI = 0;
            int highH = 0;
            for(int i = 0; i < sons->cant; i++){
                int sonH = sons->index(i)->getHeight();
                if(sonH >= highH || i == 0){
                    highH = sonH;
                    sonI = i;
                }
            }
            return sons->index(sonI)->getLast();
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

        void fix(){
            if(sons->cant == 0)
                return;
            int dataH = 0;
            int sonI = 0;
            for(int i = 0; i < sons->cant; i++){
                int sonH = sons->index(i)->data;
                if(sonH > dataH || i == 0){
                    dataH = sonH;
                    sonI = i;
                }
            }
            Node* son = sons->index(sonI);
            int tempD = data;
            int tempS = son->data;
            if(tempD >= tempS)
                return;
            data = tempS;
            son->data = tempD;
            son->fix();
        }

        int countLeaves(){
            return 0;
        }

        void printOrden(){
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
            fix(newNode);
            cant++;
        }

        int elim(){
            if(root == 0)
                return 0;
            if(cant == 1){
                cant--;
                int data = root->data;int highH = 0;
            for(int i = 0; i < sons->cant; i++){
                int sonH = sons->index(i)->getHeight();
                if(sonH > highH || i == 0)
                    highH = sonH;
            }
                root = 0;
                return data;
            }
            Node *temp = root->getLast();
            int tempR = root->data;
            int tempT = temp->data;
            root->data = tempT;
            temp->data = tempR;
            temp->prev->sons->popBack();
            temp->prev = 0;
            root->fix();
            cant--;
            return temp->data;

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

    cout << arbol->elim() << endl;

    arbol->add(9);
    arbol->printOrden();

    //cout << arbol->root->data << endl;
    //cout << arbol->root->sons->index(0)->data << endl;
    //cout << arbol->root->sons->index(1)->data << endl;
    //cout << arbol->root->sons->index(0)->sons->index(0)->data << endl;



    return 0;
}
