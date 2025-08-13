#include <iostream>
#include <vector>
using namespace std;

// Function to perform DFS
void dfs(int v, const vector<vector<int>>& adj, vector<bool>& visited) {
    visited[v] = true;
    for (int u = 0; u < adj.size(); ++u) {
        if (adj[v][u] && !visited[u])
            dfs(u, adj, visited);
    }
}

// Function to check if the graph is connected (ignoring isolated vertices)
bool isConnected(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    int start = -1;
    // Find a vertex with non-zero degree
    for (int i = 0; i < n; ++i) {
        int deg = 0;
        for (int j = 0; j < n; ++j) deg += adj[i][j];
        if (deg) {
            start = i;
            break;
        }
    }
    if (start == -1) return true; // No edges
    dfs(start, adj, visited);
    // Check if all non-isolated vertices are visited
    for (int i = 0; i < n; ++i) {
        int deg = 0;
        for (int j = 0; j < n; ++j) deg += adj[i][j];
        if (deg && !visited[i]) return false;
    }
    return true;
}

int main() {
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;
    vector<vector<int>> adj(n, vector<int>(n));
    cout << "Enter adjacency matrix:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> adj[i][j];

    // Calculate degree of each vertex
    vector<int> degree(n, 0);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            degree[i] += adj[i][j];

    cout << "Degree of each vertex:\n";
    for (int i = 0; i < n; ++i)
        cout << "Vertex " << i << ": " << degree[i] << endl;

    // Check for Eulerian circuit (all degrees even and graph is connected)
    bool allEven = true;
    for (int d : degree)
        if (d % 2 != 0)
            allEven = false;

    if (allEven && isConnected(adj))
        cout << "The problem is solvable: An Eulerian circuit exists.\n";
    else
        cout << "The problem is NOT solvable: No Eulerian circuit exists.\n";

    return 0;
}