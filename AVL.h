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

    struct Node {
        int height;

        T *obj;

        Node *left;
        Node *right;
        //Node *parent;
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

    //--------------------------Rotations implementation--------------------------
    Node* rotateRight(Node* toRotate){  //TODO: Cover the case where toRotate is the root + not sure if parent field needed
        if(!toRotate || !toRotate->left)
            return toRotate;

        //Perform the Rotation
        Node *left = toRotate->left;

        if(left->right){
            Node *left_right = left->right;
            toRotate->left = left_right;
        }

        left->right = toRotate;

        //Adjust the height
        toRotate->height = max(toRotate->left->height, toRotate->right->height) + 1;
        left->height = max(left->left->height, left->right->height) + 1;

        //Return the new root of the subtree
        return left;
    }

    Node* rotateLeft(Node* toRotate){
        if(!toRotate || !toRotate->left)
            return toRotate;

        //Perform the Rotation
        Node *right = toRotate->right;

        if(right->left){
            Node *right_left = right->left;
            toRotate->right = right_left;
        }

        right->left = toRotate;

        //Adjust the height
        toRotate->height = max(toRotate->left->height, toRotate->right->height) + 1;
        right->height = max(right->left->height, right->right->height) + 1;

        //Return the new root of the subtree
        return right;
    }

    Node* RL(Node* toRotate) { //Not sure if any additional tests needed since basic rotation methods cover all the adge cases already
        if(toRotate){
            Node *right = toRotate->right;
            toRotate->right = rotateRight(right);
            return rotateLeft(toRotate);
        }
        return nullptr;
    }

    Node* LR(Node* toRotate){
        if(toRotate){
            Node* left = toRotate->left;
            toRotate->left = rotateLeft(left);
            return rotateRight(toRotate);
        }
        return nullptr;
    }

    //Note that RR and LL are rotateLeft and rotateRight respectively

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
