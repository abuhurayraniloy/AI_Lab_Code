#include <iostream>
#include <vector>
#include <iterator>
#include <map>
#include <string>
#include <bits/stdc++.h>
#include <functional>
#include <utility>
#include <queue>
#include <fstream>
using namespace std;

struct Node
{
    vector<vector<int>> state;
    int x, y; // Position of the blank tile
    int g;    // Cost from the start node to this node
    int h;    // Heuristic cost (Manhattan distance)
};

// Direction vectors and corresponding moves
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
string moveLabels[] = {"Up", "Down", "Left", "Right"};

vector<string> solutionPath; // Stores the solution path

// Heuristic function: Manhattan distance
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

// Check if a given state is the goal
bool isGoal(const vector<vector<int>> &state, const vector<vector<int>> &goal)
{
    return state == goal;
}

// IDA* recursive function
bool IDAStar(Node node, const vector<vector<int>> &goal, int threshold, int &newThreshold)
{
    int f = node.g + node.h; // f(n) = g(n) + h(n)
    if (f > threshold)
    {
        newThreshold = min(newThreshold, f);
        return false;
    }

    if (isGoal(node.state, goal))
        return true;

    for (int i = 0; i < 4; i++)
    {
        int newX = node.x + dx[i];
        int newY = node.y + dy[i];
        if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3)
        {
            // Create a new state by moving the blank tile
            vector<vector<int>> newState = node.state;
            swap(newState[node.x][node.y], newState[newX][newY]);

            // Avoid repeating moves
            if (solutionPath.empty() || moveLabels[i] != solutionPath.back())
            {
                Node child{newState, newX, newY, node.g + 1, manhattanDistance(newState, goal)};
                solutionPath.push_back(moveLabels[i]);

                // Recursive search
                if (IDAStar(child, goal, threshold, newThreshold))
                    return true;
                solutionPath.pop_back(); // Backtrack
            }
        }
    }
    return false;
}

// IDA* main function
void solve8Puzzle(const vector<vector<int>> &start, const vector<vector<int>> &goal)
{
    int threshold = manhattanDistance(start, goal); // Initial threshold
    Node startNode{start, 0, 0, 0, threshold};

    // Locate blank tile (0)
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

    // Iterative deepening
    while (true)
    {
        int newThreshold = INT_MAX;
        if (IDAStar(startNode, goal, threshold, newThreshold))
        {
            cout << "Solution Path:\n";
            for (const auto &step : solutionPath)
                cout << step << " ";
            cout << "\nTotal moves: " << solutionPath.size() << endl;
            return;
        }
        if (newThreshold == INT_MAX)
        {
            cout << "No solution found." << endl;
            return;
        }
        threshold = newThreshold;
    }
}

int main()
{
    // Input: Initial and goal states as 3x3 matrices
    vector<vector<int>> start(3, vector<int>(3));
    vector<vector<int>> goal(3, vector<int>(3));

    cout << "Enter initial state (3x3):" << endl;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> start[i][j];

    cout << "Enter goal state (3x3):" << endl;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> goal[i][j];

    solve8Puzzle(start, goal);

    return 0;
}

/*
Input Format:
Enter initial state (3x3):
1 2 3
4 0 5
6 7 8

Enter goal state (3x3):
1 2 3
4 5 0
6 7 8

 */