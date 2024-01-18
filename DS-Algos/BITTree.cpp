#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define sz(x) ((int)x.size())
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
    int parent(int index)
    {
        return index + (index & -index);
    }
    void build_tree()
    {
        for (int i = 1; i <= size; i++)
        {
            int index = i;
            while (index <= size)
            {
                tree[index] += arr[i - 1];
                index = parent(index);
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
            index = parent(index);
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