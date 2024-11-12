#include <iostream>
#include <vector>
#include <stack>

using namespace std;
#define ll long long int
#define yes printf("YES\n")
#define no printf("NO\n")

// Function to perform depth-limited search
bool DLS(vector<vector<int>> &graph, ll start, ll goal, ll limit)
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
    for (auto i : graph[start])
    {
        if (DLS(graph, i, goal, limit - 1))
        {
            return true;
        }
    }
    return false;
}

// Function to perform Iterative-Deepening Search
bool IDS(int start, int target, vector<vector<int>> &graph)
{

    // storing max depth size. in worst case which canbe the number of nodes
    int maxDepth = graph.size();

    // finding the target for every depth
    for (int depth = 0; depth <= maxDepth; depth++)
    {
        if (DLS(graph, start, target, depth))
        {
            return true;
        }
    }

    // failed case
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
    ll goal, start;
    cin >> start >> goal;

    if (IDS(start, goal, graph))
        cout << "Yes, it is possible to reach the goal \n";
    else
        cout << "No, it isn't possible to reach the goal \n";

    return 0;
}

/*

input:

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

output: Yes, it is possible to reach the goal
*/
