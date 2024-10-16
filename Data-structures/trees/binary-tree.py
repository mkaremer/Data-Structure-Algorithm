class TreeNode:
    def __init__(self, data):
        self.data = data  # Data part of the node
        self.left = None  # Pointer to the left child
        self.right = None  # Pointer to the right child

def create_node(data):
    return TreeNode(data)  # Create and return a new tree node

def insert(root, data):
    if root is None:  # If the tree is empty, create a new node
        return create_node(data)

    if data < root.data:  # If data is less, insert in the left subtree
        root.left = insert(root.left, data)
    else:  # If data is greater or equal, insert in the right subtree
        root.right = insert(root.right, data)

    return root

def inorder_traversal(root):
    if root is not None:
        inorder_traversal(root.left)  # Traverse left subtree
        print(root.data, end=" ")  # Visit the root
        inorder_traversal(root.right)  # Traverse right subtree

def main():
    # Create the root of the tree
    root = None
    
    # Insert nodes into the tree
    elements = [50, 30, 20, 40, 70, 60, 80]
    
    for elem in elements:
        root = insert(root, elem)

    # Print the inorder traversal of the tree
    print("Inorder traversal of the binary tree:")
    inorder_traversal(root)
    print()  # Print a newline for better readability

def get_path_from_root(root, val):
    def dfs(root, val, path):
        if root is None:
            return False
        else:
            path.append(root)
            if root.val == val or dfs(root.left, val, path) or dfs(root.right, val, path):
                return True
            path.pop()
            return False
    path = []
    dfs(root, val, path)

    return path
        
def get_root_to_leaf_paths(root):
    def dfs(root, path, paths):
        if root is None:
            return
        else:
            path.append(root)
            if root.left is None and root.right is None:
                paths.append(path.copy())
            dfs(root.left, path, paths)
            dfs(root.right, path, paths)
            path.pop()
    path = []
    paths = []
    dfs(root, path, paths)

    return paths
if __name__ == "__main__":
    main()
