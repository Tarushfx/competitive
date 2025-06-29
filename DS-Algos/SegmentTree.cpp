#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define sz(x) ((int)x.size())
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
    int left_child(int node) { return 2 * node + 1; }
    int right_child(int node) { return 2 * node + 2; }
    int build_tree(int node, int start, int end)
    {
        if (start == end)
        {
            return tree[node] = arr[start];
        }
        int mid = get_mid(start, end);
        return tree[node] = build_tree(left_child(node), start, mid) +
                            build_tree(right_child(node), mid + 1, end);
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
        update_helper(left_child(node), start, mid, index, diff);
        update_helper(right_child(node), mid + 1, end, index, diff);
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
        return query_helper(left_child(node), start, mid, left, right) +
               query_helper(right_child(node), mid + 1, end, left, right);
    }
};

class LazySegmentTree
{
    int size, arr_size;
    vi tree, lazy, arr;

public:
    LazySegmentTree(vi &arr)
    {
        this->arr = arr;
        this->arr_size = sz(arr);
        this->size = 4 * arr_size;
        this->tree = vi(size, 0);
        this->lazy = vi(size, 0);
        build_tree(0, 0, arr_size - 1);
    }
    int left_child(int node) { return 2 * node + 1; }
    int right_child(int node) { return 2 * node + 2; }
    int build_tree(int node, int start, int end)
    {
        if (start == end)
        {
            return tree[node] = arr[start];
        }
        int mid = get_mid(start, end);
        return tree[node] = build_tree(left_child(node), start, mid) +
                            build_tree(right_child(node), mid + 1, end);
    }
    void update_diff(int index, int diff)
    {
        update_helper(0, 0, arr_size - 1, index, index, diff);
    }
    void update_range(int left, int right, int value)
    {
        update_helper(0, 0, arr_size - 1, left, right, value);
    }
    void update_helper(int node, int start, int end, int left, int right, int diff)
    {
        // lazy
        if (lazy[node] != 0)
        {
            tree[node] += lazy[node] * (end - start + 1);
            if (start != end)
            {
                lazy[left_child(node)] += lazy[node];
                lazy[right_child(node)] += lazy[node];
            }
            lazy[node] = 0;
        }
        if (start > right || end < left || start > end)
            return;
        if (start >= left && end <= right)
        {
            tree[node] += diff * (end - start + 1);
            if (start != end)
            {
                lazy[left_child(node)] += diff;
                lazy[right_child(node)] += diff;
            }

            // lazy[node] = 0;
            return;
        }
        int mid = get_mid(start, end);
        update_helper(left_child(node), start, mid, left, right, diff);
        update_helper(right_child(node), mid + 1, end, left, right, diff);
        tree[node] = tree[left_child(node)] + tree[right_child(node)];
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
        if (lazy[node] != 0)
        {
            tree[node] += lazy[node] * (end - start + 1);
            if (start != end)
            {
                lazy[left_child(node)] += lazy[node];
                lazy[right_child(node)] += lazy[node];
            }
            lazy[node] = 0;
        }
        if (start > right || end < left || start > end)
            return;
        if (start >= left && end <= right)
            return tree[node];
        if (start > right || end < left)
            return 0;
        int mid = get_mid(start, end);
        return query_helper(left_child(node), start, mid, left, right) +
               query_helper(right_child(node), mid + 1, end, left, right);
    }
    void clear()
    {
        for (int i = 0; i < arr_size; i++)
        {
            query(i, i);
        }
    }
};
int main()
{
    vector<int> arr({2, 12, 3, 4});
    LazySegmentTree lst = LazySegmentTree(arr);
    cout << lst.query(0, 3) << endl;
    lst.update_range(1, 2, 5);
    cout << lst.query(0, 3) << endl;
    cout << lst.query(0, 2) << endl;
    lst.update_range(2, 3, 4);
    cout << lst.query(0, 3) << endl;
    return 0;
}