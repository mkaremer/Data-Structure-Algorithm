# top sort
from collections import defaultdict, deque

def topSort(vertices, edges):
    #init the graph
    graph = defaultdict(list)

    in_degree = {}
    for i in range(vertices):
        in_degree[i] = 0
    
    for u, v in edges:
        graph[u].append(v)
        in_degree[v] += 1
    
    q = deque()
    for k in in_degree:
        if in_degree[k] == 0:
            q.append(k)
    top_order = []
    while q:
        node = q.popleft()
        top_order.append(node)

        for nei in graph[node]:
            in_degree[nei] -= 1

            if in_degree[nei] == 0:
                q.append(nei)

    if len(top_order) == vertices:
        return True
    
    return False