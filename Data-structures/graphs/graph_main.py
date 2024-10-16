"""
                        GRAPHS
    - A graph is a data structure consisting of vertices (nodes) and edges connecting them. It models relationships 
        between objects in computer science and mathematics.
    - Vertices: Represent entities or objects, such as people in a social network.
    - Edges: Represent the connections between vertices.
        - Directed Edge: Has a direction, going from one vertex to another (u, v)
        - Undirected Edge: No direction; the connection is mutual between vertices (u, v)

    TYPES OF GRAPHS

    - Directed Graph: Edges have a direction, meaning connections are one-way.
        - Example: A web page linking to another.

    - Undirected Graph: Edges have no direction, meaning connections are two-way.
        - Example: Friendships in a social network.
    
    - Weighted Graph: Edges have weights or costs (e.g., distances between cities).
        - Example: A road network with distances between cities.
    
    - Unweighted Graph: All edges are equal with no weights.

    - Cyclic Graph: Contains at least one cycle (a path that returns to the starting vertex).

    - Acyclic Graph: No cycles, meaning paths don’t return to the starting point.

    - Connected Graph: Every pair of vertices has a path between them.

    - Disconnected Graph: At least one pair of vertices has no path between them.

    - Tree: A connected, acyclic graph.
        - Every tree is a graph but not every graph is a tree. Graphs can be disconnected and can have cycles in them.

    GRAPH REPRESENTATION

        1. ADJACENCY MATRIX
            - A 2D matrix where rows and columns represent vertices. If there's an edge between two vertices, 
                the matrix value is 1 (or the edge's weight in a weighted graph), otherwise, it's 0.
            - Example:
                  A  B  C
                A [0, 1, 1]
                B [1, 0, 1]
                C [1, 1, 0]
            - Pros: Easy to implement, good for dense graphs.
            - Cons: Uses a lot of space, even for sparse graphs. it uses O(V^2) of space

        2. ADJACENCY LIST
            - Each vertex has a list of connected vertices.
            - Example:
                A: [B, C]
                B: [A, C]
                C: [A, B]
            - Pros: Space-efficient for sparse graphs. it uses O(V + E) of space
            - Cons: Less efficient for dense graphs.

        3. EDGE LIST
            - A list of all edges, each represented as a pair of connected vertices.
            - Example: [(A, B), (B, C), (C, A)]
            - Pros: Compact, only stores edges.
            - Cons: Inefficient for checking specific connections.
    
    GRAPH TRAVERSAL ALGORITHMS
        1. Depth First Search (DFS)
            - Explores a graph by starting at a vertex and following a path as deep as possible before backtracking to explore new paths.
            - DFS uses a stack (either explicitly or via recursion) to keep track of vertices.
            - DFS is useful for:
                - Finding connected components
                - Detecting cycles in a graph
                - Solving maze problems

        2. Breadth First Search (BFS)
            - Explores a graph by starting at a vertex and visiting all of its neighbors before moving to the next level of vertices.
            - BFS uses a queue to manage the traversal process.
            - BFS is useful for:
                - Finding the shortest path in an unweighted graph
                - Solving problems like finding the minimum number of moves in a game
    
    GRAPH ALGORITHMS

        1. SHORTEST PATH ALGORITHM
            - Dijkstra's Algorithm: Finds the shortest path from a single source vertex to all other vertices in a graph 
                    with non-negative edge weights.
            - Bellman-Ford Algorithm: Solves the shortest path problem for graphs with negative weights but is slower than Dijkstra's.

        2. MINIMUM SPANNING TREE (MST)
            - Prim’s Algorithm: Builds an MST by starting from an arbitrary vertex and expanding the tree by adding the smallest edge 
                    that connects a new vertex.
            - Kruskal’s Algorithm: Builds an MST by sorting all edges by weight and adding edges one by one while avoiding cycles.

        3. TOPOLOGICAL SORT
            - An ordering of the vertices in a directed acyclic graph (DAG) such that for every directed edge U->V, vertex u appears before v 
                    in ordering
            - Used in scheduling problems, where certain tasks must be completed before others.

        4. CYCLE DETECTION
            - Detects if a graph contains cycles.
            - In a directed graph, this can be done using DFS. If a back edge is found (an edge that points to an ancestor 
                in the recursion stack), there is a cycle.

        5. GRAPH COLORING
            - Assigns colors to vertices of a graph such that no two adjacent vertices share the same color.
            - Useful in scheduling problems, register allocation in compilers, and map coloring.

"""
from collections import deque, defaultdict
#
# Implementation of a graph using an adjacency matrix##

class Graph1:
    def __init__(self, num_vertices):
        # Initialize the adjacency matrix with 0s
        self.num_vertices = num_vertices
        self.adj_matrix = []
        for i in range(num_vertices):
            row = [0] * num_vertices  # Create a row with num_vertices zeros
            self.adj_matrix.append(row)

    def add_edge(self, u, v, weight=1):
        # Add an edge between vertex u and vertex v with optional weight (default is 1)
        self.adj_matrix[u][v] = weight
        self.adj_matrix[v][u] = weight  # Uncomment this line for undirected graphs

    def remove_edge(self, u, v):
        # Remove the edge between vertex u and vertex v
        self.adj_matrix[u][v] = 0
        self.adj_matrix[v][u] = 0  # Uncomment this line for undirected graphs

    def display(self):
        # Display the adjacency matrix
        for row in self.adj_matrix:
            print(row)

# Implementation of a graph using adjacency lists

class Graph:
    def __init__(self, num_vertices):
        # Initialize an adjacency list for each vertex
        self.num_vertices = num_vertices
        self.adj_list = {}
        for i in range(num_vertices):
            self.adj_list[i] = []

    def add_edge(self, u, v):
        # Add an edge between vertex u and vertex v
        self.adj_list[u].append(v)
        self.adj_list[v].append(u)  # Uncomment this line for undirected graphs
    
    def remove_edge(self, u, v):
        # Remove the edge between vertex u and vertex v
        if v in self.adj_list[u]:
            self.adj_list[u].remove(v)
        if u in self.adj_list[v]:
            self.adj_list[v].remove(u)  # Uncomment this line for undirected graphs

    def display(self):
        # Display the adjacency list
        for vertex in self.adj_list:
            print(f"{vertex}: {self.adj_list[vertex]}")

# DFS using recursion
def dfs(graph, start):
    visited = set()  # Use a set to keep track of visited nodes
    res = []  # To store the result of DFS traversal
    dfsUtil(graph, start, visited, res)

    return res

def dfsUtil(graph, start, visited, res):
    res.append(start)  # Add the current node to the result
    visited.add(start)  # Mark the current node as visited

    # Explore all neighbors of the current node
    for neighbor in graph[start]:
        if neighbor not in visited:  # Visit unvisited neighbors
            dfsUtil(graph, neighbor, visited, res)

# DFS using stack (iterative approach)
def dfsIterative(graph, start):
    stack = []
    res = []
    visited = set()

    # Start by adding the starting node to the stack and marking it visited
    stack.append(start)
    visited.add(start)

    while stack:
        curr = stack.pop()  # Pop the top element of the stack
        res.append(curr)  # Append the current node to the result

        # Add neighbors to the stack in reverse order to maintain DFS behavior
        for neighbor in reversed(graph[curr]):
            if neighbor not in visited:
                stack.append(neighbor)  # Push unvisited neighbors to the stack
                visited.add(neighbor)  # Mark them as visited to avoid reprocessing
    
    return res

# BFS (Breadth-First Search) Implementation
def bfs(graph, start):
    q = deque()      # Queue to process nodes in FIFO order
    visited = set()  # Set to track visited nodes
    res = []         # List to store the result of BFS traversal

    q.append(start)  # Start BFS from the given start node
    visited.add(start)

    while q:
        curr = q.popleft()  # Dequeue the first node
        res.append(curr)    # Add it to the result list

        # Explore all neighbors of the current node
        for neighbor in graph[curr]:
            if neighbor not in visited:  # Visit only unvisited neighbors
                q.append(neighbor)       # Enqueue the neighbor
                visited.add(neighbor)    # Mark it as visited
    
    return res

# BFS for a matrix graph
"""
    The BFS starts at the top-left corner (0, 0) and explores its neighboring cells in all four directions (up, down, left, right). 
    It continues to visit unvisited cells until the entire connected region of the matrix is explored. 

    Directions:
        -  We define a list directions that contains the four possible directions (up, down, left, right) that we can move in the matrix.  
"""
def bfs_matrix(graph, start):
    rows = len(graph)
    cols = len(graph[0])
    
    # Queue for BFS and set to track visited nodes
    q = deque()
    visited = set()
    res = []

    # Start BFS from the given start position (row, col)
    q.append(start)
    visited.add(start)

    # Directions for moving to neighboring cells: up, down, left, right
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

    while q:
        curr = q.popleft()
        row, col = curr
        res.append((row, col))  # Add the current cell to the result

        # Explore all 4 neighbors (up, down, left, right)
        for dr, dc in directions:
            new_row, new_col = row + dr, col + dc

            # Check if the new position is within bounds and unvisited
            if 0 <= new_row < rows and 0 <= new_col < cols and (new_row, new_col) not in visited:
                q.append((new_row, new_col))  # Enqueue the neighbor
                visited.add((new_row, new_col))  # Mark the neighbor as visited
    
    return res

# DFS for a matrix graph
"""
    The graph is represented as a 2D matrix. Each cell in the matrix is treated as a node, and neighboring cells (up, down, left, right) 
    are considered as connected by edges. start is a tuple representing the starting position (row, col).

    directions define the possible moves (up, down, left, right) from each cell.

"""
def dfs_matrix(graph, start):
    rows = len(graph)
    cols = len(graph[0])
    
    visited = set()  # Set to track visited nodes
    res = []

    # Start DFS from the given start position (row, col)
    start_row, start_col = start
    dfs_helper(graph, start_row, start_col, visited, res, rows, cols)

    return res

# Helper function for DFS
def dfs_helper(graph, row, col, visited, res, rows, cols):
    # Directions for moving to neighboring cells: up, down, left, right
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

    # Add the current cell to the result and mark it as visited
    res.append((row, col))
    visited.add((row, col))

    # Explore neighbors (up, down, left, right)
    for dr, dc in directions:
        new_row, new_col = row + dr, col + dc

        # Check if the new position is within bounds and unvisited
        if 0 <= new_row < rows and 0 <= new_col < cols and (new_row, new_col) not in visited:
            dfs_helper(graph, new_row, new_col, visited, res, rows, cols)  # Recursive DFS call for the neighbor


"""             PRACTICE PROBLEMS 
    DFS Matrix
        1. Number of islands
        2. Max Area of island
    BFS Matrix
        1. Shortest Path in Binary Matrix
        2. Rotting oranges

    Adjecency List
        1. Clone graph
        2. course Schedule

"""

""" Problem: Number of islands (using DFS)
    - Here’s the approach using DFS:
        - Iterate through each cell in the grid.
        - When a '1' (land) is found, increment the island count and start a DFS to mark all adjacent '1's as visited 
                (i.e., turn them into '0's or use a visited array).
        - Continue until all cells are processed.
    - Time and space complexity:
        time: O(n * m):  where n is the number of rows and m is the number of columns. We visit each cell once.
        space: O(n * m): in the worst case due to the recursion stack in DFS.
"""
def numIslands(grid):
    if not grid:
        return 0

    def dfs(grid, i, j):
        # Base case: if out of bounds or water ('0'), stop recursion
        if i < 0 or i >= len(grid) or j < 0 or j >= len(grid[0]) or grid[i][j] == '0':
            return
        
        # Mark the current cell as water ('0') to avoid re-visiting it
        grid[i][j] = '0'
        
        # Perform DFS in all four possible directions
        dfs(grid, i - 1, j)  # up
        dfs(grid, i + 1, j)  # down
        dfs(grid, i, j - 1)  # left
        dfs(grid, i, j + 1)  # right

    num_islands = 0
    
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            if grid[i][j] == '1':  # If we find a land
                num_islands += 1  # Increment island count
                dfs(grid, i, j)  # Mark the whole island as visited
    
    return num_islands

"""Problem: Number of islands (using BFS)
    Given a 2D grid grid where '1' represents land and '0' represents water, count and return the number of islands.

    An island is formed by connecting adjacent lands horizontally or vertically and is surrounded by water. 
    You may assume water is surrounding the grid (i.e., all the edges are water).

    - Approach for BFS:
        - Iterate through the grid. For each '1' (land), start a BFS traversal.
        - For each '1' encountered, mark the entire connected component (island) by changing all '1's to '0's using BFS.
        - Each time BFS starts for a new '1', increment the island count.
        - BFS explores all four possible directions (up, down, left, right).
 """
def numIslands(grid):
    if not grid:
        return 0

    def bfs(grid, i, j):
        # Initialize queue with the current cell
        queue = deque([(i, j)])
        
        # Mark the starting cell as visited by setting it to '0'
        grid[i][j] = '0'
        
        # Define the directions for moving in the grid
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        
        # BFS loop
        while queue:
            x, y = queue.popleft()
            
            # Explore all four possible directions
            for dx, dy in directions:
                nx, ny = x + dx, y + dy
                
                # If the new position is within bounds and is land ('1'), visit it
                if 0 <= nx < len(grid) and 0 <= ny < len(grid[0]) and grid[nx][ny] == '1':
                    grid[nx][ny] = '0'  # Mark as visited
                    queue.append((nx, ny))  # Add to the queue to continue BFS

    num_islands = 0
    
    # Traverse through the grid
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            if grid[i][j] == '1':  # Found an unvisited land cell
                num_islands += 1  # Increment island count
                bfs(grid, i, j)  # Perform BFS to mark the entire island
    
    return num_islands

""" Problem: Max Area of Island

You are given a matrix grid where grid[i] is either a 0 (representing water) or 1 (representing land).
An island is defined as a group of 1's connected horizontally or vertically. 
You may assume all four edges of the grid are surrounded by water.
The area of an island is defined as the number of cells within the island.
Return the maximum area of an island in grid. If no island exists, return 0.

Input: grid = [
  [0,1,1,0,1],
  [1,0,1,0,1],
  [0,1,1,0,1],
  [0,1,0,0,1]
]

Output: 6

"""
class Solution:
    def maxAreaOfIsland(self, grid: List[List[int]]) -> int:
        # Get the number of rows and columns in the grid
        ROWS, COLS = len(grid), len(grid[0])

        # Depth First Search (DFS) function to explore the island
        def dfs(r, c):
            # Base case: check if the current cell is out of bounds or is water (0)
            if r < 0 or r >= ROWS or c < 0 or c >= COLS or grid[r][c] == 0:
                return 0
            
            # Mark the current land cell as visited by setting it to 0 (turning it into water)
            grid[r][c] = 0

            # Recursively check all four directions (up, down, left, right) and sum the area
            # Each DFS call will return the area of the connected land, and we add 1 for the current land cell
            return (1 + dfs(r - 1, c) +  # Explore upward
                        dfs(r + 1, c) +  # Explore downward
                        dfs(r , c - 1) +  # Explore left
                        dfs(r , c + 1))   # Explore right

        # Variable to store the maximum area of an island found
        maxArea = 0

        # Loop through each cell in the grid
        for r in range(ROWS):
            for c in range(COLS):
                # Only start DFS if the current cell is land (1)
                maxArea = max(maxArea, dfs(r, c))
        
        # Return the largest island area found
        return maxArea

""" Problem: Given a node in a connected undirected graph, return a deep copy of the graph.
Each node in the graph contains an integer value and a list of its neighbors.

class Node {
    public int val;
    public List<Node> neighbors;
}
The graph is shown in the test cases as an adjacency list. An adjacency list is a mapping of nodes to lists,
 used to represent a finite graph. Each list describes the set of neighbors of a node in the graph.
For simplicity, nodes values are numbered from 1 to n, where n is the total number of nodes in the graph. 
The index of each node within the adjacency list is the same as the node's value (1-indexed).
The input node will always be the first node in the graph and have 1 as the value.

Solution:
    - oldToNew dictionary: This stores the mapping between the original nodes and their clones. 
                It prevents revisiting nodes and allows reuse of already cloned nodes (to avoid infinite 
                recursion in cyclic graphs).
    DFS function:
        Base case: If the current node has already been visited (i.e., it's in the oldToNew dictionary), 
                    the function returns the previously created clone.
        Clone creation: A new copy of the node is created, and its value is the same as the original node 
                    (copy = Node(node.val)).
        Recursive cloning: The function then recursively clones each neighbor of the current node and appends 
                    the cloned neighbors to the copy's neighbors list.
        Edge case handling: If the input node is None, it simply returns None.

        Time: O(V + E) where V is the number of vertices and E is the number of edges. 
        Space: O(V) where V is the number of nodes due to the recursion stack and the space used by the oldToNew dictionary.

"""
class Solution:
    def cloneGraph(self, node: Optional['Node']) -> Optional['Node']:
        # Dictionary to store the mapping from the original node to its clone
        oldToNew = {}

        # Depth First Search (DFS) function to clone the graph
        def dfs(node):
            # If the node has already been cloned, return the cloned node
            if node in oldToNew:
                return oldToNew[node]
            
            # Create a new copy of the current node
            copy = Node(node.val)
            # Store the copy in the dictionary
            oldToNew[node] = copy

            # Recursively clone all the neighbors of the node
            for nei in node.neighbors:
                # Append the cloned neighbors to the copy's neighbors list
                copy.neighbors.append(dfs(nei))
            
            # Return the cloned node
            return copy
        
        # If the input node is None, return None (edge case)
        return dfs(node) if node else None

"""Problem: Build Order
    you are given a list of projects and a list of dependencies (which is a list of pairs of projects, where the second project
    is dependent on the first project). All of a project's dependencies must be built before the project is. Find a build order
    that will allow the projects to be built. if there is no valid build order, return an error.

    Example:
    input: 
        projects: a, b, c, d, e, f
        dependencies: (a, d), (f, b), (b, d), (f, a), (d, c)
    output: f,e,a,b,d,c

Steps:
    - Build the graph: Use an adjacency list to represent the graph where each project points to the projects 
                        dependent on it.
    - Track in-degrees: Maintain an array or dictionary to track the in-degree (number of dependencies) 
                            for each project.
    - Process nodes with zero in-degrees: Begin with projects that have no dependencies and 
                    gradually add projects to the build order once their dependencies are satisfied.
    - Detect cycles: If at any point we can't find a project with zero in-degree and there are still 
                projects left to process, it means there’s a cycle, and no valid build order exists.
"""
class Solution:
    def findBuildOrder(self, projects, dependencies):
        # Build the adjacency list and in-degree count
        adj_list = defaultdict(list)
        in_degree = {}
        
        # Initialize in-degree for each project
        for project in projects:
            in_degree[project] = 0
        
        # Fill the adjacency list and in-degree map
        for dep in dependencies:
            first, second = dep
            adj_list[first].append(second)  # first -> second
            in_degree[second] += 1  # Increment in-degree of second
        
        # Queue to maintain projects with zero in-degree (no dependencies)
        zero_in_degree_queue = deque()
        for project in projects:
            if in_degree[project] == 0:
                zero_in_degree_queue.append(project)
        
        # List to store the build order
        build_order = []
        
        # Process nodes with zero in-degrees
        while zero_in_degree_queue:
            current = zero_in_degree_queue.popleft()
            build_order.append(current)
            
            # For every project dependent on the current one
            for neighbor in adj_list[current]:
                in_degree[neighbor] -= 1  # Reduce the in-degree since one dependency is resolved
                
                # If the neighbor's in-degree drops to 0, add it to the queue
                if in_degree[neighbor] == 0:
                    zero_in_degree_queue.append(neighbor)
        
        # If the build order contains all the projects, return the build order
        if len(build_order) == len(projects):
            return build_order
        else:
            return "Error: No valid build order exists (cycle detected)."

""" Problem: Course Schedule
    You are given an array prerequisites where prerequisites[i] = [a, b] indicates that you must take course b first if you want to take course a.
    The pair [0, 1], indicates that must take course 1 before taking course 0.
    There are a total of numCourses courses you are required to take, labeled from 0 to numCourses - 1.
    Return true if it is possible to finish all courses, otherwise return false.

    Time complexity:
        O(V + E): where V is the number of courses and E is the number of prerequisite pairs Each course is processed once, and each edge (dependency) is checked once.
    Space complexity: 
        O( V + E): The space required for the graph and the in-degree dictionary.
"""
class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        # Create an adjacency list to represent the graph where each course points to the next courses dependent on it
        graph = defaultdict(list)
        
        # Dictionary to store the in-degree (number of prerequisites) for each course
        in_degree = {}
        
        # List to store the topological order (the order in which courses can be completed)
        top_order = []
        
        # Queue to process courses with zero in-degree (courses with no prerequisites)
        q = deque()

        # Initialize the in-degree of all courses to 0
        for i in range(numCourses):
            in_degree[i] = 0
        
        # Build the graph and update the in-degree of each course
        # For each prerequisite pair [v, u], u -> v, meaning to take course u, you must complete course v first
        for u, v in prerequisites:
            graph[v].append(u)  # Add the edge v -> u
            in_degree[u] += 1  # Increment the in-degree of course u

        # Add all courses with zero in-degree to the queue (courses that have no prerequisites)
        for j in range(numCourses):
            if in_degree[j] == 0:
                q.append(j)

        # Process the queue and build the topological order
        while q:
            curr = q.popleft()  # Get a course with zero in-degree
            top_order.append(curr)  # Add the course to the topological order

            # For each course that depends on the current course
            for nei in graph[curr]:
                in_degree[nei] -= 1  # Reduce the in-degree of the dependent course
                if in_degree[nei] == 0:  # If the dependent course now has zero in-degree, add it to the queue
                    q.append(nei)
        
        # If the number of courses in top_order equals the total number of courses, return True (no cycles, all courses can be completed)
        return numCourses == len(top_order)

"""
        Problem: Course Schedule ||

        You are given an array prerequisites where prerequisites[i] = [a, b] indicates that you must take course b first if you want to take course a.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
There are a total of numCourses courses you are required to take, labeled from 0 to numCourses - 1.

Return a valid ordering of courses you can take to finish all courses. If there are many valid answers, return any of them. 
If it's not possible to finish all courses, return an empty array.
"""

class Solution:
    def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:
        # Create an adjacency list to represent the graph where each course points to the next courses dependent on it
        graph = defaultdict(list)
        
        # Dictionary to store the in-degree (number of prerequisites) for each course
        in_degree = {}
        
        # List to store the topological order (the order in which courses can be completed)
        top_order = []
        
        # Queue to process courses with zero in-degree (courses with no prerequisites)
        q = deque()

        # Initialize the in-degree of all courses to 0
        for i in range(numCourses):
            in_degree[i] = 0
        
        # Build the graph and update the in-degree of each course
        # For each prerequisite pair [v, u], u -> v, meaning to take course u, you must complete course v first
        for u, v in prerequisites:
            graph[v].append(u)  # Add the edge v -> u (v is a prerequisite of u)
            in_degree[u] += 1  # Increment the in-degree of course u

        # Add all courses with zero in-degree to the queue (courses that have no prerequisites)
        for j in range(numCourses):
            if in_degree[j] == 0:
                q.append(j)
        
        # Process the queue and build the topological order
        while q:
            curr = q.popleft()  # Get a course with zero in-degree
            top_order.append(curr)  # Add the course to the topological order

            # For each course that depends on the current course
            for nei in graph[curr]:
                in_degree[nei] -= 1  # Reduce the in-degree of the dependent course
                if in_degree[nei] == 0:  # If the dependent course now has zero in-degree, add it to the queue
                    q.append(nei)
        
        # If the number of courses in top_order equals the total number of courses, return the topological order
        # If not, it means a cycle exists and no valid order is possible, so return an empty list
        return top_order if len(top_order) == numCourses else []

""" Problem: Walls and Gates
    You are given an m x n grid rooms initialized with these three possible values.
    -1 A wall or an obstacle.
    0 A gate.
    INF Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as 
        you may assume that the distance to a gate is less than 2147483647.
    Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, 
        it should be filled with INF.
    
    Algorithm:
        - use BFS to solve this:
            - start a BFS at the same time from the gates and explore each adjecent cells
        - if we use DFS to solve this problem it would take O(mn)^2
        - if we do BFS from the cells and not the gates we would end up in a dead end because we mark visited node.
    
    Time and space:
        - time: O(mn): where m * n is the total number of cells
        - space: the same as time.

"""
class Solution:
    def islandsAndTreasure(self, grid: List[List[int]]) -> None:
        # Get the number of rows and columns in the grid
        rows, cols = len(grid), len(grid[0])
        
        # Queue for BFS and a set to track visited cells
        q = deque()
        visited = set()

        # Helper function to add a room (cell) to the queue and mark it as visited
        def addRoom(r, c):
            # Check if the cell is out of bounds, already visited, or blocked (-1)
            if (r < 0 or r == rows or c < 0 or c == cols or 
                (r, c) in visited or grid[r][c] == -1):
                return
            # Mark the cell as visited and add it to the BFS queue
            visited.add((r, c))
            q.append([r, c])

        # Initialize the queue with all cells containing a 0 (starting points)
        for i in range(rows):
            for j in range(cols):
                if grid[i][j] == 0:
                    q.append([i, j])  # Add cell with a treasure (0) to the queue
                    visited.add((i, j))  # Mark it as visited

        # BFS variable to track the current distance from the treasure (0)
        dist = 0
        
        # Perform Breadth-First Search (BFS)
        while q:
            # Process all cells at the current distance level
            for i in range(len(q)):
                r, c = q.popleft()  # Get the next cell from the queue
                grid[r][c] = dist   # Set the current cell to the distance from a treasure

                # Add the adjacent cells (up, down, left, right) to the queue for further exploration
                addRoom(r + 1, c)  # Down
                addRoom(r - 1, c)  # Up
                addRoom(r, c + 1)  # Right
                addRoom(r, c - 1)  # Left
            
            # Increment the distance for the next layer of BFS
            dist += 1

""" Problem: Rotting Oranges:
    You are given a 2-D matrix grid. Each cell can have one of three possible values:

0 representing an empty cell
1 representing a fresh fruit
2 representing a rotten fruit
Every minute, if a fresh fruit is horizontally or vertically adjacent to a rotten fruit, then 
the fresh fruit also becomes rotten.

Return the minimum number of minutes that must elapse until there are zero fresh fruits remaining. 
If this state is impossible within the grid, return -1.

Algorithm:
    Initialization:
        - We go through the grid to count how many fresh oranges (1) there are and collect the positions of 
                all the rotten oranges (2). The rotten ones are stored in a queue because they are the starting 
                points for spreading the rot.
    BFS to Spread Rot:
        - Using the queue, we process each rotten orange, spreading rot to its neighboring fresh oranges 
            (up, down, left, right). Whenever a fresh orange turns rotten, we reduce the fresh orange count 
            and add its position to the queue to be processed next.
    Time Tracking:
        - After processing all rotten oranges for one minute, we increase the minute counter. 
            This continues until no more fresh oranges are left, or it's impossible to rot all oranges.
    Final Check:
        - If all fresh oranges have rotted, we return the number of minutes it took. If some fresh oranges remain, 
            meaning they can't be reached by any rotten ones, we return -1.
    
BFS v. DFS:

    - DFS (Depth-First Search) wouldn't work well for this problem because it explores one path deeply before 
        returning and might not spread the rot evenly in all directions at the same time. This is a problem because 
        the rot spreads to all nearby fresh oranges simultaneously in all directions every minute.

    - BFS (Breadth-First Search) works better because it processes all rotten oranges level by level, spreading rot 
        evenly across the grid, just like how the rot would spread in real life, minute by minute. DFS would result 
        in an inefficient spread and could miss updating oranges correctly.
"""
class Solution:
    def orangesRotting(self, grid: List[List[int]]) -> int:
        # Determine the number of rows (ROWS) and columns (COLS) in the grid
        ROWS, COLS = len(grid), len(grid[0])
        
        # Initialize a queue to store the positions of rotten oranges
        q = deque()
        
        # Variables to track the number of fresh oranges and the time (in minutes)
        fresh, minute = 0, 0

        # First pass through the grid to count fresh oranges and collect rotten orange positions
        for i in range(ROWS):
            for j in range(COLS):
                if grid[i][j] == 1:  # Fresh orange
                    fresh += 1  # Count fresh oranges
                if grid[i][j] == 2:  # Rotten orange
                    q.append((i, j))  # Add the rotten orange position to the queue

        # Define the four possible directions for adjacent cells (up, down, left, right)
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

        # Continue the BFS while there are rotten oranges in the queue and fresh oranges remaining
        while q and fresh > 0:
            # Process all rotten oranges at the current time step (minute)
            for i in range(len(q)):
                row, col = q.popleft()  # Get the current rotten orange position

                # Try to infect the adjacent cells (up, down, left, right)
                for dr, dc in directions:
                    new_row, new_col = dr + row, dc + col  # Calculate new position

                    # Check if the new position is out of bounds or doesn't contain a fresh orange
                    if (new_row < 0 or new_row == ROWS or new_col < 0 or new_col == COLS
                        or grid[new_row][new_col] != 1):
                        continue  # Skip invalid or non-fresh cells

                    # Infect the fresh orange by marking it as rotten (2)
                    grid[new_row][new_col] = 2
                    
                    # Add the newly rotten orange to the queue to process in the next time step
                    q.append((new_row, new_col))
                    
                    # Decrease the count of fresh oranges since one has rotted
                    fresh -= 1

            # Increment the time (minute) after processing all rotten oranges at the current level
            minute += 1
        
        # If no fresh oranges are left, return the number of minutes; otherwise, return -1 (not all can rot)
        return minute if fresh == 0 else -1