#include <iostream>
#include <assert.h>
#include <ctime> // temporary for random tests
#include "AVLTree.h"

#define magicNumber 50


void testAVLTree();
void testTreeBalance(AVLTree<int,int> &tree);

/*
 * Tree class should have:
 *      searchKey(int key) - return true/false, if [key] is already in tree
 *      insertElement(int key)
 *      deleteElement(int key)
 *      countNodesInTree - returns int; #nodes in tree
 *      checkIfBalance() - returns true/false, if tree is balance
 *      printTree(int *arr, (enum)InOrder) - scan the tree inorder and put the results inside arr.
 *          if the tree is valid binary search tree then arr should return sorted.
 */

int main() {
    srand(time(NULL)); //for random numbers in tests
    for(int i=1;i < 5;i++)
        testAVLTree();
}

void testAVLTree(){

    AVLTree<int,int> tree;
    int amountToInsert=rand()%magicNumber+1; //generate random number in range [1,magicNumber]
    int range=2*magicNumber;    //keys inserted into the tree are in range [1,2*magicNumber]
    int t1 = 0;
    for(int i=1;i<amountToInsert;i++){
        int keyToInsert=rand()%range + 1; // random number in range [1,magicNumber*2]
        if(!tree.searchKey(keyToInsert))
            tree.insertElement(keyToInsert);
            t1++;
        testTreeBalance(tree); //Extra: check if tree is correct after every insert
    }
    AVLTree<int,int> tree2;
    int amountToInsert2=rand()%magicNumber+1; //generate random number in range [1,magicNumber]
    int range2=2*magicNumber;    //keys inserted into the tree are in range [1,2*magicNumber]
    int t2 =0 ;
    for(int i=1;i<amountToInsert2;i++){
        int keyToInsert2=rand()%range2 + 1; // random number in range [1,magicNumber*2]
        if(!tree2.searchKey(keyToInsert2) && !tree.searchKey(keyToInsert2))
            tree2.insertElement(keyToInsert2);
            t2++;
        testTreeBalance(tree); //Extra: check if tree is correct after every insert
    }
    AVLTree<int,int> treeA;
    treeA.mergeTrees (tree,tree2);
    assert(treeA.countNodesInTree() == tree.countNodesInTree() + tree2.countNodesInTree());

    testTreeBalance(tree);

    int afterInsert = treeA.countNodesInTree();

    int elementsToRemove=rand()%(afterInsert+1); // choose randomly how many nodes to remove from tree
    int r =0;
    int removalCounter=elementsToRemove;
    while(removalCounter > 0){
        assert(treeA.getRoot() != nullptr || treeA.getRoot() != NULL);
        int keyToRemove=rand()%range + 1; // random number in range [1,magicNumber*2]
        if(treeA.searchKey(keyToRemove)){
            assert(treeA.getRoot() != nullptr || treeA.getRoot() != NULL);
            treeA.deleteElement(keyToRemove);
            removalCounter--;
            r++;

            testTreeBalance(tree); //Extra: check if tree is correct after every removal
        }
    }
    int afterRemoval=treeA.countNodesInTree();
    assert(afterRemoval+elementsToRemove==afterInsert); //make sure no branches in tree are lost during removal


    testTreeBalance(tree);
    testTreeBalance(tree2);
    testTreeBalance(treeA);
}

void testTreeBalance(AVLTree<int,int> &tree){

    assert(tree.checkIfBalanced());

    //check if tree's inorder is sorted correctly
    int nodesInTree=tree.countNodesInTree();
    int *arr=(int*)malloc((sizeof(*arr))*nodesInTree);
    int *arr2 = (int*)malloc((sizeof(*arr))*nodesInTree);
    tree.printTree(arr, arr2); //fill arr with the tree, by inorder.
    bool isSorted=true;
    for(int i=1;i<nodesInTree;i++)
        if(arr[i]< arr[i-1])
            isSorted = false;

    assert(isSorted);
    free(arr);
    free(arr2);
}
