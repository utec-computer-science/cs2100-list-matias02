#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next; // puntero next node
    Node<T>* prev; // puntero prev node

    void killSelf(int count) { // destructor
        if (count > 1){
            next->killSelf(count-1);
        }
        delete next;
    }
};

#endif