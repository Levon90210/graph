#include "edge.h"

template <class T, class L>
Edge<T, L>::Edge(Node<T>* source, Node<T>* destination, const L& label)
: source(source), destination(destination), label(label) {}

template <class T, class L>
bool Edge<T, L>::operator==(const Edge<T, L>& other) const {
    return source == other.source
           && destination == other.destination
           && label == other.label;
}

template <class T, class L>
size_t EdgeHash<T, L>::operator()(const Edge<T, L>& e) const {
    return std::hash<T>()(e.source->value)
         ^ (std::hash<T>()(e.destination->value) << 1)
         ^ (std::hash<L>()(e.label) << 2);
}

template class Edge<int, int>;
template class EdgeHash<int, int>;
template class Edge<char, int>;
template class EdgeHash<char, int>;
template class Edge<std::string, int>;
template class EdgeHash<std::string, int>;