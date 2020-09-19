#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
class Solution {
    vector<vector<int>> ans;

    void permuteUnique(vector<int> nums, int index,vector<int> &perm){
        sort(nums.begin()+index, nums.end());
        if(index==nums.size())
        {
            ans.push_back(perm);
            return;
        }
        
        for(int i=index;i<nums.size();++i){
            if(i<nums.size()-1&&nums[i+1]==nums[i])
                continue;
            swap(nums[index], nums[i]);
            perm.push_back(nums[index]);
            permuteUnique(nums,index+1, perm);
            
            perm.erase(perm.end()-1);
            swap(nums[index], nums[i]);
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> perm;
        permuteUnique(nums, 0, perm);
        return ans;
    }
};

int main(){
    Solution solution;
    vector<int> nums {3,5,6,7,9,1,3};
    vector<vector<int>> res =solution.permuteUnique(nums);
    printf("%d\n", res.size());
    return 0;
}