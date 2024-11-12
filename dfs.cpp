#include <bits/stdc++.h>
using namespace std;

void dfs(int v, vector<vector<int>> &adj, vector<bool> &visited)
{
    // Mark the current node as visited
    visited[v] = true;
    cout << v + 1 << " "; // Output the current node (1-based index)

    // Explore all unvisited neighbors
    for (int neighbor : adj[v])
    {
        if (!visited[neighbor])
        {
            dfs(neighbor, adj, visited); // Recursive DFS call for unvisited neighbors
        }
    }
}

int main()
{
    int n, m, s;
    cin >> n >> m >> s;
    s--; // Convert to 0-based index

    vector<vector<int>> adj(n); // Adjacency list
    for (int i = 0; i < m; i++)
    {
        int v1, v2;
        cin >> v1 >> v2;
        v1--;
        v2--; // Convert to 0-based index
        adj[v1].push_back(v2);
        adj[v2].push_back(v1); // Assuming undirected graph
    }

    vector<bool> visited(n, false); // To keep track of visited nodes
    dfs(s, adj, visited);           // Perform DFS starting from node `s`

    cout << endl;
    return 0;
}

/*
input:
6 7 1
1 2
1 3
2 4
3 4
3 5
4 6
5 6



output:
1 2 4 3 5 6



*/