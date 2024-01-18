from collections import defaultdict
import heapq
from math import inf


def dj(n, graph, src):
    dist = [inf] * (n)
    # dist=defaultdict(lambda:inf)
    dist[src] = 0
    heap = [[0, src]]
    visited = set()
    ans = -inf
    while heap:
        w, u = heapq.heappop(heap)
        if u in visited:
            continue
        ans = max(ans, w)
        visited.add(u)
        for nei, d in graph[u]:
            if nei not in visited:
                if dist[nei] > w + d:
                    dist[nei] = w + d
                heapq.heappush(heap, (dist[nei], nei))

    if len(visited) != n:
        return -1
    return ans


def BellmanFord(n, edges, src):
    dist = [inf] * n
    dist[src] = 0
    for _ in range(n):  # n+1 to find -w cycle
        tmp = list(dist)
        for start, to, cost in edges:
            tmp[to] = min(dist[start] + cost, tmp[to])
        if dist == tmp:
            break
        dist = tmp
    return dist


def edge_to_matrix(n, edges):
    dist = [[inf] * n for _ in range(n)]
    for u, v, w in edges:
        dist[u][v] = w

    return dist


def floyd_washall(n, dist):
    r, c = len(dist), len(dist[0])

    if r != c:
        dist = edge_to_matrix(n, dist)
    for k in range(n):
        # pick all vertices as source one by one
        for i in range(n):
            # Pick all vertices as destination for the
            # above picked source
            for j in range(n):
                # If vertex k is on the shortest path from
                # i to j, then update the value of dist[i][j]
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

    return dist


class DSU:
    def __init__(self, n):
        # self.parent = [-1] * n
        # self.rank = [1] * n
        self.parent = defaultdict(lambda: -1)
        self.rank = defaultdict(lambda: 1)

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


def kruskalsMST(n, edges):
    dsu = DSU(n)
    sorted_edges = sorted(edges, key=lambda x: x[2])
    mst = []
    for u, v, w in sorted_edges:
        if dsu.union(u, v):
            mst.append([u, v])
    return mst


def edge_to_graph(edges):
    graph = defaultdict(list)
    for u, v, w in edges:
        graph[u].append([v, w])
        graph[v].append([u, w])


def primsMST(n, edges):
    graph = defaultdict(list)
    for u, v, w in edges:
        graph[u].append([v, w])
        graph[v].append([u, w])
    heap = [(0, 0, -1)]  # all edges if disconnected
    visited = set()
    mst = []
    while heap:
        w, node, par = heapq.heappop(heap)
        if node in visited:
            continue
        visited.add(node)
        if par != -1:
            mst.append([node, par])
        if len(visited) == n:
            return mst

        for nei, d in graph[node]:
            if nei not in visited:
                heapq.heappush(heap, (d, nei, node))
    return mst


if __name__ == "__main__":
    edges = [[1, 0, 3], [2, 1, 4], [0, 2, 2], [1, 3, 5]]
    print(kruskalsMST(4, edges))
    print(primsMST(4, edges))
