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
    AVLNode *left_m;
    AVLNode *right_m;
    int height_m;

    AVLNode(const T &key = T(), const S &value = S())
            : key_m(key),
              value_m(value),
              left_m(nullptr),
              right_m(nullptr),
              height_m(1) {}

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

    void setHeight(int height) {
        height_m = height;
    }

};

template<typename T, typename S>
static AVLNode<T, S> *
mergeSortedArrays(T *arr1Keys, S *arr1Values, T *arr2Keys, S *arr2Values,
                  int arr1Size, int arr2Size, int *mergedArrSize);

template<class T, class S>
class AVLTree {
public:
    AVLTree();

    ~AVLTree();

    bool insertElement(const T &key, const S &value = S());

    void deleteElement(const T &key);

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

    int height(AVLNode<T, S> *aNode);

    void printInOrder(AVLNode<T, S> *aNode);

    int countNodes(const AVLNode<T, S> *aNode) const;

    void
    printTree(AVLNode<T, S> *aNode, T *keyArr, S *valArr, int *iteration) const;

    bool checkIfBalanced(AVLNode<T, S> *aNode);

    AVLNode<T, S> *
    mergeTrees(AVLNode<T, S> *nodeArr, int start, int end,
               AVLNode<T, S> *parent);

    AVLNode<T, S> *deleteNode(AVLNode<T, S> *root, const T &keyToDelete);

    AVLNode<T,S>* insertNode(AVLNode<T,S>* root, const T& key, const S& value);

    AVLNode<T, S> *minValueNode(AVLNode<T, S> *);

    int getBalance(AVLNode<T,S>* N)
    {
        if (N == NULL)
            return 0;
        return height(N->left_m) -
               height(N->right_m);
    }


};


template<class T, class S>
AVLNode<T, S> *AVLTree<T, S>::rollLL(AVLNode<T, S> *aNode) {
    AVLNode<T, S> *y = aNode->right_m;
    AVLNode<T, S> *T2 = y->left_m;

    // Perform rotation
    y->left_m = aNode;
    aNode->right_m = T2;

    // Update heights
    aNode->height_m = std::max(height(aNode->left_m),
                          height(aNode->right_m)) + 1;
    y->height_m = std::max(height(y->left_m),
                      height(y->right_m)) + 1;

    // Return new root
    return y;
}

template<class T, class S>
AVLNode<T, S> *AVLTree<T, S>::rollRR(AVLNode<T, S> *aNode) {
    AVLNode<T, S> *x = aNode->left_m;
    AVLNode<T, S> *T2 = x->right_m;

    // Perform rotation
    x->right_m = aNode;
    aNode->left_m = T2;

    // Update heights
    aNode->height_m = max(height(aNode->left_m),
                          height(aNode->right_m)) + 1;
    x->height_m = max(height(x->left_m),
                      height(x->right_m)) + 1;

    // Return new root
    return x;
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
    if (aNode == nullptr) {
        return 0;
    }
    return aNode->height_m;
}


template<class T, class S>
AVLTree<T, S>::AVLTree() : root(nullptr) {}

template<class T, class S>
AVLTree<T, S>::~AVLTree() {
    delete root;
}

template<class T, class S>
bool AVLTree<T, S>::insertElement(const T &key, const S &value) {
    if(searchKey(key)){
        throw KeyAlreadyExists();
    }
    root = insertNode(root, key, value);
    return true;
}



template<class T, class S>
void AVLTree<T, S>::deleteElement(const T &delKey) {
    if (!searchKey(delKey)) {
        throw NoSuchKey();
    }
    root = deleteNode(root, delKey);
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
int AVLTree<T, S>::countNodesInTree() const {
    return countNodes(root);
}

template<class T, class S>
int AVLTree<T, S>::countNodes(const AVLNode<T, S> *aNode) const {
    int count = 0;
    if (aNode != nullptr && aNode != NULL) {
        count += countNodes(aNode->left_m);
        count++;
        count += countNodes(aNode->right_m);
    }
    return count;
}

template<class T, class S>
void AVLTree<T, S>::printTree(AVLNode<T, S> *aNode, T *keyArr, S *valArr,
                              int *iteration) const {
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
    return ((checkIfBalanced(aNode->left_m)) && abs(getBalance(aNode)) < 2 &&
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

        int nodeArrSize = 0;
        AVLNode<T, S> *nodeArr = mergeSortedArrays(treeAKeys, treeAVals,
                                                   treeBKeys,
                                                   treeBVals, treeASize,
                                                   treeBSize, &nodeArrSize);
        delete[] treeAKeys;
        delete[] treeAVals;
        delete[] treeBKeys;
        delete[] treeBVals;

        AVLNode<T, S> *temp = root;
        AVLNode<T, S> *res = mergeTrees(nodeArr, 0, (nodeArrSize) - 1, nullptr);
        root = res;

        delete[] nodeArr;
        if (temp != nullptr) {
            delete temp;
        }

    }
    catch (std::bad_alloc &e) {
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
    if (!nodeArr) {
        throw MemError();
    }
    if (start > end) {
        return nullptr;
    }
    int mid = (start + end) / 2;
    T key = nodeArr[mid].key_m;
    S value = nodeArr[mid].value_m;
    AVLNode<T, S> *aNode = new AVLNode<T, S>(key, value);
    aNode->left_m = mergeTrees(nodeArr, start, mid - 1, aNode);
    aNode->right_m = mergeTrees(nodeArr, mid + 1, end, aNode);
    aNode->height_m = std::max(height(aNode->left_m),
                          height(aNode->right_m)) + 1;
    return aNode;
}

template<class T, class S>
void AVLTree<T, S>::printInOrder() {
    printInOrder(root);
}

template<class T, class S>
void AVLTree<T, S>::printInOrder(AVLNode<T, S> *aNode) {
    if (aNode == nullptr) {
        return;
    }
    printInOrder(aNode->left_m);
    std::cout << aNode->key_m << ",";
    printInOrder(aNode->right_m);
}

template<class T, class S>
AVLNode<T, S> *
AVLTree<T, S>::minValueNode(AVLNode<T, S> *node) {
    AVLNode<T, S> *current = node;

    /* loop down to find the leftmost leaf */
    while (current->left_m != nullptr)
        current = current->left_m;

    return current;
}

template<class T, class S>
AVLNode<T, S> *
AVLTree<T, S>::deleteNode(AVLNode<T, S> *root, const T &keyToDelete) {

    if (root == nullptr) {
        return root;
    }

    // If the key to be deleted is smaller
    // than the root's key, then it lies
    // in left subtree
    if (keyToDelete < root->key_m)
        root->left_m = deleteNode(root->left_m, keyToDelete);

        // If the key to be deleted is greater
        // than the root's key, then it lies
        // in right subtree
    else if (keyToDelete > root->key_m)
        root->right_m = deleteNode(root->right_m, keyToDelete);

        // if key is same as root's key, then
        // This is the node to be deleted
    else {
        // node with only one child or no child
        if ((root->left_m == nullptr) ||
            (root->right_m == nullptr)) {
            AVLNode<T, S> *temp = root->left_m ?
                                  root->left_m :
                                  root->right_m;

            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else{ //one child
                root->key_m = temp->key_m;
                root->value_m = temp->value_m;
                root->right_m = temp->right_m

            }

            delete (temp);
        }
        else {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            AVLNode<T, S> *temp = minValueNode(root->right_m);

            // Copy the inorder successor's
            // data to this node
            root->key_m = temp->key_m;
            root->value_m = temp->value_m;

            // Delete the inorder successor
            root->right_m = deleteNode(root->right_m,
                                       temp->key_m);
        }

    }

    if(root == nullptr){
        return root;
    }

    root->height_m = 1 + std::max(height(root->left_m),
                           height(root->right_m));
    int balance = getBalance(root);

    if (balance > 1 &&
        getBalance(root->left_m) >= 0)
        return rollRR(root);

    // Left Right Case
    if (balance > 1 &&
        getBalance(root->left_m) < 0)
    {
        root->left_m = rollLL(root->left_m);
        return rollRR(root);
    }

    // Right Right Case
    if (balance < -1 &&
        getBalance(root->right_m) <= 0)
        return rollLL(root);

    // Right Left Case
    if (balance < -1 &&
        getBalance(root->right_m) > 0)
    {
        root->right_m = rollRR(root->right_m);
        return rollLL(root);
    }

    return root;

}

template<class T, class S>
AVLNode<T, S> *
AVLTree<T, S>::insertNode(AVLNode<T, S>* root, const T &key, const S &value) {
    /* 1. Perform the normal BST rotation */
    if (root == NULL)
        return new AVLNode<T,S>(key, value);

    if (key <root->key_m)
        root->left_m = insertNode(root->left_m, key, value);
    else if (key > root->key_m)
        root->right_m = insertNode(root->right_m, key, value);
    else // Equal keys not allowed
        throw KeyAlreadyExists();

    /* 2. Update height of this ancestor node */
    root->height_m = 1 + std::max(height(root->left_m),
                           height(root->right_m));

    /* 3. Get the balance factor of this
        ancestor node to check whether
        this node became unbalanced */
    int balance = getBalance(root);

    // If this node becomes unbalanced,
    // then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < root->left_m->key_m)
        return rollRR(root);

    // Right Right Case
    if (balance < -1 && key > root->right_m->key_m)
        return rollLL(root);

    // Left Right Case
    if (balance > 1 && key > root->left_m->key_m)
    {
        root->left_m = rollLL(root->left_m);
        return rollRR(root);
    }

    // Right Left Case
    if (balance < -1 && key < root->right_m->key_m)
    {
        root->right_m = rollRR(root->right_m);
        return rollLL(root);
    }

    /* return the (unchanged) node pointer */
    return root;
}


template<typename T, typename S>
AVLNode<T, S> *
mergeSortedArrays(T *arr1Keys, S *arr1Values, T *arr2Keys, S *arr2Values,
                  int arr1Size, int arr2Size, int *mergedSize) {
    if (!arr1Keys || !arr2Keys || !arr1Values || !arr2Values || !mergedSize) {
        throw MemError();
    }
    AVLNode<T, S> *mergedArr = new AVLNode<T, S>[arr1Size + arr2Size];
    int i = 0, j = 0, k = 0;
    while (i < arr1Size && j < arr2Size) {
        if (arr1Keys[i] <= arr2Keys[j]) {
            mergedArr[k].key_m = arr1Keys[i];
            mergedArr[k].value_m = arr1Values[i];
            if (arr1Keys[i] == arr2Keys[j]) {
                j++;
            }
            i++;
        } else {
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
        mergedArr[k].key_m = arr2Keys[j];
        mergedArr[k].value_m = arr2Values[j];
        j++;
        k++;
    }
    *mergedSize = k;
    return mergedArr;
}


template<typename T, typename S>
static bool isSorted(AVLNode<T, S> *arr, int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i].key_m < arr[i - 1].key_m) {
            return false;
        }
    }
    return true;
}

#endif //WET1_DATA_STRUCTURES_AVLTree_H
