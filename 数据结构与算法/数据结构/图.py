#coding=utf8

class DenseGraph:
    def __init__(self, n, directed):
        self.n=n
        self.m = 0
        self.directed = directed
        self.g = [[False for _ in range(n)] for _ in range(n)]
    
    def V(self):
        return self.n
    
    def E(self):
        return self.m

    def addEdge(self, v, w):
        if 0 <= v < self.n and 0 <= w < self.n:    
            if self.hasEdge(v, w):
                return
            self.g[v][w] = True
            if (not self.directed):
                self.g[w][v] = True
            self.m += 1
        else:
            raise Exception('Vertex not in the graph')
                
    def hasEdge(self, v, w):
        if 0 <= v < self.n and 0 <= w < self.n: 
            return self.g[v][w]
        else:
            raise Exception('Vertex not in the graph')

    def Dgen(self, v):
        for i in range(self.V()):
            if (self.g[v][i]):
                yield i

    def show(self):
        for i in range(self.n):
            for j in range(self.n):
                print(1 if self.g[i][j] else 0, end=' ')
            print('')

class SparseGraph:
    def __init__(self, n, directed):
        self.n = n
        self.m = 0
        self.directed = directed
        self.g = [[] for _ in range(n)]

    def V(self):
        return self.n
    
    def E(self):
        return self.m

    def addEdge(self, v, w):
        if 0 <= v < self.n and 0 <= w < self.n:    
            self.g[v].append(w)
            if (v!=w and not self.directed):
                self.g[w].append(v)
            self.m += 1
        else:
            raise Exception('Vertex not in the graph')

        
    def hasEdge(self):
        if 0 <= v < self.n and 0 <= w < self.n: 
            for i in range(len(self.g[v])):
                if g[v][i] == w:
                    return True
            return False
        else:
            raise Exception('Vertex not in the graph')

    def Sgen(self,v):
        for i in range(len(self.g[v])):
            yield self.g[v][i]

    def show(self):
        for i in range(self.n):
            print(f"vertex {i}: ",end='')
            for j in range(len(self.g[i])):
                print(self.g[i][j], end=' ')
            print('')
        
class SIterator:
    def __init__(self, graph, v):
        self.v = v
        self.G = graph
        self.index = -1
        
    def __iter__(self):
        return self

    def __next__(self):
        self.index += 1
        if self.index >= len(self.G.g[self.v]):
            raise StopIteration
        return self.G.g[self.v][self.index]


import re        
def buildGraph(graph, filePath):
    graphList=[]
    with open(filePath, 'r',encoding='utf-8') as f:
        for line in f:
            graphList.append([int(x) for x in re.split(r'\s', line.strip())])
    for i in range(len(graphList)):
        graph.addEdge(graphList[i][0],graphList[i][1])



# 查看图中的连通分量
class Component:
    def __init__(self, graph):
        self.g = graph
        self.visited =[False for _ in range(graph.V())]
        self.ccount = 0
        self.id = [0 for _ in range(graph.V())]
        for i in range(graph.V()):
            if (not self.visited[i]):
                self.dfs(i)
                self.ccount += 1
                self.id[i] += 1

    def count(self):
        return self.ccount
        
    def dfs(self, v):
        self.visited[v]=True
        sgen = self.g.Sgen(v)
        for w in sgen:
            if (not self.visited[w]):
                self.dfs(w)

    def isConnected(self, v, w):
        return self.id[v]==self.id[w]
        
# 深度优先遍历
class Path:
    def __init__(self, graph,s):
        self.g = graph
        self.visited =[False for _ in range(graph.V())]
        self.f = [-1 for _ in range(graph.V())]
        self.s = s
        self.dfs(s)

    def count(self):
        return self.ccount
        
    def dfs(self, v):
        self.visited[v]=True
        sgen = self.g.Sgen(v)
        for w in sgen:
            if (not self.visited[w]):
                self.f[w] = v
                self.dfs(w)

    def hasPath(self, w):
        return self.visited[w]

    def path(self, w, route):
        stack = []
        p = w
        while p != -1:
            stack.append(p)
            p = self.f[p]
        route.extend(stack[::-1])

    def showPath(self, w):
        route=[]
        self.path(w, route)
        for i in range(len(route)):
            if (i == len(route) - 1):
                print(route[i])
            else:
                print(route[i], end='->')



# 广度优先遍历
from collections import deque
class ShortestPath:
    def __init__(self, graph,s):
        self.g = graph
        self.visited =[False for _ in range(graph.V())]
        self.f = [-1 for _ in range(graph.V())]
        self.s = s
        self.ord = [-1 for _ in range(graph.V())]
        self.bfs(s)

    def count(self):
        return self.ccount
        
    def bfs(self, v):
        q = deque()
        q.append(v)
        self.visited[v] = True
        self.ord[v] = 0
        while q:
            k = q.popleft()
            sgen = self.g.Sgen(k)
            for w in sgen:
                if (not self.visited[w]):
                    q.append(w)
                    self.visited[w] = True
                    self.f[w] = k
                    self.ord[w] = self.ord[k] + 1


    def hasPath(self, w):
        return self.visited[w]

    def path(self, w, route):
        stack = []
        p = w
        while p != -1:
            stack.append(p)
            p = self.f[p]
        route.extend(stack[::-1])

    def showPath(self, w):
        route=[]
        self.path(w, route)
        for i in range(len(route)):
            if (i == len(route) - 1):
                print(route[i])
            else:
                print(route[i], end='->')
    
    def length(self, w):
        return self.ord[w]




if __name__ == '__main__':
    g1 = SparseGraph(13, False)
    buildGraph(g1, 'testG1.txt')
    # g1.show()
    # print('')
    g2 = SparseGraph(7, False)
    buildGraph(g2, 'testG2.txt')
    # g2.show()
    # component1 = Component(g1)
    # print(component1.count())
    # component2 = Component(g2)
    # print(component2.count())
    path2 = Path(g2, 0)
    print("DFS: ",end='')
    path2.showPath(6)
    path3 = ShortestPath(g2, 0)
    print("BFS: ", end='')
    path3.showPath(6)
    print(path3.length(6))


    # import random
    # N, M = 20, 100
    # g1 = SparseGraph(N, False)
    # for _ in range(M):
    #     a = random.randint(0,N-1)
    #     b = random.randint(0, N - 1)
    #     g1.addEdge(a, b)
        
    # for v in range(N):
    #     print(v," : ",end='')
    #     # s = SIterator(g1, v)
    #     s = g1.Sgen(v) #使用生成器
    #     for w in s:
    #         print(w, end=' ')
    #     print("")
    # print('')
    # g2 = DenseGraph(N, False)
    # for _ in range(M):
    #     a = random.randint(0, N - 1)
    #     b = random.randint(0, N - 1)
    #     g2.addEdge(a, b)
        
    # for v in range(N):
    #     print(v," : ",end='')
    #     # s = SIterator(g1, v)
    #     s = g2.Dgen(v) #使用生成器
    #     for w in s:
    #         print(w, end=' ')
    #     print("")




        


        
        

