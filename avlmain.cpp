//
// Created by ASUS on 4/22/2019.
//
#include "Avl.h"



void test_a (){
    AvlTree<int> a = AvlTree<int>(1,1);
    AvlTree<int> b = AvlTree<int>(2,1);
    AvlTree<int> c = AvlTree<int>(3,1);
    AvlTree<int> d = AvlTree<int>(4,1);
    AvlTree<int> e = AvlTree<int>(5,1);
    AvlTree<int> f = AvlTree<int>(6,1);
    AvlTree<int> g = AvlTree<int>(7,1);
    AvlTree<int> h = AvlTree<int>(8,1);
    AvlTree<int> i = AvlTree<int>(9,1);
    AvlTree<int> j = AvlTree<int>(10,1);
    AvlTree<int> k = AvlTree<int>(11,1);
    AvlTree<int> l = AvlTree<int>(12,1);
    AvlTree<int> m = AvlTree<int>(13,1);
    AvlTree<int> n = AvlTree<int>(14,1);
    AvlTree<int> o = AvlTree<int>(15,1);
    AvlTree<int> p = AvlTree<int>(16,1);
    AvlTree<int> q = AvlTree<int>(17,1);

    a.Avltree_add(e);
    a.Avltree_add(k);
    a.Avltree_add(l);
    a.Avltree_add(m);
    a.Avltree_add(n);
    a.Avltree_add(d);
    a.Avltree_add(f);
    a.Avltree_add(g);
    a.Avltree_add(h);
    a.Avltree_add(i);
    a.Avltree_add(o);
    a.Avltree_add(p);
    a.Avltree_add(b);
    a.Avltree_add(c);
    a.Avltree_add(q);
    a.Avltree_add(j);
    a.inorder(&a);
    a.Avltree_remove(17);
    a.Avltree_remove(10);
    a.Avltree_remove(12);
    a.Avltree_remove(8);
    a.inorder(&a);
}

int main() {

    test_a ();
    return 0;
}
