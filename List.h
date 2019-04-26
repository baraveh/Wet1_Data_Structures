//
// Created by Bar The magical on 25/04/2019.
//

#ifndef WET1_DATA_STRUCTURES_LIST_H
#define WET1_DATA_STRUCTURES_LIST_H

#include <stdlib.h>

template<typename T>
struct Node {
    T data_m;
    Node *next_m;
    Node * prev_m;
};

template<typename T>
class List {
    Node<T> *head_m;
    Node<T> *tail_m;
    int size;

public:

    List() {
        head_m = NULL;
        tail_m = NULL;
        size = 0;
    }

    List(const List &aList) {
        head_m = NULL;
        tail_m = NULL;
        size = 0;
        Node<T> *temp = aList.head_m;
        do{
            addLast(temp->data_m);
            temp= temp->next_m;
        } while(temp != aList.head_m);
    }

    ~List() {
        while (size > 0) {
           deleteNode(head_m);
        }
    }

    List &operator=(const List &aList) {

        while (head_m != NULL) {
            deleteNode(head_m);
        }

        Node<T> *temp = aList.head_m;
        do{
            addLast(temp->data_m);
            temp= temp->next_m;
        } while(temp != aList.head_m);
    }

    Node<T> *
    addLast(const T &value) { //adds node to the end, returns a pointer to it;
        auto *temp = new Node<T>;
        temp->data_m = value;
        temp->next_m = NULL;
        temp->prev_m = NULL;

        if (head_m == NULL) {
            head_m = temp;
            tail_m = temp;
            head_m->prev_m = tail_m;
            head_m->next_m = tail_m;
            tail_m->prev_m = head_m;
            tail_m->next_m = head_m;
        } else {
            tail_m->next_m = temp;
            head_m->prev_m = temp;
            temp->prev_m = tail_m;
            temp->next_m = head_m;
            tail_m = temp;
        }
        size++;
        return temp;
    }

    
    void deleteNode(const Node<T>* node){ //deletes a given node in the list
       if(node != nullptr && size > 0) {
           if(node == head_m){
               head_m = node->next_m;
           }
           if(node == tail_m){
               tail_m = node->prev_m;
           }
           node->prev_m->next_m = node->next_m;
           node->next_m->prev_m = node->prev_m;
           delete node;
           size--;
       }
    }

    void appendList(const List &aList) {
        Node<T> *temp = aList.head_m;
        do{
            addLast(temp->data_m);
            temp= temp->next_m;
        } while(temp != aList.head_m);
    }
};


#endif //WET1_DATA_STRUCTURES_LIST_H
