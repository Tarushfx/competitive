#include <bits/stdc++.h>
using namespace std;
class DSU
{
public:
    vector<int> parent;
    vector<int> rank;
    DSU(int n)
    {
        parent = vector<int>(n, -1);
        rank = vector<int>(n, 1);
    }
    int find(int a)
    {
        if (parent[a] == -1)
            return a;
        return parent[a] = find(parent[a]);
    }
    bool unionbyrank(int a, int b)
    {
        int pa = find(a);
        int pb = find(b);
        if (pa == pb)
            return true;
        if (rank[pa] > rank[pb])
        {
            parent[pb] = pa;
            rank[pa] += rank[pb];
        }
        else
        {
            parent[pa] = pb;
            rank[pb] += rank[pa];
        }
        return true;
    }
};
