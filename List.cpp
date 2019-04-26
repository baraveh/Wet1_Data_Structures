//
// Created by Bar The magical on 25/04/2019.
//

#include "List.h"

int main(){
    List<int> list1;
    list1.addLast(1);
    list1.addLast(2);
    list1.addLast(3);

    List<int> list2;
    list2.appendList(list1);

    List<int> List3 = List<int>(list2);
    Node<int>* potato = List3.addLast(3);
    List3.deleteNode(potato);

}