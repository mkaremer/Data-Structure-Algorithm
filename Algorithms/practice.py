from collections import defaultdict, deque

def topSort(vertices, edges):
    graph = defaultdict(list)
    in_degree = {}
    q = deque()
    res = []

    for i in range(vertices):
        in_degree[i] = 0
    
    for u, v in edges:
        graph[u].append(v)
        in_degree[v] += 1
    
    for k in in_degree:
        if in_degree[k] == 0:
            q.append(k)
    
    while q:
        vertex = q.popleft()
        res.append(vertex)

        for neighbor in graph[vertex]:
            in_degree[neighbor] -= 1
            if in_degree[neighbor] == 0:
                q.append(neighbor)
    
    return res