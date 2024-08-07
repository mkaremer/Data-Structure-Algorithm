#include <stdio.h>
#include <stdlib.h>

// Define a node structure for the binary tree
typedef struct TreeNode {
    int data;                   // Data part of the node
    struct TreeNode* left;      // Pointer to the left child
    struct TreeNode* right;     // Pointer to the right child
} TreeNode;

// Function to create a new tree node
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the binary tree
TreeNode* insert(TreeNode* root, int data) {
    if (root == NULL) {  // If the tree is empty, create a new node
        return createNode(data);
    }

    if (data < root->data) {  // If data is less, insert in the left subtree
        root->left = insert(root->left, data);
    } else {  // If data is greater or equal, insert in the right subtree
        root->right = insert(root->right, data);
    }

    return root;
}

// Function to find the node with the minimum value
TreeNode* minValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Function to search for a node in the binary tree
TreeNode* search(TreeNode* root, int data) {
    if (root == NULL || root->data == data)
        return root;

    if (data < root->data)
        return search(root->left, data);

    return search(root->right, data);
}

// Function for in-order traversal of the binary tree
void inOrderTraversal(TreeNode* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);  // Visit left subtree
        printf("%d ", root->data);     // Visit root
        inOrderTraversal(root->right); // Visit right subtree
    }
}

// Function for pre-order traversal of the binary tree
void preOrderTraversal(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);     // Visit root
        preOrderTraversal(root->left);  // Visit left subtree
        preOrderTraversal(root->right); // Visit right subtree
    }
}

// Function for post-order traversal of the binary tree
void postOrderTraversal(TreeNode* root) {
    if (root != NULL) {
        postOrderTraversal(root->left);  // Visit left subtree
        postOrderTraversal(root->right); // Visit right subtree
        printf("%d ", root->data);       // Visit root
    }
}

// Function to free the binary tree
void freeTree(TreeNode* root) {
    if (root != NULL) {
        freeTree(root->left);   // Free left subtree
        freeTree(root->right);  // Free right subtree
        free(root);             // Free root
    }
}

// Main function to test the binary tree implementation
int main() {
    TreeNode* root = NULL;

    // Insert elements into the binary tree
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    // Perform in-order traversal
    printf("In-order traversal: ");
    inOrderTraversal(root);
    printf("\n");

    // Perform pre-order traversal
    printf("Pre-order traversal: ");
    preOrderTraversal(root);
    printf("\n");

    // Perform post-order traversal
    printf("Post-order traversal: ");
    postOrderTraversal(root);
    printf("\n");

    // Free the binary tree
    freeTree(root);

    return EXIT_SUCCESS;
}
