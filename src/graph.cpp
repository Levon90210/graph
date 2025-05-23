#include "graph.h"


template <class T, class L>
Graph<T, L>::Graph() : m_allNodes(), m_inEdges(), m_outEdges() {}

template <class T, class L>
Graph<T, L>::Graph(const Matrix<T, L>& m) { // Matrix<T, L> = std::unordered_map<T, std::unordered_map<T, L>>
    for (const auto& [source, neighbors] : m) {
        addNode(source);
        for (const auto& [destination, weight] : neighbors) {
            addNode(destination);
            addEdge(source, destination, weight);
        }
    }
}

// template <class T, class L>
// Graph<T, L>::Graph(const AdjList<T>& adj) {
//     for (int i = 0; i < adj.size(); ++i) {
//         addNode(i);
//     }
//
//     for (int i = 0; i < adj.size(); ++i) {
//         for (const auto& v : adj[i]) {
//             addEdge(i, v, 0);
//         }
//     }
// }

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
    m_outEdges[source].insert(newEdge);
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
std::unordered_map<T, std::vector<T>> Graph<T, L>::getShortestPaths(const T& start) {
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

        if (currDist > distances[currNode]) {
            continue;
        }

        for (const auto &edge : m_outEdges[currNode]) {
            auto nextNode = edge.destination->value;
            if (currDist + edge.label < distances[nextNode]) {
                distances[nextNode] = currDist + edge.label;
                previous[nextNode] = m_allNodes[currNode];
                pq.push({distances[nextNode], nextNode});
            }
        }
    }

    std::unordered_map<T, std::vector<T>> paths;
    for (const auto& [value, _] : m_allNodes) {
        if (distances[value] == std::numeric_limits<L>::max()) {
            continue;
        }

        std::vector<T> path;
        T current = value;

        while (previous[current] != nullptr) {
            path.push_back(current);
            current = previous[current]->value;
        }

        path.push_back(start);
        std::reverse(path.begin(), path.end());

        paths[value] = path;
    }
    return paths;
}

template <class T, class L>
Matrix<T, L> Graph<T, L>::floydWarshall() { // Matrix<T, L> = std::unordered_map<T, std::unordered_map<T, L>>
    Matrix<T, L> distances;

    for (const auto& [val1, _] : m_allNodes) {
        for (const auto& [val2, _] : m_allNodes) {
            if (val1 != val2) {
                distances[val1][val2] = std::numeric_limits<L>::max();
            } else {
                distances[val1][val2] = 0;
            }
        }
    }

    for (const auto& [val, edges] : m_outEdges) {
        for (const auto& edge : edges) {
            distances[val][edge.destination->value] = edge.label;
        }
    }

    for (const auto& [k, _] : m_allNodes) {
        for (const auto& [i, _] : m_allNodes) {
            for (const auto& [j, _] : m_allNodes) {
                if (distances[i][k] != std::numeric_limits<L>::max() &&
                    distances[k][j] != std::numeric_limits<L>::max())
                {
                    distances[i][j] = std::min(distances[i][j], distances[i][k] + distances[k][j]);
                }

            }
        }
    }

    return distances;
}

template <class T, class L>
std::vector<Edge<T, L>> Graph<T, L>::getUndirectedEdges() const {
    std::vector<Edge<T, L>> edges;
    std::set<std::pair<T, T>> visited;
    for (const auto& [val, node] : m_allNodes) {
        for (const auto& edge : m_outEdges.at(val)) {
            T u = edge.source->value;
            T v = edge.destination->value;
            if (u > v) std::swap(u, v);
            if (!visited.contains({u, v})) {
                visited.emplace(u, v);
                edges.push_back(edge);
            }
        }
    }
    return edges;
}

template <class T, class L>
std::vector<std::pair<T, T>> Graph<T, L>::mstKruskal() {
    auto edges = getUndirectedEdges();

    for (const auto& [val, node] : m_allNodes) {
        DisjointSet<T>::makeSet(node);
    }

    std::sort(edges.begin(), edges.end(), [](Edge<T, L> a, Edge<T, L> b) {
        return a.label < b.label;
    });


    std::vector<std::pair<T, T>> results;
    for (const auto& edge : edges) {
        Node<T>* srcRoot = DisjointSet<T>::findSet(edge.source);
        Node<T>* destRoot = DisjointSet<T>::findSet(edge.destination);

        if (srcRoot != destRoot) {
            results.push_back({edge.source->value, edge.destination->value});
            DisjointSet<T>::unionSet(destRoot, srcRoot);
        }
    }

    return results;
}

template class Graph<int, int>;
template class Graph<char, int>;
template class Graph<std::string, int>;