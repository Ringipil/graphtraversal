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
    void addVertex(int u);
    vector<int> getAdjacencyList(int u); // Method to retrieve adjacency list

    std::unordered_map<int, vector<int>>& getAllAdjacencyLists() ;

    bool isDirected() const;
    void resetGraph();
    void bfs(int startNode, function<void(int, const string&)> stepCallback);
    void dfs(int startNode, std::function<void(int, const std::string&, const std::string&)> stepCallback);  // Updated signature
    bool vertexExists(int u) const;

    int getDiscoveryTime(int u);

    // Method to retrieve finish time of a vertex
    int getFinishTime(int u);

    // Method to classify edges based on DFS traversal
    std::unordered_map<std::string, std::vector<std::pair<int, int>>> classifyEdges();

private:
    unordered_map<int, vector<int>> adjList; // Adjacency list representation
    bool directed; // Flag for directed or undirected graph
    std::unordered_map<int, int> discoveryTime;
    std::unordered_map<int, int> finishTime;

    int currentTime;

    void dfsVisit(int node, std::unordered_map<int, std::string>& color, std::function<void(int, const std::string&)>& callback);
};

#endif // GRAPH_H