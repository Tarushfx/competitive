from collections import defaultdict 
import sys
# sys.stdin = open('input.txt', 'r')
# sys.stdout = open('output.txt', 'w')
sys.setrecursionlimit(10**6)
for _ in range(int(input())):
    n=int(input())
    graph=[[] for _ in range(n+1)]
    ans=[0]
    def dfs(node,visited,ans,par=None):
        if visited[node]: return 0
        visited[node]=True
        total_nodes=1
        for nei,w in graph[node]:
            if nei==par:continue
            x=dfs(nei,visited,ans,node)
            ans[0]+=2*min(x,n-x)*w
            total_nodes+=x
        return total_nodes
    for i in range(n-1):
        u,v,w=[int(i) for i in input().split()]
        graph[u].append([v,w])
        graph[v].append([u,w])
    visited=[False]*(10**5+1)
    dfs(1,visited,ans)
    print("Case #{}: {}".format(_+1,ans[0]))