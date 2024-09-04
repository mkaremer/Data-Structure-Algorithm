#include <stdio.h>
#include <stdlib.h>

// Define a node structure for the binary tree
typedef struct TreeNode{
    int data;                 
    struct TreeNode* left;      
    struct TreeNode* right;     
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
/*
        TRICKS TO SOLVE ALMOST ANY BINARY TREE CODING PROBLEM
        source: https://www.youtube.com/watch?v=s2Yyk3qdy3o&t=176s

        Recursive nature of a tree:
            - subtrees of trees are also trees
            - subtrees of subtrees are also trees
            - so the same function is called on all of them
            - this indicates recursive nature of binary trees
        THE 4 STEPS

        1. finding one or more base cases
        2. calling the same function on the left subtree
        3. calling the same function on the right subtree
        4. joining the results

        EXMPLE PROBLEMS
        1. Getting sum of elements of binary tree
        2. Getting the max value of the binary tree
        3. Getting the height of binary tree
        4. checking if an element exists in a binary tree
        5. reverse a binary tree
*/

/*
        FINDING SUME OF ELEMENTS OF BINARY TREE
    
    1. base case: If the current node is NULL, it means we've reached the end or the tree is empty, 
                so the function returns 0.
    2. Left subtree: The function calls itself to add up all the values in the left subtree.
    3. Right subtree: The function does the same for the right subtree.
    4. Final step: The function adds the current node’s value to the sums from the left and right 
            subtrees to get the total sum of the tree.
*/

int treeSum(TreeNode* root) {
    // Base case: If the current node is NULL (tree is empty or end of a branch), return 0
    if(root == NULL) {
        return 0;
    }

    // Recursively calculate the sum of all nodes in the left subtree
    int leftSum = treeSum(root->left);

    // Recursively calculate the sum of all nodes in the right subtree
    int rightSum = treeSum(root->right);

    // Return the sum of the current node's data, the sum of the left subtree, and the sum of the right subtree
    return root->data + leftSum + rightSum;
}

/*
        GETTING THE MAX VALUE OF BINARY TREE
    1. Base case:  If the root is NULL, return INT_MIN to ensure any value in the tree is larger.
    2. Recursive calls: leftMax and rightMax hold the maximum values from the left and right subtrees.
    3. Final Return: The function returns the largest value among the current node's data, leftMax, and rightMax.
*/

int maxValue(TreeNode* root) {
    if (root == NULL) {
        return INT_MIN;  // Return the smallest possible integer if the tree is empty
    }

    int leftMax = maxValue(root->left);
    int rightMax = maxValue(root->right);

    // Find the maximum value between leftMax, rightMax, and root->data
    return max(root->data, max(leftMax, rightMax));
}


/*
        GETTING THE HEIGHT OF A BINARY TREE
    Height of tree: this is the number of edges on the longest path from the root

    Explanation:
1. Base Case: If the node is NULL, return -1 (for height as edges) or 0 (for height as nodes).
2. Recursive Calls: The function calculates the height of the left and right subtrees.
3. Final Return: The height of the current node is 1 + the maximum height of its left and right subtrees.

Use return -1 if you want to calculate height as the number of edges.
Use return 0 if you want to calculate height as the number of nodes.

*/

int treeHeight(TreeNode* root){
    if(root == NULL){
        return -1;
    }

    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);

    return 1 + max(leftHeight, rightHeight);
}
// ITERATIVE DFS
class Solution {
public:
    int maxDepth(TreeNode* root) {
        stack<pair<TreeNode*, int>> stack;
        stack.push({root, 1});
        int res = 0;

        while (!stack.empty()) {
            pair<TreeNode*, int> current = stack.top();
            stack.pop();
            TreeNode* node = current.first;
            int depth = current.second;

            if (node != nullptr) {
                res = max(res, depth);
                stack.push({node->left, depth + 1});
                stack.push({node->right, depth + 1});
            }
        }
        return res;
    }
};

// BFS
class Solution {
public:
    int maxDepth(TreeNode* root) {
        queue<TreeNode*> q;
        if (root != nullptr) {
            q.push(root);
        }

        int level = 0;

        while (!q.empty()) {
            int size = q.size();

            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();
                if (node->left != nullptr) {
                    q.push(node->left);
                }
                if (node->right != nullptr) {
                    q.push(node->right);
                }
            }
            level++;
        }
        return level;
    }
};
/*
        CHECKING IF ELEMENT EXISTS IN A BINARY TREE
*/

bool exists(TreeNode* root, int data) {
    // First, check if the current node is NULL
    if (root == NULL) {
        return false;  // If the node is NULL, the value does not exist in this subtree
    }

    // Check if the current node's value matches the target data
    if (root->data == data) {
        return true;  // If the value is found, return true
    }

    // Recursively check the left subtree
    if (exists(root->left, data)) {
        return true;
    }

    // Recursively check the right subtree
    return exists(root->right, data);
}

/*
        REVERSE A TREE
*/

// Function to reverse (mirror) the binary tree
void reverseTree(TreeNode* root) {
    if (root == NULL) {
        return; // Base case: If the node is NULL, do nothing
    }

    // Recursively reverse the left and right subtrees
    reverseTree(root->left);
    reverseTree(root->right);

    // Swap the left and right children of the current node
    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
}

/*
        HOW TO SOLVE BINARY TREE PATH RELATED PROBLEMS
    - what is a path: a path is the sequence of nodes that we pass from to go from a node A to 
            a node B in the tree
    - To keep track of the path, we use an array where its first element is the root and the last element is the actual node
    - when we reach the node we add it to the array and when we backtrack we remove it.
    - We basically use DFS but we add an additional parameter array for the path
*/

void dfs(TreeNode* root, std::vector<TreeNode*>& path) {
    if (root == NULL) {
        return;
    } else {
        std::cout << root->val << std::endl;  // Print the value of the current node
        path.push_back(root);  // Add the current node to the path

        dfs(root->left, path);  // Recursively call dfs on the left child
        dfs(root->right, path);  // Recursively call dfs on the right child

        path.pop_back();  // Remove the current node from the path after exploring its children
    }
}

/*
    Example proble: get the path from the root to a particular node in the tree

    Algorithm:
    - Check if Node is Null: If the current node is NULL, return false because 
        there's nothing to search in this part of the tree.
    - Add Node to Path: Add the current node to the path because it might be part of the path to the target value.
    - Check for Value:
        - If the current node’s value matches the target value (val), return true.
        - Otherwise, recursively search in the left subtree and right subtree.
        - If the value is found in either subtree, return true.
    - Backtrack if Not Found:
        - If the value isn't found in the current node or its subtrees, remove the current node 
                from the path and return false.
    - Return the Path
*/
bool dfs(TreeNode* root, int val, std::vector<TreeNode*>& path) {
    if (root == NULL) {
        return false;
    }

    path.push_back(root);  // Add the current node to the path

    if (root->val == val || dfs(root->left, val, path) || dfs(root->right, val, path)) {
        return true;  // Return true if the value is found
    } else{
        path.pop_back();  // Remove the current node if it's not in the path to the value
        return false;
    }
}

std::vector<TreeNode*> getPathFromRoot(TreeNode* root, int val) {
    std::vector<TreeNode*> path;
    dfs(root, val, path);
    return path;
}

/*
    problem: Get the Kth Ancestor of a node
    Algorithm: 
        - Find the Path: Use getPathFromRoot to get the path from the root of the tree to the node with 
            the given value val. Store this path in a vector.
        - Check Validity of k: Determine the size of the path. If k is larger than the path size or 
                k is less than or equal to 0, return NULL because the kth ancestor doesn't exist.
        - Return the Ancestor: If k is valid, find the kth ancestor by indexing into the path 
            and return the corresponding node. The correct node is at position path_size - k - 1 in the path vector.
*/

TreeNode* kth_ancestor(TreeNode* root, int val, int k) {
    std::vector<TreeNode*> path;
    path = getPathFromRoot(root, val);
    int path_size = path.size();
    
    if (k >= path_size || k <= 0) {
        return NULL;  // Return NULL if k is out of bounds
    } else {
        return path[path_size - k - 1];  // Return the kth ancestor node
    }
}

/*
    Problem: Lowest Common Ancestor problem: 
*/
TreeNode* lca(TreeNode* root, int val1, int val2) {
    std::vector<TreeNode*> path1 = getPathFromRoot(root, val1);
    std::vector<TreeNode*> path2 = getPathFromRoot(root, val2);
    TreeNode* lastCommon = NULL;
    int i = 0;
    int j = 0;

    // Iterate through both paths to find the last common node
    while (i < path1.size() && j < path2.size()) {
        if (path1[i] == path2[j]) {
            lastCommon = path1[i];
            i++;
            j++;
        } else {
            break;
        }
    }
    return lastCommon;
}
/*
    Problem: lcs efficient solution
*/
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // Base case: if the root is null, return null
        if (root == NULL) {
            return NULL;
        }
        
        // If both p and q are less than root, then LCA lies in the left subtree
        if (p->val < root->val && q->val < root->val) {
            return lowestCommonAncestor(root->left, p, q);
        }
        
        // If both p and q are greater than root, then LCA lies in the right subtree
        if (p->val > root->val && q->val > root->val) {
            return lowestCommonAncestor(root->right, p, q);
        }
        
        // If p and q are on different sides or one is the root, then root is the LCA
        return root;
    }
};
/*
    Problem: Getting paths of leaf nodes
    Algorithms:
        - Check if the Node is Null: If the current node is NULL, exit the function.
        - Add Node to Path: Add the current node to the ongoing path.
        - Check for Leaf Node: If the current node has no left or right child (it's a leaf), 
            add the current path to the list of all paths.
        - Explore Subtrees: Recursively call the function to explore the left and right subtrees.
        - Backtrack: After exploring both subtrees, remove the current node from the path to backtrack 
            and continue searching for other paths.
        - Get All Paths: The getRootToLeafPaths function initializes the path and paths containers, 
            calls the DFS function, and returns all root-to-leaf paths.
*/
void dfs(TreeNode* root, std::vector<TreeNode*>& path, std::vector<std::vector<TreeNode*>>& paths) {
    if (root == NULL) {
        return;
    } else {
        path.push_back(root);  // Add the current node to the path

        if (root->left == NULL && root->right == NULL) {
            // If it's a leaf node, add the current path to paths
            paths.push_back(path);
        }

        // Recursively explore left and right subtrees
        dfs(root->left, path, paths);
        dfs(root->right, path, paths);

        path.pop_back();  // Remove the current node from the path when backtracking
    }
}

std::vector<std::vector<TreeNode*>> getRootToLeafPaths(TreeNode* root) {
    std::vector<TreeNode*> path;
    std::vector<std::vector<TreeNode*>> paths;
    dfs(root, path, paths);
    return paths;
}

/*
    Problem: Getting the path from a source node (not from the root) to a destination
*/
bool dfs(TreeNode* source, int val, std::vector<TreeNode*>& path) {
    if (source == NULL) {
        return false;
    }

    path.push_back(source);  // Add the current node to the path

    // Check if the current node is the destination or if the destination is found in the subtrees
    if (source->val == val || dfs(source->left, val, path) || dfs(source->right, val, path)) {
        return true;  // Return true if the value is found
    } else {
        path.pop_back();  // Remove the current node if it's not in the path to the value
        return false;
    }
}

std::vector<TreeNode*> getPathFromSource(TreeNode* source, int val) {
    std::vector<TreeNode*> path;
    dfs(source, val, path);
    return path;
}

/*
        Problem: Binary Tree diameter
The diameter of a binary tree is defined as the length of the longest path between any two nodes within the tree. 
The path does not necessarily have to pass through the root.

The length of a path between two nodes in a binary tree is the number of edges between the nodes.

Given the root of a binary tree root, return the diameter of the tree.
*/
class Solution {
public:
    // Function to calculate the diameter of a binary tree
    int diameterOfBinaryTree(TreeNode* root) {
        int res = 0;               // Initialize the result (diameter) to 0
        dfs(root, res);            // Perform DFS to calculate the diameter
        return res;                // Return the final diameter
    }
    
private:
    // Helper function to perform DFS and calculate the height of the tree
    int dfs(TreeNode* root, int& res) {
        if (root == NULL) {        // Base case: if the node is NULL, return 0
            return 0;
        }
        
        int left = dfs(root->left, res);   // Recursively calculate the height of the left subtree
        int right = dfs(root->right, res); // Recursively calculate the height of the right subtree

        res = max(res, left + right);      // Update the diameter if the current path is longer

        return 1 + max(left, right);       // Return the height of the current subtree
    }
};

/*
    Problem: check if BST is balanced:
    Given a binary tree, return true if it is height-balanced and false otherwise.

A height-balanced binary tree is defined as a binary tree in which the left and right subtrees 
    of every node differ in height by no more than 1.
*/

class Solution {
public:
    // Function to check if the binary tree is balanced
    bool isBalanced(TreeNode* root) {
        return dfs(root)[0] == 1;  // Call the dfs helper function and check if the tree is balanced
    }

private:
    // Helper function to perform DFS and determine if the subtree is balanced
    // Returns a vector: {is_balanced, height}
    vector<int> dfs(TreeNode* root) {
        if (!root) {  // Base case: if the node is NULL
            return {1, 0};  // A NULL node is balanced with a height of 0
        }

        vector<int> left = dfs(root->left);  // Recursively check the left subtree
        vector<int> right = dfs(root->right);  // Recursively check the right subtree

        // Check if the current node's subtree is balanced
        // It is balanced if both left and right subtrees are balanced and the height difference is <= 1
        bool balanced = left[0] == 1 && right[0] == 1 && abs(left[1] - right[1]) <= 1;

        // Calculate the height of the current node's subtree
        int height = 1 + max(left[1], right[1]);

        // Return whether the current subtree is balanced and its height
        return {balanced ? 1 : 0, height};
    }
};

// Helper function to check if the tree is balanced and to calculate its height
int checkHeight(struct TreeNode* root, bool* isBalanced) {
    if (root == NULL) {
        return 0;  // A NULL node has a height of 0
    }

    int leftHeight = checkHeight(root->left, isBalanced);  // Check the height of the left subtree
    int rightHeight = checkHeight(root->right, isBalanced);  // Check the height of the right subtree

    // If the height difference is more than 1, mark the tree as not balanced
    if (abs(leftHeight - rightHeight) > 1) {
        *isBalanced = false;
    }

    // Return the height of the current node's subtree
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Main function to check if the tree is height-balanced
bool isBalanced(struct TreeNode* root) {
    bool isBalancedTree = true;
    checkHeight(root, &isBalancedTree);
    return isBalancedTree;
}

/*
    Problem: isSameTree
    Given the roots of two binary trees p and q, return true if the trees are equivalent, otherwise return false.

    Two binary trees are considered equivalent if they share the exact same structure and the nodes have the same values.
*/

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // Base case: both nodes are NULL, the trees are identical at this point
        if (p == NULL && q == NULL) {
            return true;
        }

        // If one of the nodes is NULL and the other is not, the trees are not the same
        if (p == NULL || q == NULL) {
            return false;
        }

        // Check the current nodes' values and recursively check their left and right subtrees
        if (p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right)) {
            return true;
        }

        // If the values don't match or the subtrees don't match, the trees are not the same
        return false;
    }
};

/*
    Problem: Subtree of another tree
   Given the roots of two binary trees root and subRoot, return true if there is a subtree of root 
   with the same structure and node values of subRoot and false otherwise.

    A subtree of a binary tree tree is a tree that consists of a node in tree and all of this node's descendants. 
    The tree tree could also be considered as a subtree of itself. 
*/
class Solution {
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        // If subRoot is NULL, it is a subtree of any tree
        if (subRoot == NULL) {
            return true;
        }

        // If root is NULL but subRoot is not, subRoot cannot be a subtree
        if (root == NULL) {
            return false;
        }

        // Check if the trees are identical starting at this node
        if (isSameTree(root, subRoot)) {
            return true;
        }

        // Otherwise, check if subRoot is a subtree of either the left or right subtree
        return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
    }
};

/*
    Problem: Binary tree right side view
    You are given the root of a binary tree. Return only the values of the nodes that are visible from 
    the right side of the tree, ordered from top to bottom.

    Algorithm:
        - Start by putting the root node into a queue to process each level of the tree one by one.
        - For each level, determine the number of nodes at that level (this is the size of the queue).
        - As you process the nodes in the current level:
            - For the first node you encounter in each level, add its value to the result list (this will be the 
                rightmost node due to the order of processing).
            - Always add the right child to the queue first, followed by the left child, so that the rightmost node 
                is processed first in the next level.
        - Continue this process for all levels until the queue is empty.
*/
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if (root == nullptr) {
            return res;  // If the tree is empty, return an empty result
        }
        
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int size = q.size();

            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front();
                q.pop();

                // For each level, the first element we encounter from the right side
                if (i == 0) {
                    res.push_back(node->val);
                }

                // Push right child first to ensure it is processed first in the next level
                if (node->right != nullptr) {
                    q.push(node->right);
                }
                
                // Then push left child
                if (node->left != nullptr) {
                    q.push(node->left);
                }
            }
        }
        return res;
    }
};

/*
    Problem: Count Good Nodes in a tree
    Within a binary tree, a node x is considered good if the path from the root of the tree 
    to the node x contains no nodes with a value greater than the value of node x

    Given the root of a binary tree root, return the number of good nodes within the tree.

    How the Solution Works:
        - DFS Traversal: The dfs function moves through the tree starting from the root, carrying along 
                the highest value seen so far (maxValue).
        - Counting Good Nodes: A node is "good" if its value is greater than or equal to maxValue. 
                If it is, the count is increased.
        - Recursive Calls: The function updates maxValue and then checks the left and right subtrees.
*/
class Solution {
public:
    int goodNodes(TreeNode* root) {
        // Start DFS with the root node, initially the root's value is the maximum value
        return dfs(root, root->val);
    }

private:
    // Helper function to perform DFS and count good nodes
    int dfs(TreeNode* root, int maxValue){
        if(root == nullptr){
            return 0;  // Base case: if the node is NULL, return 0
        }

        // Check if the current node is a good node
        int count = (root->val >= maxValue) ? 1 : 0;

        // Update the maximum value seen so far
        maxValue = max(maxValue, root->val);

        // Continue DFS on the left and right subtrees, and add their good nodes count
        count += dfs(root->left, maxValue);
        count += dfs(root->right, maxValue);

        return count;  // Return the total count of good nodes
    }
};

/*
    Problem: Validate Binary search tree (BST)

How It Works:
DFS Traversal: The dfs function goes through the tree recursively, checking if each node’s 
    value is between a minimum (min) and maximum (max). Initially, 
    LONG_MIN and LONG_MAX are used to cover all values.

BST Conditions: If a node’s value is not between min and max, the function returns false. 
    Otherwise, it checks the left subtree (values must be less than the current node) and 
    the right subtree (values must be greater).

Base Case: If a node is NULL, the function returns true, meaning the subtree is valid.

TIME AND SPACE COMPLEXITY


Time Complexity:
Traversal of Every Node: The dfs function visits each node in the tree exactly once during the traversal. 
For each node, it performs constant-time operations like comparing values and making recursive calls.
Since every node is visited exactly once, the time complexity is O(n), where n is the number of nodes in the tree.

Space Complexity:
Recursive Call Stack: The space complexity depends on the depth of the recursive calls, 
which is related to the height of the tree.
In the worst case (if the tree is completely unbalanced, like a linked list), the height of the tree could be n, 
and the space complexity due to the recursion stack would be O(n).
In the best case (if the tree is balanced), the height of the tree is log(n), 
and the space complexity would be O(log n) due to the recursive call stack.

Thus, the overall space complexity is O(h), where h is the height of the tree, which is O(n) in the worst case and O(log n) in the best case.

*/
class Solution {
public:
    // Function to check if the binary tree is a valid BST
    bool isValidBST(TreeNode* root) {
        return dfs(root, LONG_MIN, LONG_MAX);  // Start DFS with the root and initial bounds
    }

private:
    // Helper function to perform DFS and check BST conditions
    bool dfs(TreeNode* root, long min, long max){
        if (root == nullptr) {
            return true;  // Base case: an empty tree is a valid BST
        }

        // If the current node's value is out of the allowed range, it's not a valid BST
        if (!(min < root->val && root->val < max)) {
            return false;
        }

        // Recursively check the left subtree with updated max value
        // Recursively check the right subtree with updated min value
        return dfs(root->left, min, root->val) && 
               dfs(root->right, root->val, max);
    }
};
