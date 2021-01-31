#include <bits/stdc++.h>

/*
 * Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
 */

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

ostream& operator<<(ostream& c, deque<TreeNode*>& queue) {
    deque<TreeNode*> q(queue);
    while (!q.empty()) {
        c << " -> " << q.front()->val;
        q.pop_front();
    }
    c << std::endl;
    return c;
}

bool dfs(TreeNode* node, TreeNode* target, deque<TreeNode*>& parents) {
    if (node == NULL) {
        return false;
    }
    if (node == target) {
        //note this
        parents.push_front(node);
        return true;
    }
    bool foundLeft = dfs(node->left, target, parents);
    bool foundRight = dfs(node->right, target, parents);
    if (foundLeft) {
        //push parent and signal we found it
        parents.push_front(node);
        return true;
    } else if (foundRight) {
        //push parent and signal we found it.
        parents.push_front(node);
        return true;
    } else {
        //we neither found it in left or right tree
        //this works only because vals are unique
        return false;
    }
}
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    //recursively dfs and maintain a stack using implicit frames once you reach the node
    deque<TreeNode*> firstAncestry, secondAncestry;

    dfs(root, p, firstAncestry);
    dfs(root, q, secondAncestry);

    //do this for the second node..handle null
    std::cout << "First : " << firstAncestry << std::endl;
    std::cout << "Second: " << secondAncestry << std::endl;

    //trim both ancestry
    int firstSize = firstAncestry.size();
    int secondSize = secondAncestry.size();

    while (firstSize > secondSize) {
        firstAncestry.pop_back();
        firstSize = firstSize - 1;
    }
    while (secondSize > firstSize) {
        secondAncestry.pop_back();
        secondSize = secondSize - 1;
    }
    //do this for the second node..handle null
    std::cout << "Trimmed First : " << firstAncestry << std::endl;
    std::cout << "Trimmed Second: " << secondAncestry << std::endl;
    //both ancestries are trimmed..loop until empty
    while (firstSize != 0) {
        if (firstAncestry.back() == secondAncestry.back()) {
            return firstAncestry.back();
        }
        firstSize = firstSize - 1;
        firstAncestry.pop_back();
        secondAncestry.pop_back();
    }
    return NULL;
    //trim both from the end
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);

    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(5);
    root->left->left = new TreeNode(6);
    root->left->right = new TreeNode(2);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);

    root->right = new TreeNode(1);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);

    std::cout << lowestCommonAncestor(root, root->left->right->left, root->right->right)->val << std::endl;
    std::cout << lowestCommonAncestor(root, root->left->right->left, root->left)->val << std::endl;
    std::cout << lowestCommonAncestor(root, root->left->right->left, root)->val << std::endl;
    std::cout << lowestCommonAncestor(root, root->left->right->left, root->left->right->right)->val << std::endl;
    return 0;
}
