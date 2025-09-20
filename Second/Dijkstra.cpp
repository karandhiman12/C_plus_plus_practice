#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <iomanip>

using namespace std;

// Structure to represent a weighted edge
struct Edge {
    int destination;
    int weight;
    
    Edge(int dest, int w) : destination(dest), weight(w) {}
};

// Comparison function for priority queue (min-heap)
struct Compare {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second; // Min-heap based on distance
    }
};

class Graph {
private:
    int vertices;
    vector<vector<Edge>> adjList;

public:
    Graph(int v) : vertices(v) {
        adjList.resize(v);
    }
    
    // Add a weighted edge to the graph
    void addEdge(int src, int dest, int weight) {
        adjList[src].push_back(Edge(dest, weight));
        // For undirected graph, uncomment the next line:
        // adjList[dest].push_back(Edge(src, weight));
    }
    
    // Dijkstra's algorithm implementation
    vector<int> dijkstra(int source) {
        // Initialize distances with infinity
        vector<int> dist(vertices, INT_MAX);
        vector<int> parent(vertices, -1);
        vector<bool> visited(vertices, false);
        
        // Priority queue to store (vertex, distance) pairs
        priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq;
        
        // Distance to source is 0
        dist[source] = 0;
        pq.push({source, 0});
        
        while (!pq.empty()) {
            int u = pq.top().first;
            pq.pop();
            
            // Skip if already visited
            if (visited[u]) continue;
            visited[u] = true;
            
            // Check all adjacent vertices
            for (const Edge& edge : adjList[u]) {
                int v = edge.destination;
                int weight = edge.weight;
                
                // Relaxation step
                if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({v, dist[v]});
                }
            }
        }
        
        return dist;
    }
    
    // Function to print the shortest path from source to destination
    void printPath(int source, int dest, const vector<int>& parent) {
        if (dest == source) {
            cout << source;
            return;
        }
        if (parent[dest] == -1) {
            cout << "No path exists";
            return;
        }
        
        printPath(source, parent[dest], parent);
        cout << " -> " << dest;
    }
    
    // Function to print all shortest distances and paths from source
    void printSolution(int source, const vector<int>& dist) {
        cout << "\nShortest distances from vertex " << source << ":\n";
        cout << setw(10) << "Vertex" << setw(15) << "Distance" << "\n";
        cout << string(25, '-') << "\n";
        
        for (int i = 0; i < vertices; i++) {
            cout << setw(10) << i << setw(15);
            if (dist[i] == INT_MAX) {
                cout << "INF\n";
            } else {
                cout << dist[i] << "\n";
            }
        }
    }
};

int main() {
    // Example usage
    cout << "Dijkstra's Algorithm Example\n";
    cout << "============================\n";
    
    // Create a graph with 6 vertices
    Graph g(6);
    
    // Add edges (source, destination, weight)
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 6);
    g.addEdge(1, 4, 3);
    
    int source = 0;
    vector<int> distances = g.dijkstra(source);
    
    // Print the results
    g.printSolution(source, distances);
    
    // Example of finding shortest path between two specific vertices
    cout << "\nExample paths from vertex " << source << ":\n";
    for (int i = 1; i < 6; i++) {
        cout << "To vertex " << i << " (distance " << distances[i] << "): ";
        // Note: For path reconstruction, you'd need to modify dijkstra to return parent array
        cout << "Path reconstruction would require parent tracking\n";
    }
    
    return 0;
}