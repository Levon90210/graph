#ifndef EDGE_H
#define EDGE_H
#include <bits/stdc++.h>
#include "node.h"

template <class T, class L>
class Edge {
public:
    Node<T>* source;
    Node<T>* destination;
    L label;

    Edge(Node<T>* source, Node<T>* destination, const L& label);

    bool operator==(const Edge<T, L>& other) const;
};

template <class T, class L>
class EdgeHash {
public:
    size_t operator()(const Edge<T, L>& e) const;
};

#endif //EDGE_H
