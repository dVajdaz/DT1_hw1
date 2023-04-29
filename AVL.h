//
// Created by Администратор on 29.04.2023.
//

#ifndef DS1_HW1_AVL_H
#define DS1_HW1_AVL_H

#include "wet1util.h"

template<class T>
class AVL {
private:
    //--------------------------Tree fields--------------------------
    int size;

    struct Node{
        int height;

        T* obj;

        Node* left;
        Node* right;
        Node* parent;
    };


    Node* root;
    Node* max_val;
    Node* min_val;

    //--------------------------Node operations--------------------------
    Node* initializeNode(const T& obj);

    Node* findNode(const T* toSearch, Node* subtree);
    Node* insertNode(const Node* toInsert, Node* subtree);
    Node* removeNode(const Node* toRemove, Node* subtree);

    Node* balanceNode(Node* toBalance);

    Node* getMinNode(Node* subtree) const;
    Node* getMaxNode(Node* subtree) const;

    int getNodeBalanceFactor(Node* subtree) const;
    int getNodeHeight(Node* subtree) const;

    //--------------------------Rotations--------------------------
    Node* rotateLeft(Node* toRotate);
    Node* rotateRight(Node* toRotate);
    Node* LL(Node* toRotate);
    Node* LR(Node* toRotate);
    Node* RR(Node* toRotate);
    Node* RL(Node* toRotate);

public:
    AVL();
    AVL(const AVL<T>& toCopy);

    ~AVL() = default; //TODO: custom implementation required

    //--------------------------Tree operations--------------------------
    void insert(const T& toInsert);
    void remove(const T& toRemove);

    void balance();

    int getHeight() const;
    //TODO: Might need preorder, postorder ... implementations

    //--------------------------Tree initiation implementation--------------------------
    template<class T>
    AVL<T>::AVL() : root(NULL), max_val(NULL), min_val(NULL), size(0) {}

    template<class T>
    AVL<T>::AVL(const AVL<T>& toCopy) : root(NULL), max_val(NULL), min_val(NULL), size(0){
        //TODO: custom by value copy implementation required (I guess)
    }

    //--------------------------Tree operations implementation--------------------------
    template<class T>
    void AVL<T>::insert(const T& toInsert){
        if(!toInsert)
            throw INVALID_INPUT;

        if(find(toInsert))
            throw INVALID_INPUT;

        Node* toInsertNode = initializeNode(toInsert);

        root = insertNode(toInsertNode, root);
        max_val = getMaxNode(root);
        min_val = getMinNode(root);
        size++;
    }

    template<class T>
    void AVL<T>::remove(const T& toRemove){
        if(!toRemove)
            throw INVALID_INPUT;

        if(!findNode(toRemove))
           return;

        root = removeNode(findNode(toRemove), root);
        max_val = getMaxNode(root);
        min_val = getMinNode(root);
        size--;
    }

    template<class T>
    void AVL<T>::balance(){
        root = balanceNode(root);
        max_val = getMaxNode(root);
        min_val = getMinNode(root);
    }

    template<class T>
    int AVL<T>::getHeight(){
        if(!root)
            return 0;

        return root->height;
    }

    //--------------------------Node operations implementation--------------------------
    template<class T>
    typename AVL<T>::Node* initializeNode(const T& obj){
        Node* newNode = new Node*();

        newNode->obj = new T(obj);

        newNode->right = nullptr;
        newNode->left = nullptr;

        newNode->height = 0; //not sure if it's 1 or 0

        return newNode;
    }

    template<class T>
    typename AVL<T>::Node* findNode(const T* toSearch, Node* subtree){
       if(!subtree)
           return nullptr;

       if(toSearch == *subtree->obj)
           return subtree;
       else if(toSearch > *subtree->obj){
           return findNode(toSearch, subtree->right);
       } else {
           return findNode(toSearch, subtree->left);
       }
    }

    template<class T>
    typename AVL<T>::Node* getMinNode(Node* subtree){
        if(!subtree)
            return nullptr;

        if(subtree->left)
            return getMinNode<T>(subtree->left);

        return subtree;
    }

    template<class T>
    typename AVL<T>::Node* getMaxNode(Node* subtree){
        if(!subtree)
            return nullptr;

        if(subtree->right)
            return getMaxNode<T>(subtree->right);

        return subtree;
    }







}

#endif
