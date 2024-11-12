#include <bits/stdc++.h>
using namespace std;

void bfs(int s, vector<vector<int>> &adj, int n)
{
    vector<bool> visited(n, false); // To keep track of visited nodes
    queue<int> q;                   // Queue for BFS

    q.push(s); // Start from source node `s`
    visited[s] = true;

    while (!q.empty())
    {
        int v = q.front(); // Current node
        q.pop();

        cout << v + 1 << " "; // Output the current node (1-based index)

        // Explore all neighbors of the current node
        for (int neighbor : adj[v])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                q.push(neighbor); // Add neighbor to queue
            }
        }
    }
    cout << endl;
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

    bfs(s, adj, n); // Perform BFS starting from node `s`

    return 0;
}

/*
Input
6 7 1
1 2
1 3
2 4
3 4
3 5
4 6
5 6



Output
1 2 3 4 5 6


*/