#include <bits/stdc++.h>
using namespace std;

void bfs(int s, vector<vector<int>> &adj, int n, int u)
{
    vector<bool> used(n, false); // To keep track of visited nodes
    vector<int> d(n, -1);        // Distance from source to each node
    vector<int> p(n, -1);        // Parent array to reconstruct the path

    queue<int> q;
    q.push(s);
    used[s] = true;
    d[s] = 0; // Distance to the source is 0

    // BFS traversal
    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        for (int neighbor : adj[v])
        {
            if (!used[neighbor])
            {
                used[neighbor] = true;
                q.push(neighbor);
                d[neighbor] = d[v] + 1; // Distance update
                p[neighbor] = v;        // Set parent of neighbor
            }
        }
    }

    // Check if there is a path to u
    if (!used[u])
    {
        cout << "No path from " << s + 1 << " to " << u + 1 << "!" << endl;
    }
    else
    {
        // Reconstruct the path from u to s using parent array
        vector<int> path;
        for (int v = u; v != -1; v = p[v])
        {
            path.push_back(v);
        }
        reverse(path.begin(), path.end()); // Path is reconstructed backwards

        // Print the path
        cout << "Shortest path from " << s + 1 << " to " << u + 1 << ": ";
        for (int v : path)
        {
            cout << v + 1 << " "; // Convert back to 1-based indexing for output
        }
        cout << endl;

        // Print the distance
        cout << "Shortest path length: " << d[u] << endl;
    }
}

int main()
{
    int n, m, s, u;
    cin >> n >> m >> s >> u;
    s--; // Convert to 0-based index for internal usage
    u--; // Convert to 0-based index for internal usage

    vector<vector<int>> adj(n);

    for (int i = 0; i < m; i++)
    {
        int v1, v2;
        cin >> v1 >> v2;
        v1--; // Convert to 0-based index for internal usage
        v2--; // Convert to 0-based index for internal usage
        adj[v1].push_back(v2);
        adj[v2].push_back(v1); // Assuming undirected graph
    }

    // Perform BFS and print the shortest path from s to u
    bfs(s, adj, n, u);

    return 0;
}

/*
input
6 7 1 6
1 2
1 3
2 4
3 4
3 5
4 6
5 6


output
Shortest path from 1 to 6: 1 3 5 6
Shortest path length: 3


*/