#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include "node.h"

template <class T>
class DisjointSet {
public:
    static Node<T> *makeSet(Node<T> *root);

    static Node<T> *findSet(Node<T> *root);

    static void unionSet(Node<T> *x, Node<T> *y);
};

#endif //DISJOINT_SET_H
