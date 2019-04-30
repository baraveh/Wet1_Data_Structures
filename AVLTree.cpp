//
// Created by Bar on 29-Apr-19.
//

#include "AVLTree.h"


int main(){

    AVLTree<int,int> t;

    std::cout << "Inserting integer values 1 to 10" << std::endl;
    for (int i = 1; i <= 10; ++i)
        t.insert(i,0);

    std::cout << "Printing balance: ";
    t.printBalance();
}