from collections import deque

# BFS in a tree
def bfsTree(root):
    if not root:
        return
    
    q = deque([root])

    while q:
        node = q.popleft()
        print(node.val, end = " ")

        if node.left:
            q.append(node.left)
        
        if node.right:
            q.append(node.right)

# Level by level traversal of a tree

def level_order_traversal(root):
    if not root:
        return []
    
    res = []
    q = deque([root])

    while q:
        level_size = len(q)
        level_nodes = []

        for _ in range(level_size):
            node = q.popleft()
            level_nodes.append(node.value)

            if node.left:
                q.append(node.left)
            if node.right:
                q.append(node.right)
        res.append(level_nodes)
    
    return res

graph = {
    'A': ['B', 'C'],
    'B': ['A', 'D', 'E'],
    'C': ['A', 'F'],
    'D': ['B'],
    'E': ['B', 'F'],
    'F': ['C', 'E']
}

