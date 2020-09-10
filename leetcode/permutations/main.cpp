#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
    vector<vector<int>> permute(vector<int> &nums, int index)
    {
        vector<vector<int>> arrays;
        if(index == nums.size()-1)
        {
            vector<int> array1{nums[index]};
            arrays.push_back(array1);
            return arrays;
        }
        if(index == nums.size())
            return arrays;
        for(int i=index;i<nums.size();++i)
        {
            swap(nums[index],nums[i]);
            vector<vector<int>> array1 = permute(nums, index+1);
            for(int i=0;i<array1.size();++i)
            {
                array1[i].insert(array1[i].begin(), nums[index]);
                arrays.push_back(array1[i]);
            }
            swap(nums[index],nums[i]);
        }
        return arrays;
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        return permute(nums,0);
    }
};

int main(){
    Solution solution;
    vector<int> nums {3,5,6,7,9,1};
    vector<vector<int>> res =solution.permute(nums);
    printf("%d\n", res.size());
    return 0;
}