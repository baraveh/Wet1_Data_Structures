//
// Created by Bar on 29-Apr-19.
//

#ifndef WET1_DATA_STRUCTURES_AVLTree_H
#define WET1_DATA_STRUCTURES_AVLTree_H

#include <iostream>
#include <cstdio>
#include <cmath>
#include <assert.h>
#include <cassert>
#include "exception.h"
#include "Array.h"


using namespace std;

template<class T, class S>
class AVLNode {
public:
    T key_m;
    S value_m;
    int balance_m;
    AVLNode *left_m;
    AVLNode *right_m;
    AVLNode *parent_m;

    AVLNode(const T &key = T(), const S &value = S(), AVLNode *parent = nullptr) : key_m(key),
                                                             value_m(value),
                                                             balance_m(0),
                                                             parent_m(parent),
                                                             left_m(nullptr),
                                                             right_m(nullptr) {}

    ~AVLNode() {
        delete left_m;
        delete right_m;
    }

    T &getKey() {
        return key_m;
    }

    S &getValue() {
        return value_m;
    }

};

template<typename T, typename S>
static AVLNode<T, S> *
mergeSortedArrays(T *arr1Keys, S *arr1Values, T *arr2Keys, S *arr2Values,
                  int arr1Size, int arr2Size);

template<class T, class S>
class AVLTree {
public:
    AVLTree();

    ~AVLTree();

    bool insertElement(const T &key, const S &value = S());

    void deleteElement(const T &key);

    void printBalance();

    void printInOrder();

    bool searchKey(const T &key);

    S &operator[](const T &key);

    const S &operator[](const T &key) const;

    bool checkIfBalanced();

    void printTree(T *keyArr, S *valArr) const; //prints inorder into array

    int countNodesInTree() const;

    void mergeTrees(const AVLTree<T, S> &treeA, const AVLTree &treeB);

    AVLNode<T, S> *getRoot();

private:
    AVLNode<T, S> *root;

    AVLNode<T, S> *rollLL(AVLNode<T, S> *aNode);

    AVLNode<T, S> *rollRR(AVLNode<T, S> *aNode);

    AVLNode<T, S> *rollLR(AVLNode<T, S> *aNode);

    AVLNode<T, S> *rollRL(AVLNode<T, S> *aNode);

    void balance(AVLNode<T, S> *aNode);

    int height(AVLNode<T, S> *aNode);

    void setBalance(AVLNode<T, S> *aNode);

    void printBalance(AVLNode<T, S> *aNode);

    void printInOrder(AVLNode<T,S>* aNode);

    int countNodes(const AVLNode<T, S> *aNode) const;

    void printTree(AVLNode<T, S> *aNode, T *keyArr, S *valArr, int *iteration) const;

    bool checkIfBalanced(AVLNode<T, S> *aNode);

    AVLNode<T, S> *
    mergeTrees(AVLNode<T, S> *nodeArr, int start, int end,
               AVLNode<T, S> *parent);

};


template<class T, class S>
void AVLTree<T, S>::balance(AVLNode<T, S> *aNode) {

    setBalance(aNode);

    if (aNode->balance_m == -2) {
        if (height(aNode->left_m->left_m) >= height(aNode->left_m->right_m))
            aNode = rollRR(aNode);
        else
            aNode = rollLR(aNode);
    } else if (aNode->balance_m == 2) {
        if (height(aNode->right_m->right_m) >= height(aNode->right_m->left_m))
            aNode = rollLL(aNode);
        else
            aNode = rollRL(aNode);
    }

    if (aNode->parent_m != nullptr) {
        balance(aNode->parent_m);
    } else {
        root = aNode;
    }
}

template<class T, class S>
AVLNode<T, S> *AVLTree<T, S>::rollLL(AVLNode<T, S> *aNode) {
    AVLNode<T, S> *temp = aNode->right_m;
    temp->parent_m = aNode->parent_m;
    aNode->right_m = temp->left_m;

    if (aNode->right_m != nullptr)
        aNode->right_m->parent_m = aNode;

    temp->left_m = aNode;
    aNode->parent_m = temp;

    if (temp->parent_m != nullptr) {
        if (temp->parent_m->right_m == aNode) {
            temp->parent_m->right_m = temp;
        } else {
            temp->parent_m->left_m = temp;
        }
    }

    setBalance(aNode);
    setBalance(temp);
    return temp;
}

template<class T, class S>
AVLNode<T, S> *AVLTree<T, S>::rollRR(AVLNode<T, S> *aNode) {
    AVLNode<T, S> *temp = aNode->left_m;
    temp->parent_m = aNode->parent_m;
    aNode->left_m = temp->right_m;

    if (aNode->left_m != nullptr)
        aNode->left_m->parent_m = aNode;

    temp->right_m = aNode;
    aNode->parent_m = temp;

    if (temp->parent_m != nullptr) {
        if (temp->parent_m->right_m == aNode) {
            temp->parent_m->right_m = temp;
        } else {
            temp->parent_m->left_m = temp;
        }
    }

    setBalance(aNode);
    setBalance(temp);
    return temp;
}

template<class T, class S>
AVLNode<T, S> *AVLTree<T, S>::rollLR(AVLNode<T, S> *aNode) {
    aNode->left_m = rollLL(aNode->left_m);
    return rollRR(aNode);
}

template<class T, class S>
AVLNode<T, S> *AVLTree<T, S>::rollRL(AVLNode<T, S> *aNode) {
    aNode->right_m = rollRR(aNode->right_m);
    return rollLL(aNode);
}

template<class T, class S>
int AVLTree<T, S>::height(AVLNode<T, S> *aNode) {
    if (aNode == nullptr)
        return -1;
    return 1 + std::max(height(aNode->left_m), height(aNode->right_m));
}

template<class T, class S>
void AVLTree<T, S>::setBalance(AVLNode<T, S> *aNode) {
    aNode->balance_m = height(aNode->right_m) - height(aNode->left_m);
}

template<class T, class S>
void AVLTree<T, S>::printBalance(AVLNode<T, S> *aNode) {
    if (aNode != nullptr) {
        printBalance(aNode->left_m);
        std::cout << aNode->balance_m << " ";
        printBalance(aNode->right_m);
    }
}

template<class T, class S>
AVLTree<T, S>::AVLTree() : root(nullptr) {}

template<class T, class S>
AVLTree<T, S>::~AVLTree() {
    delete root;
}

template<class T, class S>
bool AVLTree<T, S>::insertElement(const T &key, const S &value) {
    if (root == nullptr) {
        try {
            root = new AVLNode<T, S>(key, value, nullptr);
        }
        catch (std::bad_alloc &e) {
            throw MemError();
        }
        return true;
    }
    AVLNode<T, S> *iterator = root;
    AVLNode<T, S> *parent;

    while (true) {
        if (iterator->key_m == key) {
            throw KeyAlreadyExists();
        }

        parent = iterator;
        bool goLeft = (iterator->key_m) > key;
        iterator = goLeft ? iterator->left_m : iterator->right_m;

        if (iterator == nullptr) {
            try {
                if (goLeft) {
                    parent->left_m = new AVLNode<T, S>(key, value, parent);
                } else {
                    parent->right_m = new AVLNode<T, S>(key, value, parent);
                }
            }
            catch (std::bad_alloc &e) {
                throw MemError();
            }

            balance(parent);
            return true;
        }
    }

}

template<class T, class S>
void AVLTree<T, S>::deleteElement(const T &delKey) {
    if (root == nullptr) {
        throw NoSuchKey();
    }

    AVLNode<T, S> *iterator = root;
    AVLNode<T, S> *parent;
    AVLNode<T, S> *delNode = nullptr;
    AVLNode<T, S> *child = root;

    while (child != nullptr) {
        parent = iterator;
        iterator = child;
        child = (delKey >= iterator->key_m) ? iterator->right_m
                                            : iterator->left_m;
        if (delKey == iterator->key_m)
            delNode = iterator;
    }
    if (delNode == nullptr) {
        throw NoSuchKey();
    }

    delNode->key_m = iterator->key_m;
    child = (iterator->left_m != nullptr) ? iterator->left_m
                                          : iterator->right_m;

    if (root->key_m == delKey) {
        root = child;
        return;
    }

    if (parent->left_m == iterator) {
        parent->left_m = child;
    } else {
        parent->right_m = child;
    }
    balance(parent);
}

template<class T, class S>
void AVLTree<T, S>::printBalance() {
    printBalance(root);
}

template<class T, class S>
bool AVLTree<T, S>::searchKey(const T &key) {

    AVLNode<T, S>* iterator = root;

    while (iterator != nullptr && iterator != NULL) {
        if (iterator->key_m == key)
            return true;

        bool goLeft = (iterator->key_m) > key;
        iterator = goLeft ? iterator->left_m : iterator->right_m;
    }
    return false;
}

template<class T, class S>
S &AVLTree<T, S>::operator[](const T &key) {

    AVLNode<T, S> *iterator = root;
    while (iterator != nullptr) {
        if (iterator->key_m == key)
            return iterator->value_m;

        bool goLeft = (iterator->key_m) > key;
        iterator = goLeft ? iterator->left_m : iterator->right_m;
    }
    throw NoSuchKey();
}

template<class T, class S>
const S &AVLTree<T, S>::operator[](const T &key) const {
    AVLNode<T, S> *iterator = root;
    while (iterator != nullptr) {
        if (iterator->key_m == key)
            return iterator->value_m;

        bool goLeft = (iterator->key_m) > key;
        iterator = goLeft ? iterator->left_m : iterator->right_m;
    }
    throw NoSuchKey();
}

template<class T, class S>
bool AVLTree<T, S>::checkIfBalanced() {
    return checkIfBalanced(root);
}


template<class T, class S>
int AVLTree<T, S>::countNodesInTree() const {
    return countNodes(root);
}

template<class T, class S>
int AVLTree<T, S>::countNodes(const AVLNode<T, S> *aNode) const{
    int count = 0;
    if (aNode != nullptr) {
        count += countNodes(aNode->left_m);
        count++;
        count += countNodes(aNode->right_m);
    }
    return count;
}

template<class T, class S>
void AVLTree<T, S>::printTree(AVLNode<T, S> *aNode, T *keyArr, S *valArr,
                              int *iteration) const{
    if (aNode == nullptr) {
        return;
    }
    if (aNode->left_m != nullptr) {
        printTree(aNode->left_m, keyArr, valArr, iteration);
    }
    *(keyArr + *iteration) = aNode->key_m;
    *(valArr + *iteration) = aNode->value_m;
    *iteration += 1;
    if (aNode->right_m != nullptr) {
        printTree(aNode->right_m, keyArr, valArr, iteration);
    }
}

template<class T, class S>
void AVLTree<T, S>::printTree(T *keyArr, S *valArr) const {
    int iteration = 0;
    printTree(root, keyArr, valArr, &iteration);
}

template<class T, class S>
bool AVLTree<T, S>::checkIfBalanced(AVLNode<T, S> *aNode) {
    if (aNode == nullptr) {
        return true;
    }
    return ((checkIfBalanced(aNode->left_m)) && abs(aNode->balance_m) < 2 &&
            checkIfBalanced(aNode->right_m));
}

template<class T, class S>
void
AVLTree<T, S>::mergeTrees(const AVLTree<T, S> &treeA, const AVLTree &treeB) {
    int treeASize = treeA.countNodesInTree();
    int treeBSize = treeB.countNodesInTree();
    try {
    T *treeAKeys = new T[treeASize];
    S *treeAVals = new S[treeASize];
    T *treeBKeys = new T[treeBSize];
    S *treeBVals = new S[treeBSize];
    treeA.printTree(treeAKeys, treeAVals);
    treeB.printTree(treeBKeys, treeBVals);

    AVLNode<T, S> *nodeArr = mergeSortedArrays(treeAKeys, treeAVals, treeBKeys,
                                               treeBVals, treeASize, treeBSize);

    delete[] treeAKeys;
    delete[] treeAVals;
    delete[] treeBKeys;
    delete[] treeBVals;

    AVLNode<T,S>* temp = root;
    root = mergeTrees(nodeArr, 0, treeASize + treeBSize - 1,
                      nullptr);
    delete [] nodeArr;
    delete temp;
    }
    catch(std::bad_alloc& e){
        throw MemError();
    }
}


template<class T, class S>
AVLNode<T, S> *AVLTree<T, S>::getRoot() {
    return root;
}

template<class T, class S>
AVLNode<T, S> *
AVLTree<T, S>::mergeTrees(AVLNode<T, S> *nodeArr, int start, int end,
                          AVLNode<T, S> *parent) {
    if(!nodeArr){
        throw MemError();
    }
    if(start > end){
        return nullptr;
    }
    int mid = (start+end)/2;
    T key = nodeArr[mid].key_m;
    S value = nodeArr[mid].value_m;
    AVLNode<T,S>* aNode = new AVLNode<T,S>(key, value, parent);
    aNode->parent_m = parent;
    aNode->left_m = mergeTrees(nodeArr, start, mid-1, aNode);
    aNode->right_m = mergeTrees(nodeArr, mid+1, end, aNode);
    return aNode;
}

template<class T, class S>
void AVLTree<T, S>::printInOrder() {
  printInOrder(root);
}

template<class T, class S>
void AVLTree<T, S>::printInOrder(AVLNode<T, S> *aNode) {
    if(aNode == nullptr){
        return;
    }
    printInOrder(aNode->left_m);
    std::cout << aNode->key_m << "\n";
    printInOrder(aNode->right_m);
}


template<typename T, typename S>
AVLNode<T, S> *
mergeSortedArrays(T *arr1Keys, S *arr1Values, T *arr2Keys, S *arr2Values,
                  int arr1Size, int arr2Size) {
    if (!arr1Keys || !arr2Keys || !arr1Values || !arr2Values) {
        throw MemError();
    }
    AVLNode<T,S>* mergedArr = new AVLNode<T,S>[arr1Size + arr2Size];
    int i = 0, j = 0, k = 0;
    while (i < arr1Size && j < arr2Size) {
        if (arr1Keys[i] < arr2Keys[j]) {
            mergedArr[k].key_m = arr1Keys[i];
            mergedArr[k].value_m = arr1Values[i];
            i++;
        }
        else {
            mergedArr[k].key_m = arr2Keys[j];
            mergedArr[k].value_m = arr2Values[j];
            j++;
        }
        k++;
    }
    while (i < arr1Size) {
        mergedArr[k].key_m = arr1Keys[i];
        mergedArr[k].value_m = arr1Values[i];
        i++;
        k++;
    }

    while (j < arr2Size) {
        mergedArr[k] = arr2Keys[j];
        j++;
        k++;
    }
    return mergedArr;

}

#endif //WET1_DATA_STRUCTURES_AVLTree_H
