from collections import deque

def level_tra(root):
    if root is None:
        return []

    q = deque([root])
    res = []

    while q:
        level_size = len(q)
        level_nodes = []

        for _ in range(level_size):
            node = q.popleft()
            level_nodes.appen(node.val)

            if node.left:
                q.append(node.left)
            
            if node.right:
                q.append(node.right)
        res.append(level_nodes)