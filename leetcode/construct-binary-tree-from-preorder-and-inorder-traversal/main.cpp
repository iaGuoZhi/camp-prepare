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
    TreeNode *buildTree(vector<int>&preorder, int prebegin, int prend,vector<int> &inorder, int inbegin, int inend)
    {
        if(prebegin>prend)
            return NULL;

        TreeNode *node = new TreeNode(preorder[prebegin]);
        if(prebegin==prend)
            return node;
        
        for(int i=inbegin;i<=inend;++i){
            if(preorder[prebegin]==inorder[i]){
                node->left=buildTree(preorder, prebegin+1, prebegin+i-inbegin, inorder, inbegin, i-1);
                node->right=buildTree(preorder, prebegin+i-inbegin+1, prend, inorder, i+1, inend);
                return node;
            }
        }
        return node;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return buildTree(preorder, 0, preorder.size()-1,inorder, 0, inorder.size()-1);
    }
};

