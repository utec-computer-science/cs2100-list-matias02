#ifndef CIRCULAR_H
#define CIRCULAR_H

#include <algorithm>
#include <iostream>

#include "List.h"
#include "Bidirectional_Iterator.h"

using namespace std;

template <typename T>
class CircularLinkedList : public List<T> {
public:
    CircularLinkedList() : List<T>() {}

    T front() {
        if ( empty() ) {
            throw runtime_error("TimeOut");
        }
        return this->head->data;
    }

    T back() {
        if ( empty() ) {
            throw runtime_error("TimeOut");
        }
        //return this->tail->data;
        return this->head->data;
    }

    void push_front(T value) {
        auto *tmp = new Node<T>;
        if(this->nodes == 0){
            tmp->next = tmp;
            tmp->prev = tmp;
            this->head=tmp;
            //this->tail=this->head;
        }
        else{
            tmp->next = this->head;
            this->head->prev = tmp;
            this->head = tmp;
            this->head->prev = this->tail;
            //this->tail->next = this->head;
        }
        tmp->data = value;
        ++this->nodes;
    }

    void push_back(T value) {
        auto *tmp = new Node<T>;
        if(this->nodes == 0){
            tmp->next = tmp;
            tmp->prev = tmp;
            this->head = tmp;
            this->tail = this->head;
        }
        else{
            tmp->prev = this->tail;
            this->tail->next = tmp;
            this->tail = tmp;
            this->head->prev = this->tail;
            this->tail->next = this->head;
        }
        tmp->data = value;
        ++this->nodes;
    }

    void pop_front() {
        if(empty()){
            this->head=nullptr;
            this->tail=nullptr;
        }
        else{
            Node<T> *tmp = this->head->next;
            delete this->head;
            this->head = tmp;
            this->head->prev = this->tail;
            this->tail->next = this->head;
            --this->nodes;
        }
    }

    void pop_back() {
        if(this->nodes == 0){
            this->head = nullptr;
            this->tail = nullptr;
        }
        else{
            Node<T> *tmp = this->tail->prev;
            delete this->tail;
            this->tail = tmp;
            this->head->prev = this->tail;
            this->tail->next = this->head;
            --this->nodes;
        }
    }

    T operator[](int index) {
        if (index > size()){
            throw runtime_error("TimeOut");
        }
        Node<T> *tmp = this->head;
        for (int i = 0; i < index; i++)
            tmp = tmp->next ;
        return tmp->data ;
    }

    bool empty() {
        return (this->nodes == 0);
    }

    int size() {
        return this->nodes;
    }

    void clear() {
        this->head->killSelf(this->nodes);
        this->head = nullptr;
        this->tail = nullptr;
        this->nodes=0;
    }

    void sort() {
        Node<T> *first = this->head;
        T* array = new T[this->nodes];

        for(int i = 0; i < this->nodes; i++)
        {
            array[i] = first->data;
            first = first->next;
        }
        std::sort(array, array+this->nodes);
        first = this->head;

        for (int i = 0; i < size(); i++)
        {
            first->data = array[i];
            first = first->next;
        }
        delete[] array;
    }

    void reverse() {
        if (size() <= 1) {
            return;
        }
        Node<T> *actualNode = this->head;
        Node<T> *tmp = NULL;
        while(actualNode!= nullptr)
        {
            tmp = actualNode->next;
            actualNode->next = actualNode->prev;
            actualNode->prev = tmp;
            actualNode = tmp;
        }
        swap(this->head,this->tail);
    }

    string name() {
        return "Circular Linked List";
    }

    BidirectionalIterator<T> begin() {
        return BidirectionalIterator<T>(this->head);
    }

    BidirectionalIterator<T> end() {
        return BidirectionalIterator<T> (this->head);
    }

    void merge(CircularLinkedList<T> list) {
        if (list.empty()){
            return;
        }
        if (size() == 0)
            return;
        else
        {
            this->tail->next = list.head;
            list.head->prev = this->tail;
            this->tail = list.tail;
            this->tail->next = this->head;
        }
        this->nodes = this->nodes+list.nodes;
    }
};

#endif