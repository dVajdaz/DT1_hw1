//
// Created by Администратор on 29.04.2023.
//

#ifndef DS1_HW1_AVL_H
#define DS1_HW1_AVL_H

#include "wet1util.h"
#include "math.h"

template<class T, class Comparator>
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

        bool *deleteObject;

        /*
        Node(T& toAdd) {
            obj = &toAdd;

            left = nullptr;
            right = nullptr;
            parent = nullptr;

            height = 0;
        }*/

        ~Node() {
            if(*deleteObject && obj != nullptr)
                delete obj;
        }
    };

    Node *max_node = nullptr; //A pointer to the node containing the largest value in the tree
    Node *root; //A pointer to the root of the current tree

    bool deleteObject = false;
    Comparator compare;

    //--------------------------Node operations--------------------------
    //Node *initializeNode(T &obj);

    Node *findNode(const T &toSearch, Node *subtree);

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

    Node *findParent(const T &toSearch, Node *subtree);

    //--------------------------Rotations--------------------------
    /**
     * Receives a node to rotate and performs a RR rotation on him
     * @param toRotate The node which we wish to rotate
     * @return a pointer to the new root of the subtree, following the rotation
     */
    Node *rotateLeft(Node *toRotate); //RR

    /**
     * Receives a node to rotate and performs a LL rotation on him
     * @param toRotate The node which we wish to rotate
     * @return a pointer to the new root of the subtree, following the rotation
     */
    Node *rotateRight(Node *toRotate); //LL

    Node *LR(Node *toRotate);

    Node *RL(Node *toRotate);

    int BF(Node *subtree);

    bool isLeaf(Node *node);

    AVL();

    AVL(const AVL<T, Comparator> &toCopy) = default;

    ~AVL();

    /**
     * Receives a Node in the tree and updates its height
     * @param toUpdate - a Node
     */
    void updateHeight(Node *toUpdate);

    void destroy(Node* toDestroy);

    //--------------------------Tree operations--------------------------
    /**
     * Receives a value to insert into the tree and does so, while maintaining
     * the tree's balance
     * @param toInsert - a value to insert into the tree
     */
    void insert(T &toInsert);

    /**
     * Receives a value to remove from the tree and does so, while maintaining
     * the tree's balance
     * @param toRemove - a value to remove from the tree
     */
    void remove(const T &toRemove);

    /**
     * Prints the values stored in the tree in postorder
     * @param root the root of the tree
     */
    void printPostOrder(Node *root, int *&output);

    T *find(T *toFind);

    Node *getMinNode(Node *node) const;

    Node *getMaxNode(Node *node) const;

    void setObjectDelete();
};

//--------------------------Tree operations implementation--------------------------
template<class T, class Comparator>
AVL<T, Comparator>::AVL() : root(NULL), compare(), size(0) {}

template<class T, class Comparator>
AVL<T, Comparator>::~AVL() {
    destroy(root);
}

template<class T, class Comparator>
T *AVL<T, Comparator>::find(T *toFind) {
    Node *found = findNode(*toFind, root);
    if (!found) return nullptr;
    return found->obj;
}

template<class T, class Comparator>
void AVL<T, Comparator>::insert(T &toInsert) { //TODO: Return a pointer to the inserted object (T* return type)
    if (&toInsert == NULL)
        return;

    //If the tree is empty
    if (!root) {
        Node *toInsertNode = new Node;
        toInsertNode->obj = &toInsert;
        toInsertNode->right = NULL;
        toInsertNode->left = NULL;
        toInsertNode->parent = NULL;
        toInsertNode->height = 0;
        toInsertNode->deleteObject = &(AVL::deleteObject);

        root = toInsertNode;
        max_node = toInsertNode;

        //root = initializeNode(toInsert);
        //max_node = initializeNode(toInsert);
        size++;
        return;
    }

    if (findNode(toInsert, root))
        return;

    //Node *toInsertNode = initializeNode(toInsert);

    Node *toInsertNode = new Node;
    toInsertNode->obj = &toInsert;
    toInsertNode->right = NULL;
    toInsertNode->left = NULL;
    toInsertNode->parent = NULL;
    toInsertNode->height = 0;
    toInsertNode->deleteObject = &(AVL::deleteObject);

    root = insertNode(toInsertNode, root);

    max_node = getMaxNode(root);

    size++;
}

template<class T, class Comparator>
void AVL<T, Comparator>::remove(const T &toRemove) { //TODO: Return a pointer to the deleted object
    if (&toRemove == NULL)
        return;

    if (!root || !findNode(toRemove, root)) {
        findNode(toRemove, root);
        return;
    }

    Node *removed = findNode(toRemove, root);
    root = removeNode(removed, root);

    max_node = getMaxNode(root);

    size--;
}

template<class T, class Comparator>
void AVL<T, Comparator>::updateHeight(Node *toUpdate) {
    if (isLeaf(toUpdate)) {
        toUpdate->height = 0;
    } else if (toUpdate->right && toUpdate->left) {
        toUpdate->height = 1 + std::max(toUpdate->right->height, toUpdate->left->height);
    } else if (toUpdate->left) {
        toUpdate->height = toUpdate->left->height + 1;
    } else if (toUpdate->right) {
        toUpdate->height = toUpdate->right->height + 1;
    }

}

template<class T, class Comparator>
int AVL<T, Comparator>::BF(Node *subtree) {
    int right_height, left_height;
    if (subtree->right == nullptr) {
        right_height = -1;

    } else { right_height = subtree->right->height; }
    if (subtree->left == nullptr) {
        left_height = -1;

    } else { left_height = subtree->left->height; }
    return left_height - right_height;
}

template<class T, class Comparator>
bool AVL<T, Comparator>::isLeaf(Node *node) {
    return node->left == nullptr && node->right == nullptr;
}

template<class T, class Comparator>
void AVL<T, Comparator>::printPostOrder(AVL::Node *root, int *&output) {
    if (!root)
        return;
    printPostOrder(root->right, output);
    *(output++) = root->obj->getId();
    printPostOrder(root->left, output);
}

template<class T, class Comparator>
void AVL<T, Comparator>::setObjectDelete(){
    deleteObject = true;
}

//--------------------------Rotations implementation--------------------------
template<class T, class Comparator>
typename AVL<T, Comparator>::Node *
AVL<T, Comparator>::rotateRight(
        Node *toRotate) {  //TODO: Cover the case where toRotate is the root + not sure if parent field needed
    if (!toRotate || !toRotate->left)
        return toRotate;

    //Perform the Rotation
    Node *left = toRotate->left;

    if (left->right) {
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

template<class T, class Comparator>
typename AVL<T, Comparator>::Node *
AVL<T, Comparator>::rotateLeft(Node *toRotate) {
    if (!toRotate || !toRotate->right)
        return toRotate;

    //Perform the Rotation
    Node *right = toRotate->right;

    if (right->left) {
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

template<class T, class Comparator>
typename AVL<T, Comparator>::Node *
AVL<T, Comparator>::RL(
        Node *toRotate) { //Not sure if any additional tests needed since basic rotation methods cover all the edge cases already
    if (toRotate) {
        Node *right = toRotate->right;
        toRotate->right = rotateRight(right);
        return rotateLeft(toRotate);
    }
    return nullptr;
}

template<class T, class Comparator>
typename AVL<T, Comparator>::Node *
AVL<T, Comparator>::LR(Node *toRotate) {
    if (toRotate) {
        Node *left = toRotate->left;
        toRotate->left = rotateLeft(left);
        return rotateRight(toRotate);
    }
    return nullptr;
}

//Note that RR and LL are rotateLeft and rotateRight respectively

//--------------------------Node operations implementation--------------------------
/*
template<class T, class Comparator>
typename AVL<T, Comparator>::Node *AVL<T, Comparator>::initializeNode(T &obj) {
    Node *newNode = new Node;

    newNode->obj = &obj;

    newNode->right = NULL;
    newNode->left = NULL;
    newNode->parent = NULL;
    newNode->height = 0;

    newNode->deleteObject = &(AVL::deleteObject);

    Node newNode = Node(obj);
    newNode.deleteObject = &(AVL::deleteObject);

    return newNode;
}
*/

template<class T, class Comparator>
typename AVL<T, Comparator>::Node *AVL<T, Comparator>::findNode(const T &toSearch, Node *subtree) {
    if (!subtree)
        return nullptr;


    if (compare(toSearch, *subtree->obj) == 0)
        return subtree;
    else if (compare(toSearch, *subtree->obj) > 0) {
        return findNode(toSearch, subtree->right);
    } else {
        return findNode(toSearch, subtree->left);
    }
}

template<class T, class Comparator>
typename AVL<T, Comparator>::Node *AVL<T, Comparator>::findParent(const T &toSearch, Node *subtree) {
    if (compare(*subtree->obj, toSearch) == 0) {
        return subtree;
    }
    if ((subtree->right != nullptr && compare(*subtree->right->obj, toSearch) == 0)
        || (subtree->left != nullptr && compare(*subtree->left->obj, toSearch) == 0)) { return subtree; }

    else if (compare(toSearch, *subtree->obj) > 0) {
        if (subtree->right == nullptr)
            return subtree;
        return findParent(toSearch, subtree->right);
    } else {
        if (subtree->left == nullptr)
            return subtree;
        return findParent(toSearch, subtree->left);
    }
}

template<class T, class Comparator>
typename AVL<T, Comparator>::Node *AVL<T, Comparator>::insertNode(Node *toInsert, Node *root) {
    //Finding the node that should be toInsert's parent
    Node *parent = findParent(*toInsert->obj, root);
    //Checking whether toInsert should be the left child or the right child and inserting him accordingly
    if (compare(*parent->obj, *toInsert->obj) < 0) {
        parent->right = toInsert;
    } else { parent->left = toInsert; }
    toInsert->parent = parent;

    //Checking the balance of the tree and rotating if needed
    return doInsertRotation(toInsert, parent, root);
}

template<class T, class Comparator>
typename AVL<T, Comparator>::Node *AVL<T, Comparator>::doInsertRotation(Node *toInsert, Node *parent, Node *root) {
    Node *parentOfUnbalanced;
    while (toInsert != root) {
        //Checking if the parent's height has changed
        if (parent->height > toInsert->height) { return root; }

        //Updating the parent's height
        parent->height = toInsert->height + 1;

        //Checking for rotations
        if (BF(parent) == 2 || BF(parent) == -2) {
            if (BF(parent) == 2) {
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
                    if (parent == root)
                        return LR(parent);
                    else {
                        parentOfUnbalanced = parent->parent;
                        if (parentOfUnbalanced->left == parent) {
                            parentOfUnbalanced->left = LR(parent);
                        } else { parentOfUnbalanced->right = LR(parent); }
                    }

                }
            } else {
                if (parent->right && BF(parent->right) <= 0) {
                    if (parent == root)
                        return rotateLeft(parent);
                    else {
                        parentOfUnbalanced = parent->parent;
                        if (parentOfUnbalanced->left == parent) {
                            parentOfUnbalanced->left = rotateLeft(parent);
                        } else { parentOfUnbalanced->right = rotateLeft(parent); }
                    }
                } else {
                    if (parent == root)
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

template<class T, class Comparator>
typename AVL<T, Comparator>::Node *AVL<T, Comparator>::removeNode(Node *toRemove, Node *subtree) {
    //Finding toRemove
    if (compare(*toRemove->obj, *subtree->obj) > 0) {
        subtree->right = removeNode(toRemove, subtree->right);
    } else if (compare(*toRemove->obj, *subtree->obj) < 0) {
        subtree->left = removeNode(toRemove, subtree->left);
    } else {
        //Removing toRemove after found
        if (!subtree->right && !subtree->left) {
            // Leaf
            if (subtree == root) {
                //toRemove is leaf&root
                delete subtree;
                return NULL;
            } else {
                //toRemove is leaf
                if (subtree->parent->left == subtree)
                    subtree->parent->left = nullptr;
                else
                    subtree->parent->right = nullptr;

                delete subtree;
                return NULL;
            }
        } else if (!subtree->left) {
            //toRemove has only right son
            Node *tmp = subtree->right;
            subtree->obj = tmp->obj;
            subtree->right = removeNode(subtree, subtree->right);
        } else if (!subtree->right) {
            //toRemove has only left son
            Node *tmp = subtree->left;
            subtree->obj = tmp->obj;//TODO: Implement copy constructor !!!
            subtree->left = removeNode(subtree, subtree->left);
        } else {
            //toRemove has both left and right sons
            Node *tmp = getMinNode(subtree->right);
            subtree->obj = tmp->obj;
            subtree->right = removeNode(subtree, subtree->right);
        }
    }

    updateHeight(subtree);
    // Balancing the tree
    if (BF(subtree) == 2) {
        if (subtree->left && BF(subtree->left) >= 0) {
            return rotateRight(subtree); //LL
        } else {
            return LR(subtree);
        }
    } else if (BF(subtree) == -2) {
        if (subtree->right && BF(subtree->right) == 1) {
            return RL(subtree);
        } else {
            return rotateLeft(subtree); //RR
        }
    }
    return subtree;
}

template<class T, class Comparator>
typename AVL<T, Comparator>::Node *AVL<T, Comparator>::getMinNode(AVL<T, Comparator>::Node *node) const {
    if (!node)
        return NULL;

    if (!node->left)
        return node;

    return getMinNode(node->left);
}

template<class T, class Comparator>
typename AVL<T, Comparator>::Node *AVL<T, Comparator>::getMaxNode(Node *node) const {
    if (!node)
        return NULL;

    if (!node->right)
        return node;

    return getMaxNode(node->right);
}

template<class T, class Comparator>
void AVL<T, Comparator>::destroy(Node* toDestroy) {
    if(!toDestroy)
        return;

    destroy(toDestroy->left);

    destroy(toDestroy->right);

    delete toDestroy;
}

#endif

