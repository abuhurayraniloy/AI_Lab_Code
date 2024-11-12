/*bismillahir~rahmanir~rahim*/
#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;

#define ll long long int
#define yes printf("YES\n")
#define no printf("NO\n")

bool DLS(vector<vector<int>> &g, ll start, ll goal, ll limit)
{

    // if we reached the goal
    if (start == goal)
    {
        return true;
    }

    // if we crossed limit
    if (limit == 0)
    {
        return false;
    }

    // traversing child nodes
    for (auto i : g[start])
    {
        if (DLS(g, i, goal, limit - 1))
        {
            return true;
        }
    }
    return false;
}

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    // taking input the numbers of nodes and edges
    cout << "Enter the number of nodes and edges:\n";
    ll n, m;
    cin >> n >> m;

    // adjacency list
    vector<vector<int>> graph(n + 1);

    // taking input the edges
    cout << "Enter the edges:\n";
    for (int i = 0; i < m; i++)
    {
        ll u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[u].push_back(v);
    }

    // taking input the start and goal node
    cout << "Enter the start and goal node and limit:\n";
    ll goal, limit, start;
    cin >> start >> goal >> limit;

    if (DLS(graph, start, goal, limit))
        cout << "Yes, it is possible to reach the goal \n";
    else
        cout << "No, it isn't possible to reach the goal \n";
}

/*

input 1 :

9 8
1 2
1 3
2 4
2 5
5 8
3 6
6 7
7 9
1 3 2

output 1 : Yes, it is possible to reach the goal

input 2 :

9 8
1 2
1 3
2 4
2 5
5 8
3 6
6 7
7 9
1 9 2

output 1 : No, it isn't possible to reach the goal

*/