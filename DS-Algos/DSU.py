class DSU:
    def __init__(self, n):
        self.parent = [-1] * n
        self.rank = [1] * n

    def union(self, a, b):
        pa, pb = self.find(a), self.find(b)
        if pa == pb:
            return False
        if self.rank[pa] > self.rank[pb]:
            self.parent[pb] = pa
            self.rank[pa] += self.rank[pb]
        else:
            self.parent[pa] = pb
            self.rank[pb] += self.rank[pa]
        return True

    def find(self, a):
        if self.parent[a] == -1:
            return a
        pa = self.find(self.parent[a])
        self.parent[a] = pa
        return pa
