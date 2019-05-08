//
// Created by Bar The magical on 25/04/2019.
//

#ifndef WET1_DATA_STRUCTURES_LIST_H
#define WET1_DATA_STRUCTURES_LIST_H

#include <stdlib.h>
#include <cassert>

template<typename T>
class Node {
public:
    T data_m;
    Node *next_m;
    Node *prev_m;

    Node(const T& data = T(), Node* prev = nullptr, Node* next = nullptr) : data_m(data), next_m(next), prev_m(prev){}
    ~Node(){
        if(next_m != nullptr){
            Node* temp = next_m;
            next_m = nullptr;
            delete temp;
        }
    }
};

template<typename T>
class List {
    Node<T> *head_m;
    int size_m;

public:

    List() {
        head_m = nullptr;
        size_m = 0;
    }

    List(const List &aList) {
        head_m = nullptr;
        size_m = 0;
        Node<T> *temp = aList.head_m;
        while (size_m != aList.size_m) {
            addLast(temp->data_m);
        }
    }

    ~List() {
        while (size_m > 0) {
            deleteNode(head_m);
        }
    }

    List &operator=(const List &aList) {
        if(this == &aList){
            return *this;
        }
        while (head_m != nullptr) {
            deleteNode(head_m);
        }

        if(aList.head_m == nullptr){
            return *this;
        }

        Node<T> *temp = aList.head_m;
        do {
            addLast(temp->data_m);
            temp = temp->next_m;
        } while (temp != aList.head_m);

        return *this;
    }

    Node<T> *
    addLast(const T &value) { //adds node to the end, returns a pointer to it;
        auto *temp = new Node<T>(value);

        if (head_m == nullptr) {
            assert(size_m == 0);
            head_m = temp;
        }
        else if(size_m == 1){
            head_m->next_m = temp;
            head_m->prev_m = temp;
            temp->next_m = head_m;
            temp->prev_m = head_m;
        }
        else {
            Node<T>* tail = head_m->prev_m;
            assert(tail != nullptr);
            tail->next_m = temp;
            head_m->prev_m = temp;
            temp->prev_m = tail;
            temp->next_m = head_m;
        }
        size_m++;
        return temp;
    }


    void deleteNode(Node<T>* node) { //deletes a given node in the list
        assert(size_m != 0);
        Node<T>* next = node->next_m;
        Node<T>* prev = node->prev_m;
        node->next_m = nullptr;
        node->prev_m = nullptr;

        if(size_m == 1){
            delete node;
            head_m = nullptr;
            size_m--;
            return;
        }
        if(size_m == 2){
            assert(prev == next);
            head_m = next;
            head_m->next_m = nullptr;
            head_m->prev_m = nullptr;
            delete node;
            size_m--;
            return;
        }

        assert(prev != nullptr && next != nullptr);
        prev->next_m = next;
        next->prev_m = prev;
        if(node == head_m){
            head_m = next;
        }

        delete node;
        size_m--;
    }

    void appendList(const List &aList) {
        int firstListSize = size_m;
        Node<T> *iterator = aList.head_m;
        while (iterator != nullptr &&
               size_m != firstListSize + aList.size_m) {
            addLast(iterator->data_m);
            iterator = iterator->next_m;
        }
    }

    bool isEmpty() {
        return size_m == 0;
    }

    void moveNodeToEnd(Node<T> *node) {
        if(size_m == 1){
            return;
        }
        if(node == head_m){
            head_m = node->next_m;
            return;
        }
        if(size_m == 2){
            //node is not head and there is only one other node
            return;
        }

        node->prev_m->next_m = node->next_m;
        node->next_m->prev_m = node->prev_m;

        Node<T>* tail = head_m->prev_m;
        tail->next_m = node;
        node->prev_m = tail;
        node->next_m = head_m;
        head_m->prev_m = node;
    }

    void moveNodeToStart(Node<T> *node) {
        if(size_m == 1 || head_m == node){
            return;
        }
        if(size_m == 2){
            head_m = node;
            return;
        }

        node->prev_m->next_m = node->next_m;
        node->next_m->prev_m = node->prev_m;

        Node<T>* tail = head_m->prev_m;
        tail->next_m = node;
        node->prev_m = tail;
        node->next_m = head_m;
        head_m->prev_m = node;
        head_m = node;
    }

    int &getSize() {
        return size_m;
    }

    Node<T> *getHead() const {
        return head_m;
    }

    Node<T> *getHead() {
        return head_m;
    }

};


#endif //WET1_DATA_STRUCTURES_LIST_H
