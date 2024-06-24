#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <set>
#include <functional>
#include <queue>
#include <iostream>

using namespace std;

class Graph {
public:
    Graph(bool directed = false); // Constructor

    void addEdge(int u, int v); // Method to add an edge
    vector<int> getAdjacencyList(int u); // Method to retrieve adjacency list

    const unordered_map<int, vector<int>>& getAllAdjacencyLists() const;

    bool isDirected() const;

    void bfs(int startNode, function<void(int, const string&)> stepCallback);

private:
    unordered_map<int, vector<int>> adjList; // Adjacency list representation
    bool directed; // Flag for directed or undirected graph
};

#endif // GRAPH_H
