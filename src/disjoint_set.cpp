#include "disjoint_set.h"

template <class T>
Node<T> *DisjointSet<T>::makeSet(Node<T> *root) {
    root->parent = root;
    root->rank = 0;
    return root;
}

template <class T>
Node<T>* DisjointSet<T>::findSet(Node<T>* root) {
    if (root->parent != root) {
        root->parent = findSet(root->parent);
    }
    return root->parent;
}

template <class T>
void DisjointSet<T>::unionSet(Node<T>* x, Node<T>* y) {
    Node<T>* xRoot = findSet(x);
    Node<T>* yRoot = findSet(y);

    if (xRoot == yRoot) return;

    if (xRoot->rank < yRoot->rank) {
        xRoot->parent = yRoot;
    } else if (xRoot->rank > yRoot->rank) {
        yRoot->parent = xRoot;
    } else {
        yRoot->parent = xRoot;
        ++xRoot->rank;
    }
}

template class DisjointSet<int>;
template class DisjointSet<char>;
template class DisjointSet<std::string>;
