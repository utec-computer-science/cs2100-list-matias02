#ifndef LIST_H
#define LIST_H

#include "Node.h"
#include <string>

using namespace std;

template <typename T>
class List {
protected:
    Node<T>* head; // puntero a head
    Node<T>* tail; // puntero a tail
    int nodes; // nodos de la lista

public:
    List() : head(nullptr), tail(nullptr), nodes(0) {};

    virtual void push_front(T) = 0;
    virtual void push_back(T) = 0;
    virtual void pop_front() = 0;
    virtual void pop_back() = 0;
    virtual T front() = 0;
    virtual T back() = 0;
    virtual T operator[](int) = 0;
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual void sort() = 0;
    virtual void reverse() = 0;
    virtual string name() = 0;

    ~List() {
        // TODO
    }
};

#endif