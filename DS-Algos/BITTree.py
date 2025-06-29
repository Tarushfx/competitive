"""
sum[11]=tree[11]+tree[10]+tree[8]
6:110 equals [1:4]+[5:6] or tree[4]+tree[6]
tree[6]=A[5]+A[6] (area of responsibilty)
updating 6 affects 8:1000,16:10000....
"""


class BITTree:
    def __init__(self, arr):
        self.arr = arr
        self.arr_size = len(self.arr)
        self.size = self.arr_size
        self.tree = [0] * (self.size + 1)
        self.build_tree()

    def LSB(self, index):
        return index & -index

    def build_tree(self):
        for i in range(1, self.size + 1):
            index = i
            while index <= self.size:
                self.tree[index] += self.arr[i - 1]
                index += self.LSB(index)

    def update_value(self, index, value):
        diff = value - self.arr[index]
        self.arr[index] = value
        self.update_helper(index, diff)

    def update_diff(self, index, diff):
        self.update_helper(index, diff)

    def update_helper(self, index, diff):
        index += 1
        while index <= self.size:
            self.tree[index] += diff
            index += self.LSB(index)

    def query(self, left, right):
        return self.query_helper(right) - self.query_helper(left - 1)

    def query_helper(self, index):
        res = 0
        index += 1
        while index > 0:
            res += self.tree[index]
            index -= self.LSB(index)

        return res
