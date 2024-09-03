def dfs(graph, start, visited= None):
    if visited is None:
        visited = set()

    visited.add(start)
    print(start)

    for nei in graph[start]:
        if nei not in visited:
            dfs(graph, nei, visited)