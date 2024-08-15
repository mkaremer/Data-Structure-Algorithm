/*
        Three cases:
    1. Node with No children: simply remove the node from the tree
    2. Node with one child: remove node and replace it with its child
    3. node with 2 children: find in-order successor, the smallest node in right subtree to replace 
        the node's value and then delete the successor.
*/

// Function to find the minimum value node in a tree
TreeNode* minValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Function to delete a value from the binary search tree
TreeNode* deleteNode(TreeNode* root, int value) {
    if (root == NULL) {
        return root;
    }

    // If the value to be deleted is smaller than the root's value, it lies in the left subtree
    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    }
    // If the value to be deleted is greater than the root's value, it lies in the right subtree
    else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    }
    // If the value is the same as the root's value, this is the node to be deleted
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the in-order successor (smallest in the right subtree)
        TreeNode* temp = minValueNode(root->right);

        // Copy the in-order successor's content to this node
        root->data = temp->data;

        // Delete the in-order successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}