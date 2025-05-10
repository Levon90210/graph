#include "node.h"

template <class T>
Node<T>::Node(const T& value) : value(value) {}

template class Node<int>;
template class Node<char>;