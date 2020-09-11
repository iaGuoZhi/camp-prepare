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
    void traverse(TreeNode *root, vector<vector<int>> &res, int level){
        if(root==NULL) return;
        while(res.size()<=level){
            res.push_back(vector<int>{});
        }

        res[level].push_back(root->val);
        traverse(root->left, res, level+1);
        traverse(root->right, res, level+1);
    }
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        traverse(root, res, 0);
        return res;
    }
};


int main(){
    Solution solution;

    TreeNode *tree = new TreeNode(10);

    auto result = solution.levelOrder(tree);
    cout<<result.size();
}