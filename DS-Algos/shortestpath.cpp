#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pii pair<int, int>
#define tii tuple<int, int, int>
#define vi vector<int>
#define vb vector<bool>
#define vvi vector<vi>
#define vpi vector<pii>
#define vti vector<tii>
#define vvpi vector<vpi>
#define mii map<int, int>
#define mvpi map<int, vpi>
#define si set<int>
#define sc set<char>
#define spi set<pii>
#define endl "\n"
#define sz(x) ((int)x.size())
#define all(x) x.begin(), x.end()
#define maxheap priority_queue<int>
#define minheap priority_queue<int, vi, greater<int>>
#define f(i, s, e) for (int i = s; i < e; i++)
#define fe(i, s, e) for (int i = s; i <= e; i++)
#define rf(i, s, e) for (int i = e - 1; i >= s; i--)
#define pb push_back
#define eb emplace_back
#define F first
#define S second

#define print(a)          \
    for (auto x : a)      \
        cout << x << ","; \
    cout << endl
#define printpair(a) \
    for (auto x : a) \
    cout << x.F << "-" << x.S << endl
#define bug(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char *name, Arg1 &&arg1) { cout << name << " : " << arg1 << endl; }
template <typename Arg1, typename... Args>
void __f(const char *names, Arg1 &&arg1, Args &&...args)
{
    const char *comma = strchr(names + 1, ',');
    cout.write(names, comma - names) << " : " << arg1 << " | ";
    __f(comma + 1, args...);
}
inline int power(int a, int b, int mod)
{
    int x = 1;
    while (b)
    {
        if (b & 1)
            x = (x * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return a;
}

#define MOD 1000000007
#define PI 3.1415926535897932384626433832795
int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}
int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int lcm(int a, int b) { return a / gcd(a, b) * b; }

string to_upper(string a)
{
    for (int i = 0; i < sz(a); ++i)
        if (a[i] >= 'a' && a[i] <= 'z')
            a[i] -= 'a' - 'A';
    return a;
}
string to_lower(string a)
{
    for (int i = 0; i < sz(a); ++i)
        if (a[i] >= 'A' && a[i] <= 'Z')
            a[i] += 'a' - 'A';
    return a;
}
bool prime(int a)
{
    if (a == 1)
        return 0;
    for (int i = 2; i <= round(sqrt(a)); ++i)
        if (a % i == 0)
            return 0;
    return 1;
}
void yes() { cout << "YES\n"; }
void no() { cout << "NO\n"; }
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
            return false;
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

vpi primsMST(int n, vti &edges);
vpi kruskalsMST(int n, vti &edges);
void solve()
{
    vti edges = vti({{0, 1, 3}, {2, 1, 4}, {0, 2, 2}, {1, 3, 5}});
    auto ans = primsMST(4, edges);
    for (auto [u, v] : ans)
    {
        cout << u << " " << v << endl;
    }
    ans = kruskalsMST(4, edges);
    for (auto [u, v] : ans)
    {
        cout << u << " " << v << endl;
    }
}

int32_t main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    int t = 1;
    // cin >> t;
    while (t--)
        solve();
    return 0;
}
vvpi edge_to_graph(int n, vti &edges)
{
    vvpi graph = vvpi(n, vpi());
    for (const auto &[u, v, w] : edges)
    {
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    return graph;
}
class Compare
{
public:
    bool operator()(tii a, tii b)
    {
        return get<0>(a) >= get<0>(b);
    }
};
void sort_tuple(vti &x)
{
    sort(all(x), [](tii &a, tii &b)
         { return get<2>(a) < get<2>(b); });
}
void sort_v(vpi &x)
{
    // < for low to high
    sort(all(x), [](pii &a, pii &b)
         { return a.F < b.F; });
}
vpi primsMST(int n, vti &edges)
{
    // Create graph representation
    vvpi graph = vvpi(n, vpi());
    for (auto &[u, v, w] : edges)
    {
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    // Prim's algorithm
    priority_queue<tii, vti, greater<tii>> pq;
    set<int> visited;
    vpi mst;

    pq.push({0, 0, -1}); // Start with arbitrary node 0

    while (!pq.empty())
    {
        auto [w, node, par] = pq.top();
        pq.pop();
        if (visited.find(node) != visited.end())
            continue;
        visited.insert(node);
        if (par != -1)
        {
            mst.push_back({node, par});
        }
        if (sz(visited) == n)
        {
            return mst;
        }
        for (auto [nei, w] : graph[node])
        {
            if (visited.find(nei) == visited.end())
            {
                pq.push({w, nei, node});
            }
        }
    }
    return mst;
}
vpi kruskalsMST(int n, vti &edges)
{
    // Sort edges by weight
    sort_tuple(edges);

    DSU dsu = DSU(n);
    vpi mst;

    for (const auto &[u, v, w] : edges)
    {

        if (dsu.unionbyrank(u, v))
        {
            mst.push_back({u, v});
        }
    }

    return mst;
}