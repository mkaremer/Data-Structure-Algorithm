//get the path from the roor to a node
bool dfs(TreeNode* root, int val, vector<TreeNode*> path){
    if(root == NULL){
        return false;
    }

    path.push_back(root);
    if(root->val == val || dfs(root->left, val, path) || dfs(root->right, val ,path)){
        return true;
    }
    path.pop_back();
    return false;
}

vector<TreeNode*> getPathFromRoot(TreeNode* root, int val){
    vector<TreeNode*> path;
    dfs(root, val, path);
    return path;
}