#ifndef NODE_H
#define NODE_H

#include <string>

enum Color {WHITE, GRAY, BLACK};

template <class T>
class Node {
public:
    T value;
    Color color = WHITE;
    Node<T> *parent =  nullptr;
    int rank = 0;

    explicit Node(const T& value);
};

#endif //NODE_H
