#ifndef FORWARD_H
#define FORWARD_H

#include <algorithm>
#include <iostream>
#include "List.h"
#include "Foward_Iterator.h"

template <typename T>
class ForwardList : public List<T> {
public:
    ForwardList() : List<T>() {}

    T front() {
        if ( empty() ) {
            throw runtime_error("Empty list!");
        }
        return this->head->data;
    }

    T back() {
        if ( empty() ) {
            throw runtime_error("Empty list!");
        }
        return this->tail->data;
    }

    void push_front(T value) {
        auto *tmp = new Node<T>;
        if(empty()){
            this->head = nullptr;
            this->tail = nullptr;
        }
        else{
            tmp->next = this->head;
            this->head = tmp;
        }
        tmp->data = value;
        ++this->nodes;
    }

    void push_back(T value) {
        auto *tmp = new Node<T>;
        if(empty()){
            this->head = nullptr;
            this->tail = nullptr;
        }
        else{
            this->tail-> next = tmp;
        }
        this->tail = tmp;
        tmp->data = value;
        tmp->next = nullptr;
        ++this->nodes;
    }

    void pop_front() {
        if (!empty())
        {
            auto *tmp = this->head->next;
            delete this->head;
            this->head = tmp;
            --this->nodes;
        }
    }

    void pop_back() {
        if ( empty() ) { throw runtime_error("Empty list!"); }
        else
        {
            auto *tmp = this->head;
            while (tmp->next != this->tail)
            {
                tmp = tmp->next;
            }
            this->tail = tmp;
            delete this->tail;
            this->tail->next = nullptr;
            --this->nodes;
        }
    }

    T operator[](int index) {
        if (index > size())
            throw runtime_error("Empty list!");
        auto *tmp = this->head;
        int i=0;
        while(i<index)
        {
            tmp = tmp->next ;
            i++;
        }
        return tmp->data ;
    }

    bool empty() {
        return (this -> nodes == 0);
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

        for(int i = 0; i< size(); i++)
        {
            array[i]=first -> data;
            first = first -> next;
        }
        int n = sizeof(array)/sizeof(array[0]);
        std::sort(array, array+n);
        first=this -> head;

        for (int i = 0; i < size(); i++)
        {
            first-> data = array[i];
            first = first -> next;
        }

        delete[] array;
    }

    void reverse() {
        if (size() <= 1) {
            return;
        }
        else{
            Node<T> *prevNode = NULL;
            Node<T> *actualNode = this->head;
            Node<T> *tmp = NULL;
            for (int i = 0; i < size(); i++)
            {
                tmp = actualNode -> next;
                actualNode -> next= prevNode;
                prevNode = actualNode;
                actualNode = tmp;
            }
        }
    }

    string name() {
        return "Forward List";
    }

    ForwardIterator<T> begin() {
        return ForwardIterator<T> (this->head);
    }

    ForwardIterator<T> end() {
        return ForwardIterator<T> (NULL);
    }

    void merge(ForwardList<T> list) {
        if (list.empty())
        {
            return;
        }
        else
        {
            this->tail->next = list.head;
            this->tail = list.tail;
        }
        this->nodes = this->nodes+list.nodes;
    }
};

#endif