from collections import deque

"""
                LEETCODE BFS PROBLEMS TO PRACTICE

        Easy
104. Maximum Depth of Binary Tree = DONE✅
101. Symmetric Tree = DONE✅
111. Minimum Depth of Binary Tree DONE✅
637. Average of Levels in Binary Tree
733. Flood Fill

Medium
199. Binary Tree Right Side View
279. Perfect Squares
102. Binary Tree Level Order Traversal
210. Course Schedule II
542. 01 Matrix
994. Rotting Oranges
130. Surrounded Regions
Hard
297. Serialize and Deserialize Binary Tree
126. Word Ladder II
212. Word Search II
847. Shortest Path Visiting All Nodes
1345. Jump Game IV


"""
def bfs(graph, start):
    q = deque([start])
    visited = set([start])

    while q:
        node = q.popleft()
        print(node, end=' ')

        for neighbor in graph[node]:
            if neighbor not in visited:
                visited.add(neighbor)
                q.append(neighbor)