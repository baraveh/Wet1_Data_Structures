//
// Created by Bar The magical on 25/04/2019.
//

#ifndef WET1_DATA_STRUCTURES_LIST_H
#define WET1_DATA_STRUCTURES_LIST_H

#include <stdlib.h>

template <typename T>
struct Node{
    T data_m;
    Node* next_m;
};

template <typename T>
class List {
   Node<T>* head_m, tail_m;

public:

    List(){
        head_m = NULL;
        tail_m = NULL;
    }

    List(const List& aList){
        Node<T>* temp = aList.head_m;
        while(temp!= NULL){
            addNode(temp->data_m);
            temp = temp->next_m;
        }
    }

    ~List(){
        while(head_m != NULL) {
            T temp = tail_m.data_m;
            deleteNode(temp);
        }
    }

    void addNode(const T& value){ //adds node to the end
        Node<T>* temp = new Node<T>;
        temp->data_m = value;
        temp->next_m = NULL;

        if(head_m == NULL){
            head_m = temp;
            tail_m = temp;
        }
        else{
            tail_m->next_m = temp;
            tail_m = tail_m->next_m;
        }
    }

    Node<T>*& getHead(){
        return head_m;
    }

    void deleteNode (const T& value){ //deletes a node if it exists
        if(head_m == NULL){
            return;
        }

        if(head_m->data_m == value){
            Node<T>* temp = head_m;
            head_m = temp->next_m;
            delete temp;
            return;
        }

        Node<T>* prev = head_m;
        Node<T>* curr = head_m->next_m;
        while(curr != NULL){
            if(curr->data_m == value){

                prev->next_m = curr->next_m;

                if(curr == tail_m){
                    tail_m = prev;
                }

                delete curr;
                return;
            }
            prev = curr;
            curr = prev->next_m;
        }
    }

    void appendList (const List& aList){
        Node<T>* temp = aList.head_m;
        while(temp!= NULL){
            addNode(temp->data_m);
            temp = temp->next_m;
        }
    }
};


#endif //WET1_DATA_STRUCTURES_LIST_H
