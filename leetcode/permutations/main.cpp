#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
    vector<vector<int>> ans;

    void permute(vector<int> &nums, int index, vector<int> &perm){
        if(index==nums.size())
            ans.push_back(perm);
        for(int i=index;i<nums.size();++i){
            swap(nums[i], nums[index]);
            perm.push_back(nums[index]);
            permute(nums, index+1, perm);
            swap(nums[i], nums[index]);
            perm.erase(perm.end()-1);
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> perm;
        permute(nums, 0, perm);
        return ans;
    }
};class Solution {
    vector<vector<int>> ans;

    void permute(vector<int> &nums, int index, vector<int> &perm){
        if(index==nums.size())
            ans.push_back(perm);
        for(int i=index;i<nums.size();++i){
            swap(nums[i], nums[index]);
            perm.push_back(nums[index]);
            permute(nums, index+1, perm);
            swap(nums[i], nums[index]);
            perm.erase(perm.end()-1);
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> perm;
        permute(nums, 0, perm);
        return ans;
    }
};

int main(){
    Solution solution;
    vector<int> nums {3,5,6,7,9,1};
    vector<vector<int>> res =solution.permute(nums);
    printf("%d\n", res.size());
    return 0;
}