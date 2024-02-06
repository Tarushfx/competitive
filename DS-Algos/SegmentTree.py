class SegmentTree:
    def __init__(self, arr):
        self.arr_size = len(arr)
        self.size = 4 * self.arr_size
        self.arr = arr
        self.tree = [0] * 4 * self.arr_size
        self.buildtree(0, 0, self.arr_size - 1)
        self.node = self.start = 0
        self.end = self.arr_size - 1

    def update_value(self, index, value):
        diff = value - self.arr[index]
        self.arr[index] = value
        self.update_tree_helper(self.node, self.start, self.end, index, diff)

    def update_diff(self, index, diff):
        self.update_tree_helper(self.node, self.start, self.end, index, diff)

    def query(self, left, right):
        return self.query_helper(self.node, self.start, self.end, left, right)

    def left_child(self, node):
        return 2 * node + 1

    def right_child(self, node):
        return 2 * node + 2

    def buildtree(self, node, start, end):
        if start == end:
            self.tree[node] = self.arr[start]
            return self.tree[node]
        mid = (start + end) // 2
        self.tree[node] = self.buildtree(
            self.left_child(node), start, mid
        ) + self.buildtree(self.right_child(node), mid + 1, end)
        return self.tree[node]

    def update_tree_helper(self, node, start, end, idx, diff):
        if idx < start or idx > end:
            return
        self.tree[node] += diff
        if start == end:
            return
        mid = (start + end) // 2
        self.update_tree_helper(self.left_child(node), start, mid, idx, diff)
        self.update_tree_helper(self.right_child(node), mid + 1, end, idx, diff)

    def query_helper(self, node, start, end, left, right):
        if left <= start and right >= end:
            return self.tree[node]
        if left > end or right < start:
            return 0
        mid = (start + end) // 2
        return self.query_helper(
            self.left_child(node), start, mid, left, right
        ) + self.query_helper(self.right_child(node), mid + 1, end, left, right)


class LazySegmentTree:
    def __init__(self, arr):
        self.arr = arr
        self.arr_size = len(arr)
        self.size = 4 * self.arr_size
        self.tree = [0] * self.size
        self.lazy = [0] * self.size
        self.build_tree(0, 0, self.arr_size - 1)

    def left_child(self, node):
        return 2 * node + 1

    def right_child(self, node):
        return 2 * node + 2

    def build_tree(self, node, start, end):
        if start == end:
            self.tree[node] = self.arr[start]
            return self.tree[node]
        mid = (start + end) // 2
        self.tree[node] = self.build_tree(
            self.left_child(node), start, mid
        ) + self.build_tree(self.right_child(node), mid + 1, end)
        return self.tree[node]

    def update_diff(self, index, diff):
        self.update_helper(0, 0, self.arr_size - 1, index, index, diff)

    def update_range(self, left, right, value):
        self.update_helper(0, 0, self.arr_size - 1, left, right, value)

    def update_helper(self, node, start, end, left, right, diff):
        # Handle lazy propagation
        if self.lazy[node] != 0:
            self.tree[node] += self.lazy[node] * (end - start + 1)
            if start != end:
                self.lazy[self.left_child(node)] += self.lazy[node]
                self.lazy[self.right_child(node)] += self.lazy[node]
            self.lazy[node] = 0

        if start > right or end < left or start > end:
            return

        if start >= left and end <= right:
            self.tree[node] += diff * (end - start + 1)
            if start != end:
                self.lazy[self.left_child(node)] += diff
                self.lazy[self.right_child(node)] += diff
            return

        mid = (start + end) // 2
        self.update_helper(self.left_child(node), start, mid, left, right, diff)
        self.update_helper(self.right_child(node), mid + 1, end, left, right, diff)
        self.tree[node] = (
            self.tree[self.left_child(node)] + self.tree[self.right_child(node)]
        )

    def query(self, left, right):
        return self.query_helper(0, 0, self.arr_size - 1, left, right)

    def query_helper(self, node, start, end, left, right):
        if self.lazy[node] != 0:
            self.tree[node] += self.lazy[node] * (end - start + 1)
            if start != end:
                self.lazy[self.left_child(node)] += self.lazy[node]
                self.lazy[self.right_child(node)] += self.lazy[node]
            self.lazy[node] = 0
        if start >= left and end <= right:
            return self.tree[node]

        if start > right or end < left:
            return 0

        mid = (start + end) // 2
        return self.query_helper(
            self.left_child(node), start, mid, left, right
        ) + self.query_helper(self.right_child(node), mid + 1, end, left, right)

    def clear(self):
        for i in range(self.arr_size):
            self.query(i, i)


if __name__ == "__main__":
    arr = [2, 12, 3, 4]
    st = SegmentTree(arr)
    print(st.query(0, 3))
    st.update_value(1, 2)
    print(st.query(0, 3))
    lst = LazySegmentTree(arr)
    print(lst.query(0, 3))  # Output: 21
    lst.update_range(1, 2, 5)
    print(lst.query(0, 3))  # Output: 31
    print(lst.query(0, 2))  # Output: 27
    lst.update_range(2, 3, 4)
    print(lst.query(0, 3))  # Output: 39
