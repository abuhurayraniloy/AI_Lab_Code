#include <bits/stdc++.h>

using namespace std;

// Graph
map<char, vector<char>> G;

// dis of edges
map<pair<char, char>, int> dis;

// returns the minimum dis in a vector
map<char, int> UCS(vector<char> goal, char source)
{
    // minimum dis upto goal from source
    map<char, int> ans;

    // priority queue
    priority_queue<pair<int, char>> queue;

    // set the ans vector to max value
    for (char i : goal)
        ans[i] = INT_MAX;

    // insert the source index
    queue.push(make_pair(0, source));

    // map to store visited node
    map<char, int> visited;

    // count
    int count = 0;

    // while the queue is not empty
    while (queue.size() > 0)
    {
        // get the top element of the
        // priority queue
        pair<int, char> p = queue.top();

        // pop the element
        queue.pop();

        // get the original value
        p.first *= -1;

        // check if the element is part of
        // the goal list
        if (find(goal.begin(), goal.end(), p.second) != goal.end())
        {

            // if a new goal is reached
            if (ans[p.second] == INT_MAX)
            {
                count++;
            }

            // if the dis is less
            if (ans[p.second] > p.first)
            {
                ans[p.second] = p.first;
            }

            // pop the element
            queue.pop();

            // if all goals are reached
            if (count == goal.size())
            {
                return ans;
            }
        }

        // check for the non visited nodes
        // which are adjacent to present node
        if (visited[p.second] == 0)
        {
            for (char i : G[p.second])
            {
                // value is multiplied by -1 so that
                // least priority is at the top
                queue.push(make_pair((p.first + dis[make_pair(p.second, i)]) * -1, i));
            }
        }
        // mark as visited
        visited[p.second] = 1;
    }
    return ans;
}
int main()
{
    // edges
    G['S'].push_back('A');
    G['S'].push_back('G');
    G['A'].push_back('B');
    G['A'].push_back('C');
    G['B'].push_back('D');
    G['C'].push_back('D');
    G['C'].push_back('G');
    G['D'].push_back('G');
    G['D'].push_back('G');

    // add the dis of edges
    dis[make_pair('S', 'A')] = 1;
    dis[make_pair('S', 'G')] = 12;
    dis[make_pair('A', 'B')] = 3;
    dis[make_pair('A', 'C')] = 1;
    dis[make_pair('B', 'D')] = 3;
    dis[make_pair('C', 'D')] = 1;
    dis[make_pair('C', 'G')] = 2;
    dis[make_pair('D', 'G')] = 3;
    dis[make_pair('D', 'G')] = 3;

    // goal state
    vector<char> goal;

    // set the goal
    // there can be multiple goal states
    goal.push_back('G');

    // get the ans
    map<char, int> ans = UCS(goal, 'S');

    // print the ans
    cout << "Minimum dis from Source to Goal is = " << ans['G'] << endl;

    return 0;
}