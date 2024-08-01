"""                     LEETCODE DFS PROBLEMS TO PRACTICE
    Easy
104. Maximum Depth of Binary Tree (can be solved with DFS)
100. Same Tree
101. Symmetric Tree (can be solved with DFS)
226. Invert Binary Tree
112. Path Sum
Medium
200. Number of Islands
133. Clone Graph
547. Number of Provinces (formerly known as "Friend Circles")
797. All Paths From Source to Target
694. Number of Distinct Islands
Hard
212. Word Search II (can be solved with DFS)
329. Longest Increasing Path in a Matrix
124. Binary Tree Maximum Path Sum
140. Word Break II
968. Binary Tree Cameras


    visited=None, ensures that each time you call dfs_recursive without 
    providing a visited set, a new set is created
"""
def dfs_recursive(graph, start, visited=None):
    if visited is None:
        visited = set()  # Initialize a new set for each call

    visited.add(start)
    print(start)  # Print the current node or perform any action

    for neighbor in graph[start]:
        if neighbor not in visited:
            dfs_recursive(graph, neighbor, visited)

# Example usage
graph = {
    'A': ['B', 'C'],
    'B': ['A', 'D', 'E'],
    'C': ['A', 'F'],
    'D': ['B'],
    'E': ['B', 'F'],
    'F': ['C', 'E']
}

dfs_recursive(graph, 'A')
print("******")
dfs_recursive(graph, 'A')
