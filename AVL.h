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
    int size; //Number of Nodes in the tree

    /** A struct representing a single node in the tree
     * height - the height of the subtree whose root is the current node. A single node's height is set to 0,
     * while an empty node's height is -1
     * obj - A pointer to the value contained inside the node
     * left - A pointer to the nodes' left son
     * right - A pointer to the nodes' right son
     * parent - A pointer to the nodes' parent
     */
    struct Node {
        int height;

        T *obj;

        Node *left;
        Node *right;
        Node *parent;
    };

    Node *max_node = nullptr; //A pointer to the node containing the largest value in the tree
    Node *root; //A pointer to the root of the current tree

    //--------------------------Node operations--------------------------
    /**
     * Initializes a new node with the given value
     * @param obj - A value of type T
     * @return A pointer to a new Node which contains a pointer to obj
     */
    Node *initializeNode(const T &obj);

    /**
     * Receives a value to search in the tree, and the tree's root. Finds the
     * node containing the given value in the tree
     * @param toSearch a value to search in the tree
     * @param subtree the tree's root
     * @return a pointer to the node containing the given value. If there's no such node,
     * the method whill return nullptr
     */
    Node *findNode(const T& toSearch, Node *subtree);

    /**
     *
     * @param toInsert A pointer to a node which we want to insert into the current tree
     * @param root The tree's root
     * @return A pointer to the root of the tree with the inserted Node in the correct position
     */
    Node *insertNode(Node *toInsert, Node *root);

    /**
     *
     * @param toRemove A pointer to a node which we want to remove from the current tree
     * @param root The tree's root
     * @return A pointer to the root of the tree with the removed Node no longer present
     */
    Node *removeNode(Node *toRemove, Node *root);

    /**
     * Balances the tree after insertion by performing a rotation if necessary and
     * updating heights along the insertion path
     * @param toInsert - the Node which was inserted into the tree
     * @param parent  - the Inserted node's parent
     * @param root - the root of the tree
     * @return - the root of the new tree, with toInsert present and the tree balanced
     */
    Node *doInsertRotation(Node *toInsert, Node *parent, Node *root);


    Node *doRemoveRotation(Node* parent, Node* root);

    int getNodeHeight(Node *subtree) const;

    //--------------------------Rotations--------------------------
    /**
     * Receives a node to rotate and performs a RR rotation on him
     * @param toRotate The node which we wish to rotate
     * @return a pointer to the new root of the subtree, following the rotation
     */
    Node *rotateLeft(Node *toRotate);

    /**
     * Receives a node to rotate and performs a LL rotation on him
     * @param toRotate The node which we wish to rotate
     * @return a pointer to the new root of the subtree, following the rotation
     */
    Node *rotateRight(Node *toRotate);


    Node *LL(Node *toRotate);

    Node *LR(Node *toRotate);

    Node *RL(Node *toRotate);

    /**
     *
     * @param toSearch a value of type T
     * @param subtree the root of the tree
     * @return If toSearch is stored in the root, the method returns the root.
     * If toSearch exists in the tree, the method returns a pointer to the parent of the Node in which
     * toSearch is stored.
     * Else, the method returns a pointer to the Node which would be the parent of the Node storing toSearch, had it
     * been in the tree
     */
    Node *findParent(const T &toSearch, Node *subtree);


    /**
     * Returns the Balance factor of a given node, which is defind as (left_son->height - right_son->height)
     * @param subtree a Node
     * @return the Balance factor of subtree
     */
    int BF(Node* subtree);

    /**
     *
     * @param node a given Node
     * @return True if node is a leaf, i.e. node has no sons. False otherwise
     */
    bool isLeaf(Node *node);

    /**
     *
     * @param node a given Node
     * @return True if node has either a right son or a left son but not both. False otherwise
     */
    bool hasOneSon(Node *node);

    /**
     * Swaps between the values stored in 2 given Nodes
     * @param n1 - a Node
     * @param n2 - a Node
     */
    void swap(Node *n1, Node *n2);

    /**
     * Receives a node to remove from the tree and removes it according to the
     * Binary Search Tree node removal algorithm
     * @param toRemove - the node to remove
     * @param parent - the nodes' parent
     * @param root - the root of the tree
     */
    void removeBST(Node *toRemove, Node* &parent, Node*& root);

    /**
     * Receives the root of the tree and removes it
     * @param root - the root of the tree
     */
    void removeRoot(Node* root, Node*& realRoot, Node*& myParent);


    AVL();

    AVL(const AVL<T> &toCopy) = default;

    ~AVL(); //TODO: custom implementation required

    void destroy(Node* root);

    /**
     * Receives a Node in the tree and updates its height
     * @param toUpdate - a Node
     */
    void updateHeight(Node* toUpdate);

    //--------------------------Tree operations--------------------------
    /**
     * Receives a value to insert into the tree and does so, while maintaining
     * the tree's balance
     * @param toInsert - a value to insert into the tree
     */
    T* insert(const T &toInsert);

    /**
     * Receives a value to remove from the tree and does so, while maintaining
     * the tree's balance
     * @param toRemove - a value to remove from the tree
     */
    T* remove(const T &toRemove);

    /**
     * Prints the values stored in the tree in postorder
     * @param root the root of the tree
     */
    void printPostOrder(Node* root, int*& output);

    T* find(T* toFind);
    //--------------------------Tree initiation implementation--------------------------

};
    //--------------------------Tree operations implementation--------------------------
    template<class T>
    AVL<T>::AVL() : root(NULL),  size(0) {}


    template<class T>
    T* AVL<T>::insert(const T& toInsert){ //TODO: Return a pointer to the inserted object (T* return type)
        if(&toInsert == NULL)
            return nullptr; //TODO: change to return pointer
        //If the tree is empty
        if(!this->root) {
            root = initializeNode(toInsert);
            max_node = initializeNode(toInsert);
            size++;
            return root->obj;
        }

        if (findNode(toInsert, root))
            return nullptr;

        Node *toInsertNode = initializeNode(toInsert);
        root = insertNode(toInsertNode, root);

        if( *max_node->obj < toInsert) {
            *max_node->obj = toInsert;
        }
        /*
        max_val = getMaxNode(root);
        min_val = getMinNode(root);*/
        size++;
        return toInsertNode->obj;
    }

    template<class T>
    T* AVL<T>::remove(const T& toRemove){ //TODO: Return a pointer to the deleted object
        if(&toRemove == NULL)
            return nullptr;

        if(!findNode(toRemove, root) || !root)
           return nullptr;
        Node* removed = findNode(toRemove, root);
        root = removeNode(removed, root);
        if(*max_node->obj == *removed->obj) {
            Node* tmp = root;
            if(!tmp) {
                delete max_node;
                max_node = nullptr;
            }
            else {
                while (tmp->right) tmp = tmp->right;
                *max_node->obj = *tmp->obj;
            }
        }
        /*
        max_val = getMaxNode(root);
        min_val = getMinNode(root);*/
        size--;
        return removed->obj;
    }

    template<class T>
    void AVL<T>::updateHeight(Node* toUpdate) {
        if(isLeaf(toUpdate)) {
            toUpdate->height = 0;
        }
        else if(toUpdate->right && toUpdate->left) {
            toUpdate->height = 1+ std::max(toUpdate->right->height, toUpdate->left->height);
        }
        else if(toUpdate->left) {
            toUpdate->height = toUpdate->left->height + 1;
        }
        else if(toUpdate->right) {
            toUpdate->height = toUpdate->right->height + 1;
        }

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
            left_right->parent = toRotate;
        }
        toRotate->left = left->right;
        left->right = toRotate;
        left->parent = toRotate->parent;
        toRotate->parent = left;

        //Adjust the height
        updateHeight(toRotate);
        updateHeight(left);

        //Return the new root of the subtree
        return left;
    }
    template<class T>
    typename AVL<T>::Node*
    AVL<T>::rotateLeft(Node* toRotate){
        if(!toRotate || !toRotate->right)
            return toRotate;

        //Perform the Rotation
        Node *right = toRotate->right;

        if(right->left){
            Node *right_left = right->left;
            toRotate->right = right_left;
            right_left->parent = toRotate;
        }
        toRotate->right = right->left;
        right->left = toRotate;
        right->parent = toRotate->parent;
        toRotate->parent = right;

        //Adjust the height
        updateHeight(toRotate);
        updateHeight(right);

        //Return the new root of the subtree
        return right;
    }
    template<class T>
    typename AVL<T>::Node*
    AVL<T>::RL(Node* toRotate) { //Not sure if any additional tests needed since basic rotation methods cover all the edge cases already
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
        Node* newNode = new Node();

        newNode->obj = new T(obj);

        newNode->right = nullptr;
        newNode->left = nullptr;
        newNode->parent = nullptr;
        newNode->height = 0;

        return newNode;
    }

    template<class T>
    typename AVL<T>::Node* AVL<T>::findNode(const T& toSearch, Node* subtree){
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
        if(*subtree->obj == toSearch) {
            return subtree;
        }
        if((subtree->right != nullptr && *subtree->right->obj == toSearch)
        || (subtree->left != nullptr && *subtree->left->obj == toSearch)) { return subtree;}

        else if(toSearch > *subtree->obj){
            if(subtree->right == nullptr)
                return subtree;
            return findParent(toSearch, subtree->right);
        } else {
            if(subtree->left == nullptr)
                return subtree;
            return findParent(toSearch, subtree->left);
        }
    }

    /**
     *
     * @param toSearch The value of the node
     * @param subtree A pointer to the root of the AVL tree. We assume that the tree isn't empty, and that it is
     * an ordered AVL tree.
     * @return a pointer to the node which would be the parent of a Node with the value toSearch,
     * if that node were to be inserted into the tree

    template<class T>
    typename AVL<T>::Node* AVL<T>::findPrevNode(const T& toSearch, Node* subtree){

        if(*subtree->obj < toSearch && subtree->left == nullptr) { return subtree;}

        if(*subtree->obj > toSearch && subtree->right == nullptr) { return subtree;}
        else if(toSearch > *subtree->obj){
            return findNode(toSearch, subtree->right);
        } else {
            return findNode(toSearch, subtree->left);
        }
    } **/
    template<class T>
    int AVL<T>::BF(Node* subtree) {
        int right_height, left_height;
        if(subtree->right == nullptr) {
            right_height = -1;

        }
        else { right_height = subtree->right->height;}
        if(subtree->left == nullptr) {
            left_height = -1;

        }
        else { left_height = subtree->left->height;}
        return left_height - right_height;
    }
    template<class T>
    typename AVL<T>::Node* AVL<T>::insertNode(Node* toInsert, Node* root) {
        //Finding the node that should be toInsert's parent
        Node* parent = findParent(*toInsert->obj, root);
        //Checking whether toInsert should be the left child or the right child and inserting him accordingly
        if(*parent->obj < *toInsert->obj) { parent->right = toInsert;}
        else { parent->left = toInsert; }
        toInsert->parent = parent;

        //Checking the balance of the tree and rotating if needed
        return doInsertRotation(toInsert, parent, root);
    }

    template<class T>
    typename AVL<T>::Node* AVL<T>::doInsertRotation(Node *toInsert, Node *parent, Node *root) {
        Node* parentOfUnbalanced = nullptr;
        while(toInsert != root) {
            //Checking if the parent's height has changed
            if(parent->height > toInsert->height) { return root;}
            //Updating the parent's height
            parent->height = toInsert->height + 1;
            //Checking for rotations
            if(BF(parent) == 2 || BF(parent) == -2) {
                if(BF(parent) == 2) {
                    if (parent->left && BF(parent->left) >= 0) {
                        if (parent == root)
                            return rotateRight(parent);
                        else {
                            parentOfUnbalanced = parent->parent;
                            if (parentOfUnbalanced->left == parent) {
                                parentOfUnbalanced->left = rotateRight(parent);
                            } else { parentOfUnbalanced->right = rotateRight(parent); }
                        }
                    } else {
                        if(parent == root)
                            return LR(parent);
                        else {
                            parentOfUnbalanced = parent->parent;
                            if (parentOfUnbalanced->left == parent) {
                                parentOfUnbalanced->left = LR(parent);
                            } else { parentOfUnbalanced->right = LR(parent); }
                        }

                    }
                }
                else {
                    if (parent->right && BF(parent->right) <= 0) {
                        if (parent == root)
                            return rotateLeft(parent);
                        else {
                            parentOfUnbalanced = parent->parent;
                            if (parentOfUnbalanced->left == parent) {
                                parentOfUnbalanced->left = rotateLeft(parent);
                            } else { parentOfUnbalanced->right = rotateLeft(parent); }
                        }
                    }
                    else
                    {
                        if(parent == root)
                            return RL(parent);
                        else {
                            parentOfUnbalanced = parent->parent;
                            if (parentOfUnbalanced->left == parent) {
                                parentOfUnbalanced->left = RL(parent);
                            } else { parentOfUnbalanced->right = RL(parent); }
                        }

                    }
                }
                return root;
            }
            toInsert = parent;
            parent = parent->parent;
        }
        return root;
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
    template<class T>
    void AVL<T>::removeBST(Node* toRemove, Node*& parent, Node*& root) {
        if(toRemove == root) {
            removeRoot(root, root, parent);
        }
        else if(isLeaf(toRemove)) {
            if(parent->left == toRemove) {
                parent->left = nullptr;

            }
            else {
                parent->right = nullptr;

            }
            //delete toRemove;
        }
        else if(hasOneSon(toRemove)) {
            if(parent->left == toRemove) {
                if (toRemove->right == nullptr) {
                    parent->left = toRemove->left;
                    toRemove->left->parent = parent;
                } else {
                    parent->left = toRemove->right;
                    toRemove->right->parent = parent;
                }
            }
            else {
                if (toRemove->right == nullptr) {
                    parent->right = toRemove->left;
                    toRemove->left->parent = parent;
                } else {
                    parent->right = toRemove->right;
                    toRemove->right->parent = parent;
                }
            }
            //delete toRemove;
        }
        else {
            Node* nextInOrder = toRemove->right;
            while(nextInOrder->left != nullptr) { nextInOrder = nextInOrder->left;}
            swap(nextInOrder, toRemove);
            parent = nextInOrder->parent;
            removeBST(nextInOrder, parent, root);
        }


    }
    template<class T>
    void AVL<T>::removeRoot(Node* root, Node *&realRoot, Node*& myParent) {
        Node* toRemove = nullptr;
        if(isLeaf(root)) {
            realRoot = nullptr;
        }
        else if (hasOneSon(root)) {
            toRemove = root;
            if(root->right == nullptr) {
                realRoot = realRoot->left;
            }
            else { realRoot = realRoot->right;}
            realRoot->parent = nullptr;
            toRemove->parent = nullptr;
            toRemove->right = nullptr;
            toRemove->left = nullptr;
            //delete toRemove;
        }
        else { //Has 2 sons
            Node* nextInOrder = root->right;
            while(nextInOrder->left != nullptr) { nextInOrder = nextInOrder->left;}
            swap(root, nextInOrder);
            myParent = nextInOrder->parent;
            removeBST(nextInOrder, nextInOrder->parent, root);

        }

    }
    template<class T>
    typename AVL<T>::Node* AVL<T>::doRemoveRotation(Node *parent, Node *root) {
        Node* parentOfUnbalanced = nullptr;
        bool parent_is_right_son = false;
        int prev;
        while (parent) {
            prev = parent->height;
            updateHeight(parent);
            if(BF(parent) == 2 || BF(parent) == -2) {
                if(BF(parent) == 2) {
                    if (parent->left && BF(parent->left) >= 0) {
                        if (parent == root)
                            return rotateRight(parent);
                        else {
                            parentOfUnbalanced = parent->parent;
                            if (parentOfUnbalanced->left == parent) {
                                parentOfUnbalanced->left = rotateRight(parent);
                            }
                            else {
                                parent_is_right_son = true;
                                parentOfUnbalanced->right = rotateRight(parent);
                            }
                        }
                    } else {
                        if(parent == root)
                            return LR(parent);
                        else {
                            parentOfUnbalanced = parent->parent;
                            if (parentOfUnbalanced->left == parent) {
                                parentOfUnbalanced->left = LR(parent);
                            } else {
                                parent_is_right_son = true;
                                parentOfUnbalanced->right = LR(parent);
                            }
                        }

                    }
                }
                else {
                    if (parent->right && BF(parent->right) <= 0) {
                        if (parent == root)
                            return rotateLeft(parent);
                        else {
                            parentOfUnbalanced = parent->parent;
                            if (parentOfUnbalanced->left == parent) {
                                parentOfUnbalanced->left = rotateLeft(parent);
                            } else {
                                parent_is_right_son = true;
                                parentOfUnbalanced->right = rotateLeft(parent);
                            }
                        }
                    }
                    else
                    {
                        if(parent == root)
                            return RL(parent);
                        else {
                            parentOfUnbalanced = parent->parent;
                            if (parentOfUnbalanced->left == parent) {
                                parentOfUnbalanced->left = RL(parent);
                            } else {
                                parent_is_right_son = true;
                                parentOfUnbalanced->right = RL(parent);
                            }
                        }

                    }

                }
                /*
                if(parent_is_right_son) {
                    if(parentOfUnbalanced->right->height == prev) return root;
                }
                if(parentOfUnbalanced->left->height == prev) return root; */
            }
            /*
            else {
                if(parent->height == prev) { return root;}
            } */

            parent = parent->parent;
        }
        return root;
    }
    template<class T>
    typename AVL<T>::Node* AVL<T>::removeNode(Node* toRemove, Node* root) {
            Node *toRemove_parent = toRemove->parent;
            removeBST(toRemove, toRemove_parent, root);
            return doRemoveRotation(toRemove_parent, root);
    }

template<class T>
AVL<T>::~AVL() {
    destroy(root);
}

template<class T>
void AVL<T>::destroy(AVL::Node *root) {
    if(!root)
        return;
    destroy(root->left);
    destroy(root->right);
    delete root;
}
template <class T>
T* AVL<T>::find(T* toFind) {
    Node* found = findNode(*toFind, root);
    if(!found) return nullptr;
    return found->obj;
}
template<class T>
void AVL<T>::printPostOrder(AVL::Node *root, int *&output) {
    if(!root)
        return;
    printPostOrder(root->right, output);
    *(output++) = root->obj->getId();
    printPostOrder(root->left, output);
}


#endif

