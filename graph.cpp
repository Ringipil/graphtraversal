#include "graph.h"
#include <stack>


// Constructor to initialize the graph with the directed/undirected property
Graph::Graph(bool directed) : directed(directed) {}

// Function to add an edge between nodes u and v
void Graph::addEdge(int u, int v) {
    adjList[u].push_back(v);
    if (!directed) {
        adjList[v].push_back(u);
    }
}

// Function to add a vertex to the graph
void Graph::addVertex(int u){
    adjList.emplace(u, vector<int>());
}

// Function to get the adjacency list of a node u
vector<int> Graph::getAdjacencyList(int u) {
    if (adjList.find(u) != adjList.end()) {
        return adjList[u];
    }
    return vector<int>(); // Return empty vector if no adjacency list for node
}

// Function to get all adjacency lists of the graph
std::unordered_map<int, vector<int>>& Graph::getAllAdjacencyLists() {
    return adjList;
}

// Function to check if the graph is directed
bool Graph::isDirected() const {
    return directed;
}

// Function to reset the graph
void Graph::resetGraph() {
    adjList.clear();
    discoveryTime.clear();
    finishTime.clear();
}

// Function to perform BFS traversal of the graph
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

// Function to check if a vertex exists in the graph
bool Graph::vertexExists(int u) const {
    return adjList.find(u) != adjList.end();
}

// Function to get the discovery time of a vertex
int Graph::getDiscoveryTime(int u) {
    return discoveryTime[u];
}

// Function to get the finish time of a vertex
int Graph::getFinishTime(int u) {
    return finishTime[u];
}

// Function to classify edges based on DFS traversal
void Graph::dfs(int startNode, std::function<void(int, const std::string&,const std::string&)> stepCallback) {
    std::stack<int> stack;
    std::unordered_map<int, std::string> status;
    std::unordered_map<int, int> discoveryTime;
    std::unordered_map<int, int> finishTime;
    std::set<std::pair<int, int>> classifiedEdges;


    int time = 0;

    // Initialize all nodes to white
    for (const auto& pair : adjList) {
        status[pair.first] = "white";
        discoveryTime[pair.first] = -1;
        finishTime[pair.first] = -1;
    }

    // Helper function to perform DFS visit
    auto dfsVisit = [&](int node) {
        stack.push(node);
        status[node] = "gray";
        discoveryTime[node] = ++time;
        stepCallback(node, "gray", "Discovered at time : " + std::to_string(discoveryTime[node]));

        // Perform DFS traversal
        while (!stack.empty()) {
            int currentNode = stack.top();
            bool allVisited = true;

            // Iterate over neighbors
            for (int neighbor : adjList[currentNode]) {
                if (status[neighbor] == "white") {
                    stack.push(neighbor);
                    status[neighbor] = "gray";
                    discoveryTime[neighbor] = ++time;
                    stepCallback(neighbor, "gray", "Discovered at time : " + std::to_string(discoveryTime[neighbor]));
                    allVisited = false;

                    // Handle tree edge (optional visualization logic)
                    if (classifiedEdges.find({currentNode, neighbor}) == classifiedEdges.end()) {
                        stepCallback(currentNode, "gray", "Tree edge to : " + std::to_string(neighbor));
                        classifiedEdges.insert({currentNode, neighbor});
                        if (!directed) {
                            classifiedEdges.insert({neighbor, currentNode});
                        }
                    }
                    break;

                } else if (status[neighbor] == "gray") {
                    // Handle back edge (optional visualization logic)
                    if (classifiedEdges.find({currentNode, neighbor}) == classifiedEdges.end()) {
                        stepCallback(currentNode, "gray", "Back edge to : " + std::to_string(neighbor));
                        classifiedEdges.insert({currentNode, neighbor});
                        if (!directed) {
                            classifiedEdges.insert({neighbor, currentNode});
                        }
                    }
                } else if (status[neighbor] == "black") {
                    if (discoveryTime[currentNode] < discoveryTime[neighbor]) {
                        // Classify as forward edge
                        if (classifiedEdges.find({currentNode, neighbor}) == classifiedEdges.end()) {
                            stepCallback(currentNode, "gray", "Forward edge to : " + std::to_string(neighbor));
                            classifiedEdges.insert({currentNode, neighbor});
                            if (!directed) {
                                classifiedEdges.insert({neighbor, currentNode});
                            }
                        }
                    } else {
                        // Classify as cross edge
                        if (classifiedEdges.find({currentNode, neighbor}) == classifiedEdges.end()) {
                            stepCallback(currentNode, "gray", "Cross edge to : " + std::to_string(neighbor));
                            classifiedEdges.insert({currentNode, neighbor});
                            if (!directed) {
                                classifiedEdges.insert({neighbor, currentNode});
                            }
                        }
                    }
                }
            }

            if (allVisited) {
                stack.pop();
                status[currentNode] = "black";
                finishTime[currentNode] = ++time;
                stepCallback(currentNode, "black", "Finished at time: " + std::to_string(finishTime[currentNode]));
            }
        }
    };

    // Perform DFS visit on the start node
    dfsVisit(startNode);

    // Ensure all nodes are visited
    for (const auto& pair : adjList) {
        int node = pair.first;
        if (status[node] == "white") {
            dfsVisit(node);
        }
    }
}
