//
// Created by Bar on 29-Apr-19.
//

#ifndef WET1_DATA_STRUCTURES_AVLTree_H
#define WET1_DATA_STRUCTURES_AVLTree_H

#include<iostream>
#include<cstdio>


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
};

/* AVL tree */
template<class T, class S>
class AVLTree {
public:
    AVLTree();

    ~AVLTree();

    bool insert(const T &key, const S &value = S());

    void remove(const T &key);

    void printBalance();

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
bool AVLTree<T, S>::insert(const T &key, const S &value = S()) {
    if (root == nullptr) {
        root = new AVLNode<T, S>(key, value, nullptr);
        return true;
    }
    AVLNode<T, S> *iterator = root;
    AVLNode<T, S> *parent;

    while (true) {
        if (iterator->key_m == key)
            //TODO exception
            return false;

        parent = iterator;
        bool goLeft = (iterator->key_m) > key;
        iterator = goLeft ? iterator->left_m : iterator->right_m;

        if (iterator == nullptr) {
            if (goLeft) {
                parent->left_m = new AVLNode<T, S>(key, value, parent);
            } else {
                parent->right_m = new AVLNode<T, S>(key, value, parent);
            }

            balance(parent);
            return true;
        }
    }

}

template<class T, class S>
void AVLTree<T, S>::remove(const T &delKey) {
    if (root == nullptr) {
        //TODO - excpetion
        return;
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
        //TODO exception
        return;
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


#endif //WET1_DATA_STRUCTURES_AVLTree_H