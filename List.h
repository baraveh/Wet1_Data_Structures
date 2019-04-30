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
    Node *prev_m;
};

template<typename T>
class List {
    Node<T> *head_m;
    Node<T> *tail_m;
    int size_m;

public:

    List() {
        head_m = nullptr;
        tail_m = nullptr;
        size_m = 0;
    }

    List(const List &aList) {
        head_m = nullptr;
        tail_m = nullptr;
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

        while (head_m != NULL) {
            deleteNode(head_m);
        }

        Node<T> *temp = aList.head_m;
        do {
            addLast(temp->data_m);
            temp = temp->next_m;
        } while (temp != aList.head_m);
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
        size_m++;
        return temp;
    }


    void deleteNode(const Node<T> *node) { //deletes a given node in the list
        if (node != nullptr && size_m > 0) {
            if (node == head_m) {
                head_m = node->next_m;
            }
            if (node == tail_m) {
                tail_m = node->prev_m;
            }
            node->prev_m->next_m = node->next_m;
            node->next_m->prev_m = node->prev_m;
            delete node;
            size_m--;
        }
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
        if (node == head_m) {
            head_m = node->next_m;
        }
        if (node == tail_m) {
            tail_m = node->prev_m;
        }
        node->prev_m->next_m = node->next_m;
        node->next_m->prev_m = node->prev_m;

        tail_m->next_m = node;
        head_m->prev_m = node;
        tail_m = node;
        head_m = node->next_m;
    }

    void moveNodeToStart(Node<T> *node) {
        if (node == head_m) {
            head_m = node->next_m;
        }
        if (node == tail_m) {
            tail_m = node->prev_m;
        }
        node->prev_m->next_m = node->next_m;
        node->next_m->prev_m = node->prev_m;

        tail_m->next_m = node;
        head_m->prev_m = node;
        head_m = node;
        tail_m = node->prev_m;
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

    Node<T> *getTail() const {
        return tail_m;
    }

    Node<T> *getTail() {
        return tail_m;
    }
};


#endif //WET1_DATA_STRUCTURES_LIST_H
