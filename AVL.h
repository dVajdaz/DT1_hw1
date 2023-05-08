//
// Created by Администратор on 29.04.2023.
//

#ifndef DS1_HW1_AVL_H
#define DS1_HW1_AVL_H

#include "wet1util.h"
#include "math.h"

template<class T>
class AVL {
public:
    //--------------------------Tree fields--------------------------
    int size;

    struct Node {
        int height;

        T *obj;

        Node *left;
        Node *right;

    };


    Node *root;

    //--------------------------Node operations--------------------------
    Node *initializeNode(const T &obj);

    Node *findNode(const T *toSearch, Node *subtree);

    Node *insertNode(const Node *toInsert, Node *root);

    //TODO: Remember to free toRemove
    Node *removeNode(Node *toRemove, Node *root);


    int getNodeBalanceFactor(Node *subtree) const;

    int getNodeHeight(Node *subtree) const;

    //--------------------------Rotations--------------------------
    Node *rotateLeft(Node *toRotate);

    Node *rotateRight(Node *toRotate);

    Node *LL(Node *toRotate);

    Node *LR(Node *toRotate);

    Node *RR(Node *toRotate);

    Node *RL(Node *toRotate);

    Node *findParent(const T &toSearch, Node *subtree);

    Node *findPrevNode(const T &toSearch, Node *subtree);

    int BF(Node* subtree);

    bool isLeaf(Node *node);

    bool hasOneSon(Node *node);

    void swap(Node *n1, Node *n2);

    void removeLeft(Node *toRemove, Node *parent);

    void removeRight(Node *toRemove, Node *parent);

    AVL();

    AVL(const AVL<T> &toCopy);

    ~AVL() = default; //TODO: custom implementation required

    //--------------------------Tree operations--------------------------
    void insert(const T &toInsert);

    void remove(const T &toRemove);
    //TODO: Might need preorder, postorder ... implementations

    //--------------------------Tree initiation implementation--------------------------

};
    //--------------------------Tree operations implementation--------------------------
    template<class T>
    AVL<T>::AVL() : root(NULL),  size(0) {}

    template<class T>
    AVL<T>::AVL(const AVL<T> &toCopy) : root(NULL),size(0) {
        //TODO: custom by value copy implementation required (I guess)
    }
    template<class T>
    void AVL<T>::insert(const T& toInsert){
        if(!toInsert)
            throw StatusType::INVALID_INPUT;

        if(find(toInsert))
            throw StatusType::INVALID_INPUT;

        Node* toInsertNode = initializeNode(toInsert);

        root = insertNode(toInsertNode, root);
        /*
        max_val = getMaxNode(root);
        min_val = getMinNode(root);*/
        size++;
    }

    template<class T>
    void AVL<T>::remove(const T& toRemove){
        if(!toRemove)
            throw StatusType::INVALID_INPUT;

        if(!findNode(toRemove))
           return;

        root = removeNode(findNode(toRemove), root);
        /*
        max_val = getMaxNode(root);
        min_val = getMinNode(root);*/
        size--;
    }



    //--------------------------Rotations implementation--------------------------
    template<class T>
    typename AVL<T>::Node*
    AVL<T>::rotateRight(Node* toRotate){  //TODO: Cover the case where toRotate is the root + not sure if parent field needed
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
    template<class T>
    typename AVL<T>::Node*
    AVL<T>::rotateLeft(Node* toRotate){
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
    template<class T>
    typename AVL<T>::Node*
    AVL<T>::RL(Node* toRotate) { //Not sure if any additional tests needed since basic rotation methods cover all the adge cases already
        if(toRotate){
            Node *right = toRotate->right;
            toRotate->right = rotateRight(right);
            return rotateLeft(toRotate);
        }
        return nullptr;
    }
    template<class T>
    typename AVL<T>::Node*
    AVL<T>::LR(Node* toRotate){
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
    typename AVL<T>::Node* AVL<T>::initializeNode(const T& obj){
        Node* newNode = new Node*();

        newNode->obj = new T(obj);

        newNode->right = nullptr;
        newNode->left = nullptr;

        newNode->height = 0; //not sure if it's 1 or 0

        return newNode;
    }

    template<class T>
    typename AVL<T>::Node* AVL<T>::findNode(const T* toSearch, Node* subtree){
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
    typename AVL<T>::Node* AVL<T>::findParent(const T& toSearch, Node* subtree){

        if((*subtree->right != nullptr && *subtree->right->obj == toSearch)
        || (*subtree->left != nullptr && *subtree->left->obj == toSearch)) { return subtree;}

        else if(toSearch > *subtree->obj){
            return findNode(toSearch, subtree->right);
        } else {
            return findNode(toSearch, subtree->left);
        }
    }

    /**
     *
     * @param toSearch The value of the node
     * @param subtree A pointer to the root of the AVL tree. We assume that the tree isn't empty, and that it is
     * an ordered AVL tree.
     * @return a pointer to the node which would be the parent of a Node with the value toSearch,
     * if that node were to be inserted into the tree
     */
    template<class T>
    typename AVL<T>::Node* AVL<T>::findPrevNode(const T& toSearch, Node* subtree){

        if(*subtree->obj < toSearch && subtree->left == nullptr) { return subtree;}

        if(*subtree->obj > toSearch && subtree->right == nullptr) { return subtree;}
        else if(toSearch > *subtree->obj){
            return findNode(toSearch, subtree->right);
        } else {
            return findNode(toSearch, subtree->left);
        }
    }
    template<class T>
    int AVL<T>::BF(Node* subtree) {
        int right_height;
        if(subtree->right == nullptr) {
            right_height = -1;
            if(subtree->left == nullptr) {
                return 0;
            }
            return subtree->left->height - right_height;
        }
        return subtree->left->height - subtree->right->height;


    }
    template<class T>
    typename AVL<T>::Node* AVL<T>::insertNode(const Node* toInsert, Node* root) {
        //Finding the node that should be toInsert's parent
        Node* parent = findPrevNode(toInsert->obj, root);
        //Checking whether toInsert should be the left child or the right child and inserting him accordingly
        if(parent->obj < toInsert->obj) { parent->left = toInsert;}
        else { parent->right = toInsert; }
        //Checking the balance of the tree and rotating if needed
        while(toInsert != root) {
            //Checking if the parent's height has changed
            if(parent->height > toInsert->height) { return root;}
            //Updating the parent's height
            parent->height = toInsert->height + 1;
            //Checking for rotations
            if(BF(parent) == 2 || BF(parent) == -2) {
                if(BF(parent) == 2) {
                    if(BF(toInsert) >= 0) {return LL(parent);}
                    return LR(parent);
                }
                if(BF(toInsert) <=0) {return RR(parent);}
                return RL(parent);
            }
            parent = findParent(toInsert->obj, root);
        }

    }
    template<class T>
    bool AVL<T>::isLeaf(Node* node) {
        return node->left == nullptr && node->right == nullptr;
    }
    template<class T>
    bool AVL<T>::hasOneSon(Node* node) {
        return (node->left == nullptr && node->right != nullptr) ||
                (node->left != nullptr && node->right == nullptr);
    }
    template<class T>
    void AVL<T>::swap(Node* n1, Node* n2) {
        T temp = *n1->obj;
        *n1->obj = *n2->obj;
        *n2->obj = temp;
    }
    //TODO: Combine removeLeft and removeRight
    template<class T>
    void AVL<T>::removeLeft(Node* toRemove, Node* parent) {
        if(isLeaf(toRemove)) {
            parent->left = nullptr;
            free(toRemove); //TODO: Change from free to delete
        }
        else if(hasOneSon(toRemove)) {
            if(toRemove->right == nullptr) {
                parent->left = toRemove->left;
            }
            else {
                parent->left = toRemove->right;

            }
            free(toRemove);
        }
        else {
            Node* nextInOrder = toRemove->right;
            while(nextInOrder->left != nullptr) { nextInOrder = nextInOrder->left;}
            swap(nextInOrder, toRemove);
            parent = findParent(nextInOrder);
            removeLeft(nextInOrder, parent);
        }


    }
    template<class T>
    void AVL<T>::removeRight(Node* toRemove, Node* parent) {
        if(isLeaf(toRemove)) {
            parent->right = nullptr;
            free(toRemove);
        }
        else if(hasOneSon(toRemove)) {
            if(toRemove->right == nullptr) {
                parent->right = toRemove->left;
            }
            else {
                parent->right = toRemove->right;

            }
            free(toRemove);
        }
        //TODO: fix this removal
        else {
            Node* nextInOrder = toRemove->right;
            while(nextInOrder->left != nullptr) { nextInOrder = nextInOrder->left;}
            swap(nextInOrder, toRemove);
            parent = findParent(nextInOrder);
            removeLeft(nextInOrder, parent);
        }


    }
    template<class T>
    typename AVL<T>::Node* AVL<T>::removeNode(Node* toRemove, Node* root) {
        //TODO: Check the case where toRemove is the root.

        Node* parent = findParent(toRemove);
        if(parent->left == toRemove) {
            removeLeft(toRemove, parent);
        }
        else { removeRight(toRemove, parent); }
        while (parent != root) {
            parent->height = 1 + max(parent->right, parent->left);
            if(abs(BF(parent)) == 2) {
                if(BF(parent) == 2) {
                    if(BF(toRemove) >= 0) {return LL(parent);}
                    return LR(parent);
                }
                if(BF(toRemove) <=0) {return RR(parent);}
                return RL(parent);
            }
        }
    }


#endif

