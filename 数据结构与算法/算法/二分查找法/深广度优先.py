#coding=utf-8
'''
490. The Maze
小球能否从起点滚到终点
'''
# BFS思路：
# 建立一个queue,先将start放入队列。每次从队列头部拿到一个位置，如果该位置是
# 终点则直接返回，否则就看该位置是否被访问过，如果没有被访问，将其四个方向
# 上移动最终停靠的点加入队列作为下次的起点，并标记该位置被访问过了，如果队列
# 为空还没有发现可以到达的路径，说明无法到达。

from collections import deque
direction = [(-1, 0), (0, 1), (0, -1), (1, 0)]

def hasPath(maze, start, destination):
    m,n = len(maze), len(maze[0])
    if n == 0 or m == 0:
        return False
    isvisited = [[False for _ in range(n)] for _ in range(m)]
    q = deque()
    q.append(start)
    isvisited[start[0]][start[1]] = True
    while (q):
        cur_pos = q.popleft()
        for i in range(4):
            next_pos = go(maze, cur_pos, i)
            if not isvisited[next_pos[0]][next_pos[1]]:
                if (next_pos == destination):
                    return True
                q.append(next_pos)
                isvisited[next_pos[0]][next_pos[1]] = True

    return False
 
            
def go(maze, start, i):
    m = len(maze)
    n = len(maze[0])
    y, x = start
    while (0 <= x < n and 0 <= y < m and maze[y][x] ==0):
        y += direction[i][0]
        x += direction[i][1]
    y -= direction[i][0]
    x -= direction[i][1]
    return y, x   

def go2(maze, start, i):
    m = len(maze)
    n = len(maze[0])
    while (True):
        y,x = tuple(map(lambda a,b:a+b,start,direction[i]))     
        if (0 <=x < n and 0 <= y < m and maze[y][x] == 0):
            start = (y, x)
        else:
            return start    


# DFS:
# 递归调用+记忆化搜索，先沿着一条路走到底
def hasPath2(maze, start, destination):
    m, n = len(maze), len(maze[0])
    if (m == 0 or n == 0):
        return False
    dp = [[-1 for _ in range(n)] for _ in range(m)]
    isvisited = [[False for _ in range(n)] for _ in range(m)]
    return _hasPath(maze, dp, isvisited, start, destination)
    
def _hasPath(maze, dp, isvisited, start, destination):
    if (dp[start[0]][start[1]] != -1):
        return dp[start[0][start[1]]]
    if (start == destination):
        return True
    isvisited[start[0]][start[1]] = True
    res = False
    for i in range(4):
        next_pos = go(maze, start, i)
        if (not isvisited[next_pos[0]][next_pos[1]]):
            res |= _hasPath(maze, dp, isvisited, next_pos, destination)
    dp[start[0]][start[1]] = res
    return res
    
            

maze1 = [[0, 0, 1, 0, 0],
         [0, 0, 0, 0, 0],
         [0, 0, 0, 1, 0],
         [1, 1, 0, 1, 1],
         [0, 0, 0, 0, 0]]

# start1 = (0, 4)
# des1 = (4, 4)
# print(hasPath2(maze1, start1, des1))
# start2 = (0, 4)
# des2=(3,2)
# print(hasPath2(maze1, start2, des2))



'''
127. Word Ladder
给定两个单词（beginWord 和 endWord）和一个字典，找到从 beginWord 到 endWord 的最短转换序列的长度。
转换需遵循如下规则：
1.每次转换只能改变一个字母。
2.转换过程中的中间单词必须是字典中的单词
'''
# BFS最适合寻找最短路径了，每次搜索从小的可能路径长度为1,2,3，依次探索下去。
def ladderLength(beginWord: str, endWord: str, wordList) -> bool:
    if endWord not in wordList:
        return 0
    if beginWord not in wordList:
        wordList.append(beginWord)
    q = deque()
    q.append(wordList.index(beginWord))
    step = [0 for _ in range(len(wordList))]
    step[wordList.index(beginWord)] = 1

    g = [[False for _ in range(len(wordList))] for _ in range(len(wordList))]
    for i in range(len(wordList)):
        for j in range(i):
            g[i][j] = g[j][i] = similar(wordList[i], wordList[j])
            
    while q:
        cur = q.popleft()
        for i in range(len(wordList)):
            if step[i]==0 and g[cur][i]:
                if wordList[i] == endWord:
                    return step[cur] + 1
                step[i] = step[cur]+ 1
                q.append(i)
    
    return 0

def ladderLength(beginWord: str, endWord: str, wordList) -> bool:
    if endWord not in wordList:
        return 0

    q = deque()
    q.append((beginWord, 1))
    if beginWord in wordList:
        wordList.remove(beginWord)
    visited = []
         
    while q:
        visited.clear()
        cur,step = q.popleft()
        for w in wordList:
            if similar(cur, w):
                if w == endWord:
                    return step + 1
                visited.append(w)
                q.append((w, step + 1))
        
        for i in visited:
            wordList.remove(i)
    
    return 0


# Bi-directional BFS
def ladderLength3(beginWord, endWord, wordList):
    if endWord not in wordList:
        return 0
    if beginWord not in wordList:
        wordList.append(beginWord)
    q = deque()
    q.append(wordList.index(beginWord))
    step = [0 for _ in range(len(wordList))]
    step[wordList.index(beginWord)] = 1
    q2 = deque()
    q2.append(wordList.index(endWord))
    step2 = [0 for _ in range(len(wordList))]
    step2[wordList.index(endWord)] = 1

    while q and q2:
        cur = q.popleft()
        cur2 = q2.popleft()
        for i in range(len(wordList)):
            if step[i] == 0 and similar(wordList[i], wordList[cur]):
                q.append(i)
                step[i] = step[cur] + 1
            if step2[i] == 0 and similar(wordList[i], wordList[cur2]):
                q2.append(i)
                step2[i] = step2[cur2] + 1
        for i in range(len(wordList)):
            if step[i] != 0 and step2[i] != 0:
                return step[i] + step2[i] - 1
            
    return 0



def similar(word1, word2) -> bool:
    assert (word1 != word2 and len(word1) == len(word2))
    diff=0
    for w1, w2 in zip(word1, word2):
        if w1 != w2:
            diff += 1
            if diff > 1:
                return False
    return True 


'''
126.WordLadderII 打印出所有可能的最短转换序列(Hard)
'''


'''
130. 被围绕的区域
给定一个二维的矩阵，包含 'X' 和 'O'（字母 O）。
找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。
在边界上以及和边界相连的0不会被填充
'''
# 思路：遍历所有元素，发现'O'开始广度搜索，如果发现下一个搜索点出界了，说明和外面连通了，
# 这种情况就说明不应该改变为'X'，如果发现没有，则记录好所有的元素，全部改变就好了。
def solve(board: List[List[str]]) -> None:
    m, n = len(board), len(board[0])
    if (m == 0 or n == 0):
        return
    visited = [[False for _ in range(n)] for _ in range(m)]
    for i in range(m):
        for j in range(n):
            if (board[i][j] == 'O' and not visited[i][j]):
                record=[]
                if (bfs(board, i, j, visited, record)): # True 和边界不连通
                    for r in record:
                        board[r[0]][r[1]] = 'X'
                        
    return 

direction = [(-1, 0), (0, 1), (1, 0), (0, -1)]                    
def bfs(board, i, j, visited, record):
    q = deque()
    q.append((i, j))
    visited[k][l] = True
    ret=True
    while q:
        cur = q.popleft()
        record.append(cur)
        for d in direction:
            k,l = cur[0] + d[0], cur[1] + d[1]
            if (not inAera(k,l)):
                ret=False
            elif (board[k][l] == 'O' and not visited[k][l]):
                q.append((k, l))
                visited[k][l] = True   
    
    return ret

def inArea(i, j):
    return 0 <= i < m and 0 <= j < n
            

        

    



