#include<iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
    TreeNode *flatten2(TreeNode *root){
        if(root==NULL)
            return NULL;
        
        TreeNode *left = root->left;
        TreeNode *right = root->right;

        if(left==NULL&&right==NULL)
            return root;
        
        if(left==NULL)
            return flatten2(root->right);

        if(right==NULL){
            root->right=left;
            root->left=NULL;
            return flatten2(root->right);
        }

        root->right=left; 
        root->left=NULL;
        TreeNode *node=flatten2(left);
        node->right=right;
        return flatten2(right);
    }
public:
    void flatten(TreeNode* root) {
        flatten2(root);
    }
};

int main(){
    Solution solu;
    return 0;
}