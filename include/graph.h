#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <forward_list>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include "edge.h"

template <class T, class L>
using Matrix = std::unordered_map<T, std::unordered_map<T, L>>;

template <class T>
using AdjList = std::vector<std::forward_list<T>>;

template <class T, class L>
class Graph {
    std::unordered_map<T, Node<T> *> m_allNodes;
    std::unordered_map<T, std::unordered_set<Edge<T, L>, EdgeHash<T, L> > > m_inEdges;
    std::unordered_map<T, std::unordered_set<Edge<T, L>, EdgeHash<T, L> > > m_outEdges;

    Node<T> *getNode(const T& data);

    void dfsVisit(const T& start);

    bool findPathDFS(const T& start, const T& end, std::vector<T>& path);

public:
    Graph();

    explicit Graph(const Matrix<T, L>& m);

    explicit Graph(const AdjList<T>& adj);

    bool addNode(const T& v);

    bool addEdge(const T& source, const T& dest, const L& label);

    std::unordered_set<T> getAllNodes() const;

    std::vector<T> getNextNodes(const T& nodeValue) const;

    std::vector<T> bfs(const T& start);

    void bfsPrint(const T& start);

    void dfsVisitAll();

    std::vector<T> findPath(const T& start, const T& end);

    std::unordered_map<T, std::vector<T>> getShortestPaths(const T& start);

    Matrix<T, L> floydWarshall();

    void printFloydWarshall() const;
};

#endif //GRAPH_H