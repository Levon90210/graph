#ifndef NODE_H
#define NODE_H

enum Color {WHITE, GRAY, BLACK};

template <class T>
class Node {
public:
    T value;
    Color color = WHITE;

    explicit Node(const T& value);
};

#endif //NODE_H
