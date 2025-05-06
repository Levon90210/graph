#include "graph.h"

template <class T, class L>
Graph<T, L>::Graph(const Matrix<T>& m) {
    for (int i = 0; i < m.size(); ++i) {
        addNode(i);
    }

    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < m.size(); ++j) {
            if (m[i][j] == 1) {
                addEdge(i, j, 0);
            }
        }
    }
}

template <class T, class L>
Graph<T, L>::Graph(const AdjList<T>& adj) {
    for (int i = 0; i < adj.size(); ++i) {
        addNode(i);
    }

    for (int i = 0; i < adj.size(); ++i) {
        for (const auto& v : adj[i]) {
            addEdge(i, v, 0);
        }
    }
}

template <class T, class L>
bool Graph<T, L>::addNode(const T& v) {
    if (m_allNodes.contains(v)) {
        return false;
    }
    m_allNodes[v] = new Node<T>(v);
    return true;
}

template <class T, class L>
Node<T> *Graph<T, L>::getNode(const T& data) {
    return m_allNodes.at(data);
}

template <class T, class L>
bool Graph<T, L>::addEdge(const T& source, const T& dest, const L& label) {
    if (!m_allNodes.contains(source) || !m_allNodes.contains(dest)) {
        return false;
    }
    auto sourceNode = getNode(source);
    auto destNode = getNode(dest);
    Edge<T, L> newEdge(sourceNode, destNode, label);
    if (m_inEdges[dest].find(newEdge) != m_inEdges[dest].end()) {
        return false;
    }
    m_inEdges[dest].insert(newEdge);
    m_OutEdges[source].insert(newEdge);
    return true;
}

template <class T, class L>
std::unordered_set<T> Graph<T, L>::getAllNodes() const {
    std::unordered_set<T> nodes;
    for (const auto &node: m_allNodes) {
        nodes.insert(node.first);
    }
    return nodes;
}

template <class T, class L>
std::vector<T> Graph<T, L>::getNextNodes(const T& nodeValue) const {
    std::vector<T> nextNodes;
    auto it = m_outEdges.find(nodeValue);
    if (it != m_outEdges.end()) {
        for (const auto &edge: it->second) {
            nextNodes.push_back(edge.destination->value);
        }
    }
    return nextNodes;
}

template <class T, class L>
std::vector<T> Graph<T, L>::bfs(const T& start) {
    std::vector<T> results;
    std::unordered_map<T, bool> visited;
    std::queue<T> queue;
    visited[start] = true;
    queue.push(start);
    while (!queue.empty()) {
        T current = queue.front();
        queue.pop();
        results.push_back(current);
        for (auto adjacentNodes = getNextNodes(current); const auto& node : adjacentNodes) {
            if (!visited[node]) {
                visited[node] = true;
                queue.push(node);
            }
        }
    }
    return results;
}

template <class T, class L>
void Graph<T, L>::bfsPrint(const T& start) {
    for (std::vector<T> results = bfs(start); const auto &result: results) {
        std::cout << result << " ";
    }
    std::cout << std::endl;
}

template <class T, class L>
void Graph<T, L>::dfsVisit(const T& start) {
    m_allNodes[start]->color = GRAY;
    for (const auto &next: getNextNodes(start)) {
        if (m_allNodes[next]->color == WHITE) {
            dfsVisit(next);
        }
    }
    m_allNodes[start]->color = BLACK;
}

template <class T, class L>
void Graph<T, L>::dfsVisitAll() {
    for (const auto &node : m_allNodes) {
        node.second->color = WHITE;
    }

    for (const auto &node: m_allNodes) {
        if (node.second->color == WHITE) {
            dfsVisit(node.first);
        }
    }
}

template <class T, class L>
bool Graph<T, L>::findPathDFS(const T& start, const T& end, std::vector<T>& path) {
    m_allNodes[start]->color = GRAY;
    path.push_back(start);
    for (const auto& next : getNextNodes(start)) {
        if (next == end) {
            path.push_back(end);
            return true;
        }
        if (m_allNodes[next]->color == WHITE) {
            if (findPathDFS(next, end, path)) {
                return true;
            }
        }
    }
    path.pop_back();
    return false;
}

template <class T, class L>
std::vector<T> Graph<T, L>::findPath(const T& start, const T& end) {
    std::vector<T> path;
    for (const auto &node : m_allNodes) {
        node.second->color = WHITE;
    }

    if (findPathDFS(start, end, path)) {
        return path;
    }
    return {};
}

template <class T, class L>
std::vector<std::vector<T>> Graph<T, L>::getShortestPaths(const T& start) {
    std::unordered_map<T, L> distances;
    std::unordered_map<T, Node<T>*> previous;
    for (const auto &[val, node] : m_allNodes) {
        distances[val] = std::numeric_limits<L>::max();
        previous[val] = nullptr;
    }

    std::priority_queue<std::pair<L, T>, std::vector<std::pair<L, T>>, std::greater<>> pq;
    distances[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [currDist, currNode] = pq.top();
        pq.pop();
        for (const auto &edge : m_outEdges[currNode]) {
            auto nextNode = edge.destination->value;
            if (currDist + edge.label < distances[nextNode]) {
                distances[nextNode] = currDist + edge.label;
                previous[nextNode] = currNode;
                pq.push({distances[nextNode], nextNode});
            }
        }
    }

    std::vector<std::vector<T>> paths;
    for (const auto &[val, node] : m_allNodes) {
        std::vector<T> path;
        while (node != nullptr) {
            path.push_back(node->value);
            node = previous[node->value];
        }
        std::reverse(path.begin(), path.end());
    }

    return paths;
}


template class Graph<int, int>;