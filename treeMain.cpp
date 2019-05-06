#include <iostream>
#include <assert.h>
#include <ctime> // temporary for random tests
#include "AVLTree.h"

#define magicNumber 200


void testAVLTree();
void testTreeBalance(AVLTree<int,int> &tree);
void testMerge(AVLTree<int,int> & mergedTree, AVLTree<int,int> &tree1, AVLTree<int,int> &tree2);

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

        for (int i = 1; i < 3000; i++) {
                testAVLTree();
        }
}

void testAVLTree(){


    AVLTree<int,int> tree;
    int amountToInsert=rand()%magicNumber+1; //generate random number in range [1,magicNumber]
    int range=2*magicNumber;    //keys inserted into the tree are in range [1,2*magicNumber]
    int t1 = 0;
    for(int i=1;i<amountToInsert;i++){
        int keyToInsert=rand()%range + 1; // random number in range [1,magicNumber*2]
        if(!tree.searchKey(keyToInsert)) {
            tree.insertElement(keyToInsert);
            t1++;
        }
        testTreeBalance(tree); //Extra: check if tree is correct after every insert
    }
   // tree.printInOrder();
    AVLTree<int,int> tree2;
    int amountToInsert2=rand()%magicNumber+1; //generate random number in range [1,magicNumber]
    int range2=2*magicNumber;    //keys inserted into the tree are in range [1,2*magicNumber]
    int t2 =0 ;
    for(int i=1;i<amountToInsert2;i++){
        int keyToInsert2=rand()%range2 + 1; // random number in range [1,magicNumber*2]
        if(!tree2.searchKey(keyToInsert2) && !tree.searchKey(keyToInsert2)) {
            tree2.insertElement(keyToInsert2);
            t2++;
        }
        testTreeBalance(tree); //Extra: check if tree is correct after every insert
    }
        AVLTree<int, int> treeA;
        treeA.mergeTrees(tree, tree2);
        int afterInsert = treeA.countNodesInTree();

            testMerge(treeA, tree, tree2);


           testTreeBalance(treeA);



        int elementsToRemove = rand() % (afterInsert + 1); // choose randomly how many nodes to remove from tree
        int r = 0;
        int removalCounter = elementsToRemove;
        while (removalCounter > 0) {
            assert(treeA.getRoot() != nullptr || treeA.getRoot() != NULL);
            int keyToRemove = rand() % range + 1; // random number in range [1,magicNumber*2]
            if (treeA.searchKey(keyToRemove)) {
                assert(treeA.getRoot() != nullptr || treeA.getRoot() != NULL);
                treeA.deleteElement(keyToRemove);
                removalCounter--;
                r++;

                testTreeBalance(treeA); //Extra: check if tree is correct after every removal
            }
        }
        int afterRemoval = treeA.countNodesInTree();
       assert(afterRemoval + elementsToRemove == afterInsert); //make sure no branches in tree are lost during removal


        testTreeBalance(tree);
        testTreeBalance(tree2);
        testTreeBalance(treeA);
    }

void testTreeBalance(AVLTree<int,int> &tree){
    assert(tree.checkIfBalanced());
    //check if tree's inorder is sorted correctly
    int nodesInTree=tree.countNodesInTree();
    int *arr=(int*)malloc((sizeof(*arr))*(nodesInTree));
    int *arr2 = (int*)malloc((sizeof(*arr))*(nodesInTree));
    tree.printTree(arr, arr2); //fill arr with the tree, by inorder.
    for(int i=1;i<nodesInTree;i++) {
        assert (arr[i] > arr[i - 1]);
    }

    free(arr);
    free(arr2);
}

void testMerge(AVLTree<int, int> &mergedTree, AVLTree<int, int> &tree1,
               AVLTree<int, int> &tree2) {
    int nodesInTree = mergedTree.countNodesInTree();
    int *mergedArrKeys=(int*)malloc((sizeof(*mergedArrKeys))*(nodesInTree));
    int *mergedArrValues= (int*)malloc((sizeof(*mergedArrValues))*(nodesInTree));
    mergedTree.printTree(mergedArrKeys, mergedArrValues);
    for(int i=0;i<nodesInTree;i++) {
        assert(tree1.searchKey(mergedArrKeys[i]) || tree2.searchKey(mergedArrKeys[i]));
    }

    free(mergedArrKeys);
    free(mergedArrValues);

    nodesInTree = tree1.countNodesInTree();
    int *tree1Keys=(int*)malloc((sizeof(*tree1Keys))*(nodesInTree));
    int *tree1Values = (int*)malloc((sizeof(*tree1Values))*(nodesInTree));
    tree1.printTree(tree1Keys, tree1Values);

    for(int i=0;i<nodesInTree;i++) {

        assert(mergedTree.searchKey(tree1Keys[i]));
    }

    free(tree1Keys);
    free(tree1Values);

    nodesInTree = tree2.countNodesInTree();
    int *tree2Keys=(int*)malloc((sizeof(*tree2Keys))*(nodesInTree));
    int *tree2Values = (int*)malloc((sizeof(*tree2Keys))*(nodesInTree));
    tree2.printTree(tree2Keys, tree2Values);
    for(int i=0;i<nodesInTree;i++) {
        assert(mergedTree.searchKey(tree2Keys[i]));
    }

    free(tree2Keys);
    free(tree2Values);
}



/* int main()
{

    AVLTree<int, int> tree1;
    tree1.insertElement(100,0);
    tree1.insertElement(50,0);
   tree1.insertElement(20,0);

    cout << "Following is Inorder traversal of tree 1 \n";
    tree1.printInOrder();


    AVLTree<int, int> tree2;
    tree2.insertElement(80,0);
    tree2.insertElement(40,0);
    tree2.insertElement(120,0);

    tree2.deleteElement(120);

    cout << "Following is Inorder traversal of tree 2 \n";
    tree2.printInOrder();

    AVLTree<int, int> mergedTree;
    mergedTree.mergeTrees(tree1, tree2);

    cout << "Following is Inorder traversal of the merged tree \n";
    mergedTree.printInOrder();

    mergedTree.insertElement(42);
    mergedTree.insertElement(420);
    mergedTree.insertElement(69);

    cout << "Following is Inorder traversal of the merged tree \n";
    mergedTree.printInOrder();



    return 0;
} */
