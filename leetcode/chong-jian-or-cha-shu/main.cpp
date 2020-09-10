/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
#include<iostream>
#include<vector>
using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
    TreeNode* buildTree(vector<int> &preorder, int pl, int pr,vector<int> &inorder, int il, int ir){
        if(pl>pr)
            return NULL;
        if(pl==pr)
            return new TreeNode(preorder[pl]);
        TreeNode *tree = NULL;
        for(int i=il; i<=ir; ++i){
            if(inorder[i]==preorder[pl])
            {
                tree = new TreeNode(inorder[i]);
                tree->left = buildTree(preorder, pl+1,pl+i-il,inorder, il, i-1);
                tree->right = buildTree(preorder, pl+i-il+1, pr, inorder, i+1,ir);
                break;
            }
        }
        return tree;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return buildTree(preorder,0,preorder.size()-1,inorder,0,inorder.size()-1);
    }
};

int main(){
    vector<int> arr1{3,9,20,15,7}, arr2{9,3,15,20,7};
    Solution solution;
    TreeNode *tree = solution.buildTree(arr1,arr2);
    cout<<tree->left->val;
}