#include <bits/stdc++.h>
using namespace std;

// Node structure to represent each state in the puzzle
struct Node
{
    vector<vector<int>> state; // The 8-puzzle grid
    int x, y;                  // Position of the blank tile
    int g, h;                  // g: cost from start, h: heuristic cost (Manhattan distance)
    string path;               // Path of moves taken to reach this state

    // Comparator for priority queue based on f = g + h
    bool operator<(const Node &other) const
    {
        return (g + h) > (other.g + other.h);
    }
};

// Direction vectors for moving the blank tile (up, down, left, right)
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
string moveLabels[] = {"Up", "Down", "Left", "Right"};

// Manhattan distance heuristic function
int manhattanDistance(const vector<vector<int>> &state, const vector<vector<int>> &goal)
{
    int dist = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (state[i][j] != 0)
            {
                for (int x = 0; x < 3; x++)
                {
                    for (int y = 0; y < 3; y++)
                    {
                        if (state[i][j] == goal[x][y])
                        {
                            dist += abs(i - x) + abs(j - y);
                        }
                    }
                }
            }
        }
    }
    return dist;
}

// Function to check if a given state matches the goal state
bool isGoal(const vector<vector<int>> &state, const vector<vector<int>> &goal)
{
    return state == goal;
}

// A* algorithm for solving the 8-puzzle
void aStar(const vector<vector<int>> &start, const vector<vector<int>> &goal)
{
    priority_queue<Node> pq;
    int startH = manhattanDistance(start, goal);
    Node startNode{start, 0, 0, 0, startH, ""};

    // Find the initial position of the blank tile (0)
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (start[i][j] == 0)
            {
                startNode.x = i;
                startNode.y = j;
            }
        }
    }

    pq.push(startNode);
    set<vector<vector<int>>> visited; // To keep track of visited states
    visited.insert(start);

    while (!pq.empty())
    {
        Node current = pq.top();
        pq.pop();

        // If the current state matches the goal state, output the solution path
        if (isGoal(current.state, goal))
        {
            cout << "Solution Path: " << current.path << endl;
            cout << "Total Moves: " << count(current.path.begin(), current.path.end(), ' ') << endl;

            return;
        }

        // Explore each possible move
        for (int i = 0; i < 4; i++)
        {
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];

            // Check if the new position is within the grid boundaries
            if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3)
            {
                vector<vector<int>> newState = current.state;
                swap(newState[current.x][current.y], newState[newX][newY]);

                // Process new state if it hasn't been visited
                if (visited.find(newState) == visited.end())
                {
                    int newG = current.g + 1;
                    int newH = manhattanDistance(newState, goal);
                    string newPath = current.path + moveLabels[i] + " ";

                    pq.push({newState, newX, newY, newG, newH, newPath});
                    visited.insert(newState);
                }
            }
        }
    }

    cout << "No solution found." << endl;
}

int main()
{
    vector<vector<int>> start(3, vector<int>(3));
    vector<vector<int>> goal(3, vector<int>(3));

    cout << "Enter the initial state (3x3 grid, use 0 for the blank tile):" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> start[i][j];
        }
    }

    cout << "Enter the goal state (3x3 grid, use 0 for the blank tile):" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> goal[i][j];
        }
    }

    aStar(start, goal);

    return 0;
}
