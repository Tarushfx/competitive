#include <bits/stdc++.h>
using namespace std;

#define ll long long int
#define pii pair<int, int>
#define vi vector<int>
#define vb vector<bool>
#define vvi vector<vi>
#define vpi vector<pii>
#define vvpi vector<vpi>
#define mii map<int, int>
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
void __f(const char *name, Arg1 &&arg1)
{
    cout << name << " : " << arg1 << endl;
}
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
class SegmentTree
{
    int size, arr_size;
    vi tree, arr;

public:
    SegmentTree(vi &arr)
    {
        this->arr = arr;
        this->arr_size = sz(arr);
        this->size = 4 * arr_size;
        this->tree = vi(size, 0);
        build_tree(0, 0, arr_size - 1);
    }
    int left_subtree(int node) { return 2 * node + 1; }
    int right_subtree(int node) { return 2 * node + 2; }
    int build_tree(int node, int start, int end)
    {
        if (start == end)
        {
            return tree[node] = arr[start];
        }
        int mid = get_mid(start, end);
        return tree[node] = build_tree(left_subtree(node), start, mid) +
                            build_tree(right_subtree(node), mid + 1, end);
    }
    void update_value(int index, int value)
    {
        int diff = value - arr[index];
        arr[index] = value;
        update_helper(0, 0, arr_size - 1, index, diff);
    }
    void update_diff(int index, int diff)
    {
        update_helper(0, 0, arr_size - 1, index, diff);
    }
    void update_helper(int node, int start, int end, int index, int diff)
    {
        if (start > index || end < index)
            return;
        tree[node] += diff;

        if (start == end)
        {
            return;
        }
        int mid = get_mid(start, end);
        update_helper(left_subtree(node), start, mid, index, diff);
        update_helper(right_subtree(node), mid + 1, end, index, diff);
    }
    int get_mid(int start, int end)
    {
        return start + (end - start) / 2;
    }
    int query(int left, int right)
    {
        return query_helper(0, 0, arr_size - 1, left, right);
    }
    int query_helper(int node, int start, int end, int left, int right)
    {
        if (start >= left && end <= right)
            return tree[node];
        if (start > right || end < left)
            return 0;
        int mid = get_mid(start, end);
        return query_helper(left_subtree(node), start, mid, left, right) +
               query_helper(right_subtree(node), mid + 1, end, left, right);
    }
};
class BITTree
{
    int size, arr_size;
    vi tree, arr;

public:
    BITTree(vi &arr)
    {
        this->arr = arr;
        this->arr_size = sz(arr);
        this->size = arr_size;
        this->tree = vi(size + 1, 0);
        build_tree();
    }

    void build_tree()
    {
        for (int i = 1; i <= size; i++)
        {
            int x = i;
            while (x <= size)
            {
                tree[x] += arr[i - 1];
                x += (x & -x);
            }
        }
    }
    void update_value(int index, int value)
    {
        int diff = value - arr[index];
        arr[index] = value;
        update_helper(index, diff);
    }
    void update_diff(int index, int diff)
    {
        update_helper(index, diff);
    }
    void update_helper(int index, int diff)
    {
        index++;
        while (index <= size)
        {
            tree[index] += diff;
            index += (index & -index);
        }
    }
    int query(int left, int right)
    {
        return query_helper(right) - query_helper(left - 1);
    }
    int query_helper(int index)
    {
        int res = 0;
        index++;
        while (index > 0)
        {
            res += tree[index];
            index -= (index & -index);
        }
        return res;
    }
};
class TrieNode
{
public:
    char data;
    bool isEnd = false;
    vector<TrieNode *> children;
    // map<char, TrieNode *> children;
    TrieNode(char data = '\0')
    {
        this->data = data;
        this->children = vector<TrieNode *>(26, NULL);
    }
};
class Trie
{
public:
    TrieNode *root;
    Trie()
    {
        this->root = new TrieNode('\0');
    }
    bool has_child(TrieNode *curr, int w)
    {
        // return curr->children.find(w)!=curr->children.end();
        cout << (curr != NULL);
        return curr->children[w] != NULL;
    }
    void insert(string word)
    {
        TrieNode *curr = root;
        for (auto w : word)
        {
            w -= 'a';
            if (!has_child(curr, w))
            {
                curr->children[w] = new TrieNode(w);
            }
            curr = curr->children[w];
        }
        curr->isEnd = true;
    }
    bool search(string word)
    {
        TrieNode *curr = root;
        for (auto w : word)
        {
            w -= 'a';
            if (!has_child(curr, w))
                return false;
            curr = curr->children[w];
        }
        return curr->isEnd;
    }
};
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
    void unionbyrank(int a, int b)
    {
        int pa = find(a);
        int pb = find(b);
        if (pa == pb)
            return;
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
    }
};

void solve() {}
int32_t main()
{
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
