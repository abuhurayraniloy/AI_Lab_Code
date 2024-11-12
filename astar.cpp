/*bismillahir~rahmanir~rahim*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

map<string, vector<pair<string, int>>> g; // city1 city2 distance
map<string, int> h;                       // heuristic
map<string, bool> v;                      // visited
map<string, int> d;                       // distance
map<string, string> parentNode;
vector<string> path;
priority_queue<pair<ll, string>, vector<pair<ll, string>>, greater<pair<ll, string>>> pq;

void aStarSearch(string source, string destinaton)
{

    pq.push({h[source], source});
    d[source] = 0;
    parentNode[source] = source;

    while (!pq.empty())
    {
        auto x = pq.top();
        pq.pop();

        if (v[x.second])
            continue; // if visited skip
        if (x.second == destinaton)
        {

            // cout<<"code ends"<<endl;
            break;
        } // if reached break
        v[x.second] = true;
        for (auto u : g[x.second])
        {

            ll ff, hh, gg, dd;

            dd = x.first; // parents distance from source

            string ss = u.first; // child city
            gg = u.second;       // distance from parent to child
            hh = h[ss];          // heuristic distance of child
            // cout<<x.second<<" "<<ss<<" ";

            ff = dd - (h[x.second]) + gg + hh; // f(n)  = distance from parent + g(n) + h(n)

            if (dd - (h[x.second]) + gg < d[ss])
            {
                d[ss] = dd - (h[x.second]) + gg;
                parentNode[ss] = x.second;
                // cout<<"d : "<<ss<<" "<<d[ss]<<endl;
            }
            // printf("dd=%lld, h[%s]=%d, gg=%lld, hh=%lld ff=%lld d[%s]=%lld\n",dd,x.second.c_str(),h[x.second],gg,hh,ff,ss.c_str(),d[ss]);
            pq.push({ff, ss});
        }
    }
}

int main()
{

    int n, m, x;
    cin >> n >> m;
    string s1, s2;
    while (m--)
    {
        cin >> s1 >> s2 >> x;
        g[s1].push_back({s2, x});
        // cout<<"edges done"<<endl;
    }
    getchar();
    getchar();

    while (n--)
    {
        cin >> s1 >> x;
        h[s1] = x;
        v[s1] = false;
        d[s1] = INT_MAX;
        parentNode[s1] = "blank";
    }
    getchar();
    getchar();

    cin >> s1 >> s2;

    aStarSearch(s1, s2);
    // cout<<"search done"<<endl;
    // cout<<parentNode[s2]<<endl;
    cout << endl;
    if (parentNode[s2] != "blank" && !parentNode[s2].empty())
    {
        string cast = s2;
        stack<string> sss;
        sss.push(s2);

        while (parentNode[s2] != s2)
        {
            sss.push(parentNode[s2]);
            s2 = parentNode[s2];
        }

        while (!sss.empty())
        {
            cout << sss.top();
            sss.pop();
            if (!sss.empty())
                cout << "->";
            else
            {
                cout << endl;
                cout << "Path cost: " << d[cast] << endl;
            }
        }
    }
    else
    {
        cout << "No path found" << endl;
    }
}
/*
input :
=======
7 9
S C 3
S B 4
C D 7
C E 10
B E 12
B F 5
D E 2
E G 5
F G 16

S 14
C 11
B 12
D 6
E 4
F 11
G 0

S G

output:
S->C->D->E->G
Path cost: 17

*/