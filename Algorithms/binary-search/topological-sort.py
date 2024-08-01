from collections import defaultdict, deque

def topological_sort(vertices, edges):
    # Initialize the graph
    in_degree = {}
    for i in range(vertices):
        in_degree[i] = 0
    
    graph = defaultdict(list)
    
    # Build the graph and compute in-degrees
    for u, v in edges:
        graph[u].append(v)
        in_degree[v] += 1

    # Find all sources (vertices with 0 in-degrees)
    queue = deque()
    for k in in_degree:
        if in_degree[k] == 0:
            queue.append(k)
    
    topological_order = []
    
    # Process the sources
    while queue:
        vertex = queue.popleft()
        topological_order.append(vertex)
        
        # Reduce in-degree for all neighboring vertices
        for neighbor in graph[vertex]:
            in_degree[neighbor] -= 1
            # If in-degree becomes 0, add it to the queue
            if in_degree[neighbor] == 0:
                queue.append(neighbor)
    
    # Check if topological sort includes all vertices
    if len(topological_order) == vertices:
        return topological_order
    else:
        return "The graph has a cycle."

# Example usage:
vertices = 6
edges = [
    (5, 2),
    (5, 0),
    (4, 0),
    (4, 1),
    (2, 3),
    (3, 1)
]

print("Topological Sort:", topological_sort(vertices, edges))
