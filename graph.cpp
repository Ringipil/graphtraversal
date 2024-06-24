#include "graph.h"

Graph::Graph(bool directed) : directed(directed) {}

void Graph::addEdge(int u, int v) {
    adjList[u].push_back(v);
    if (!directed) {
        adjList[v].push_back(u);
    }
}

vector<int> Graph::getAdjacencyList(int u) {
    if (adjList.find(u) != adjList.end()) {
        return adjList[u];
    }
    return vector<int>(); // Return empty vector if no adjacency list for node
}

const unordered_map<int, vector<int>>& Graph::getAllAdjacencyLists() const {
    return adjList;
}

bool Graph::isDirected() const {
    return directed;
}

void Graph::bfs(int startNode, function<void(int, const string&)> stepCallback) {
    unordered_map<int, string> color;
    queue<int> q;

    for (const auto& pair : adjList) {
        color[pair.first] = "white";
    }

    color[startNode] = "gray";
    q.push(startNode);
    stepCallback(startNode, "gray");

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adjList[u]) {
            if (color[v] == "white") {
                color[v] = "gray";
                q.push(v);
                stepCallback(v, "gray");
            }
        }
        color[u] = "black";
        stepCallback(u, "black");
    }
}
