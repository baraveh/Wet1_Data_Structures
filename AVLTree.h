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

    AVLNode(const T &key, const S &value, AVLNode *parent) : key_m(key),
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


template<class T, class S>
class AVLTree {
public:
    AVLTree();

    ~AVLTree();

    bool insertElement(const T &key, const S &value = S());

    void deleteElement(const T &key);

    void printBalance();

    bool searchKey(const T &key);

    S &operator[](const T &key);

    const S &operator[](const T &key) const;

    bool checkIfBalanced();

    void printTree(T *keyArr, S *valArr); //prints inorder into array

    int countNodesInTree();

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

    int countNodes(const AVLNode<T, S> *aNode);

    void printTree(AVLNode<T, S> *aNode, T *keyArr, S *valArr, int *iteration);

    bool checkIfBalanced(AVLNode<T, S> *aNode);

    void createSortedArr(const AVLTree<T,S>& treeA, const AVLTree<T,S>& treeB, AVLNode<T,S>** arrPtr);

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

    AVLNode<T, S> *iterator = root;

    while (iterator != nullptr) {
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
int AVLTree<T, S>::countNodesInTree() {
    return countNodes(root);
}

template<class T, class S>
int AVLTree<T, S>::countNodes(const AVLNode<T, S> *aNode) {
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
                              int *iteration) {
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
void AVLTree<T, S>::printTree(T *keyArr, S *valArr) {
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
AVLTree<T, S>::mergeTrees(const AVLTree<T,S>& treeA, const AVLTree& treeB) {
    AVLNode<T,S>* temp = root;
    AVLNode<T,S>** arrPtr = (AVLNode<T,S>**)malloc(sizeof(*arrPtr));
    if(!arrPtr){
        throw MemError();
    }
    createSortedArr(treeA, treeB, arrPtr);
    assert(*arrPtr);
    int size = (treeA.countNodesInTree()) + (treeB.countNodesInTree());
    mergeTreesFromArr(*arrPtr, 0, size, root,
                      nullptr);
    delete *arrPtr;
    free(arrPtr);
    delete temp;
}

template<class T, class S>
void createSortedArr(const AVLTree<T,S>& treeA, const AVLTree<T,S>& treeB, AVLNode<T,S>** arrPtr){

    int treeASize = treeA.countNodesInTree();
    int treeBSize = treeB.countNodesInTree();
    T *treeAKeys = malloc(sizeof(*treeAKeys) * treeASize);
    S *treeAVals = malloc(sizeof(*treeAVals) * treeASize);
    T *treeBKeys = malloc(sizeof(*treeBKeys) * treeBSize);
    S *treeBVals = malloc(sizeof(*treeBVals) * treeBSize);
    if (!treeAKeys || !treeAVals || !treeBKeys || !treeBVals) {
        throw MemError();
    }
    treeA.printTree(treeAKeys, treeAVals);
    treeB.printTree(treeBKeys, treeAVals);
    Array<AVLNode<T, S>> treeAArr = Array<AVLNode<T, S>>(treeASize);
    Array<AVLNode<T, S>> treeBArr = Array<AVLNode<T, S>>(treeBSize);
    for (int i = 0; i < treeASize; i++) {
        treeAArr[i] = AVLNode<T, S>(treeAKeys[i], treeAVals[i], nullptr);
    }

    for (int i = 0; i < treeBSize; i++) {
        treeBArr[i] = AVLNode<T, S>(treeBKeys[i], treeBVals[i], nullptr);
    }
    free(treeAKeys);
    free(treeAVals);
    free(treeBKeys);
    free(treeBVals);

    *arrPtr = new AVLNode<T,S>[treeBSize + treeASize];
    if(!*arrPtr){
        throw MemError();
    }
    AVLNode<T,S>* mergedTreeArr = *arrPtr;

    int AIndex = 0;
    int BIndex = 0;
    for (int i = 0; i < treeBSize + treeASize; i++) {
        if (AIndex < treeASize && BIndex < treeBSize) {
            if (treeAArr[AIndex].getKey() < treeBArr[BIndex].getKey()) {
                mergedTreeArr[i] = AVLNode<T, S>(treeAArr[AIndex].getKey(),
                                                 treeAArr[AIndex].getValue(),
                                                 nullptr);
                AIndex++;
            } else {
                mergedTreeArr[i] = AVLNode<T, S>(treeBArr[BIndex].getKey(),
                                                 treeBArr[BIndex].getValue(),
                                                 nullptr);
                BIndex++;
            }
        }
        if (BIndex >= treeBSize) {
            assert(AIndex < treeASize);
            mergedTreeArr[i] = treeAArr[AIndex];
            AIndex++;
        }
        if (AIndex >= treeASize) {
            assert(BIndex < treeBSize);
            mergedTreeArr[i] = treeBArr[BIndex];
            BIndex++;
        }
    }
}

template<class T, class S>
AVLNode<T, S> *AVLTree<T, S>::getRoot() {
    return root;
}

template <class T, class S>
static void mergeTreesFromArr(AVLNode<T,S>* NodeArr, int start, const int& end, AVLNode<T,S>* aNode, AVLNode<T,S>* parent);

template<class T, class S>
static void mergeTreesFromArr(AVLNode<T,S>* NodeArr, int start, const int& end, AVLNode<T,S>* aNode, AVLNode<T,S>* parent) {
    if(start > end){
        aNode = nullptr;
        return;
    }
    int mid = (start + end) / 2;
    aNode = new AVLNode<T,S>(NodeArr[mid]);
    aNode->parent_m = parent;
    mergeTreesFromArr(NodeArr, start, mid -1, aNode->left_m, aNode);
    mergeTreesFromArr(NodeArr, mid + 1, end, aNode->right_m, aNode);

}
#endif //WET1_DATA_STRUCTURES_AVLTree_H
