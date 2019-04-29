//
// Created by Bar on 29-Apr-19.
//

#ifndef WET1_DATA_STRUCTURES_AvlTree_H
#define WET1_DATA_STRUCTURES_AvlTree_H

#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))
using namespace std;

/*
 * Node Declaration
 */
template <typename T, typename S>
struct avlNode
{
    T& key_m; //might need to be not by reference
    S& value_m;
    struct avlNode *left_m;
    struct avlNode *right_m;
};

template <typename T, typename S>
class AvlTree {
    avlNode<T,S>* root;

public:

    int height(avlNode<T,S> *);
    int diff(avlNode<T,S> *);
    avlNode<T,S>* rollRR(avlNode<T,S> *);
    avlNode<T,S>* rollLL(avlNode<T,S> *);
    avlNode<T,S>* rollLR(avlNode<T,S> *);
    avlNode<T,S>* rollRL(avlNode<T,S> *);
    avlNode<T,S>* balance(avlNode<T,S> *);
    avlNode<T,S>* insert(avlNode<T,S> *, const T&, const S& );
    avlNode<T,S>* remove(const T&); //TODO
    void display(avlNode<T,S> *, int);
    void inorder(avlNode<T,S> *);
    void preorder(avlNode<T,S> *);
    void postorder(avlNode<T,S> *);

    S& operator[](const T& key); //TODO
    AvlTree merge(const AvlTree& treeA, const AvlTree& treeB); //TODO


    AvlTree()
    {
        root = NULL;
    }

    AvlTree(const AvlTree& aTree); //TODO
    ~AvlTree(); //TODO
    AvlTree& operator= (const AvlTree& aTree); //TODO

};

/*
 * Height of AVL Tree
 */
template <typename T, typename S>
int AvlTree<T,S>::height(avlNode<T,S> *temp)
{
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height (temp->left_m);
        int r_height = height (temp->right_m);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

/*
 * Height Difference 
 */
template <typename T, typename S>
int AvlTree<T,S>::diff(avlNode<T,S> *temp)
{
    int l_height = height (temp->left_m);
    int r_height = height (temp->right_m);
    int b_factor= l_height - r_height;
    return b_factor;
}

/*
 * Right- Right Rotation
 */
template <typename T, typename S>
avlNode<T,S> *AvlTree<T,S>::rollRR(avlNode<T,S> *parent)
{
    avlNode<T,S> *temp;
    temp = parent->right_m;
    parent->right_m = temp->left_m;
    temp->left_m = parent;
    return temp;
}
/*
 * Left- Left Rotation
 */
template <typename T, typename S>
avlNode<T,S> *AvlTree<T,S>::rollLL(avlNode<T,S> *parent)
{
    avlNode<T,S> *temp;
    temp = parent->left_m;
    parent->left_m = temp->right_m;
    temp->right_m = parent;
    return temp;
}

/*
 * Left - Right Rotation
 */
template <typename T, typename S>
avlNode<T,S> *AvlTree<T,S>::rollLR(avlNode<T,S> *parent)
{
    avlNode<T,S> *temp;
    temp = parent->left_m;
    parent->left_m = rollRR (temp);
    return rollLL (parent);
}

/*
 * Right- Left Rotation
 */
template <typename T, typename S>
avlNode<T,S> *AvlTree<T,S>::rollRL(avlNode<T,S> *parent)
{
    avlNode<T,S> *temp;
    temp = parent->right_m;
    parent->right_m = rollLL (temp);
    return rollRR (parent);
}

/*
 * Balancing AVL Tree
 */
template <typename T, typename S>
avlNode<T,S> *AvlTree<T,S>::balance(avlNode<T,S> *temp)
{
    int bal_factor = diff (temp);
    if (bal_factor > 1)
    {
        if (diff (temp->left_m) > 0)
            temp = rollLL (temp);
        else
            temp = rollLR (temp);
    }
    else if (bal_factor < -1)
    {
        if (diff (temp->right) > 0)
            temp = rollRL (temp);
        else
            temp = rollRR (temp);
    }
    return temp;
}

/*
 * Insert Element into the tree
 */
template <typename T, typename S>
avlNode<T,S>* AvlTree<T,S>::insert(avlNode<T,S> *root, const T& key, const S& value)
{
    if (root == NULL)
    {
        root = new avlNode<T,S>;
        root->key_m = key;
        root->value_m = value;
        root->left_m = NULL;
        root->right_m = NULL;
        return root;
    }
    else if (key < root->key_m)
    {
        root->left_m = insert(root->left_m, key, value);
        root = balance (root);
    }
    else if (key >= root->key_m)
    {
        //decide what should happen when key already exists, atm - adds the new key anyway
        root->right_m = insert(root->right_m, key, value);
        root = balance (root);
    }
    return root;
}

/*
 * Display AVL Tree
 */
template <typename T, typename S>
void AvlTree<T,S>::display(avlNode<T,S> *ptr, int level)
{
    int i;
    if (ptr!=NULL)
    {
        display(ptr->right_m, level + 1);
        printf("\n");
        if (ptr == root)
            cout<<"Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout<<"        ";
        cout<<ptr->key_m;
        display(ptr->left_m, level + 1);
    }
}

/*
 * Inorder Traversal of AVL Tree
 */
template <typename T, typename S>
void AvlTree<T,S>::inorder(avlNode<T,S> *tree)
{
    if (tree == NULL)
        return;
    inorder (tree->left_m);
    cout<<tree->key_m<<"  ";
    inorder (tree->right_m);
}
/*
 * Preorder Traversal of AVL Tree
 */
template <typename T, typename S>
void AvlTree<T,S>::preorder(avlNode<T,S> *tree)
{
    if (tree == NULL)
        return;
    cout<<tree->key_m<<"  ";
    preorder (tree->left_m);
    preorder (tree->right_m);

}

/*
 * Postorder Traversal of AVL Tree
 */
template <typename T, typename S>
void AvlTree<T,S>::postorder(avlNode<T,S> *tree)
{
    if (tree == NULL)
        return;
    postorder ( tree ->left_m );
    postorder ( tree ->right_m );
    cout<<tree->key_m<<"  ";
}
#endif //WET1_DATA_STRUCTURES_AvlTree_H
