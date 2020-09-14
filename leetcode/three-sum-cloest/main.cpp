#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        if(nums.size()<3)
            return 0;

        int ans=nums[0]+nums[1]+nums[2];

        for(int i=0;i<nums.size()-2;++i){
            int j=i+1, k=nums.size()-1;
            while(j<k){
                if(abs(nums[i]+nums[j]+nums[k]-target)<abs(ans-target))
                    ans=nums[i]+nums[j]+nums[k];
                
                if(nums[i]+nums[j]+nums[k]>target)
                    k--;
                else j++;
            }
        }
        return ans;
    }
};

int main(){
    vector<int> nums{3,5,6,7,3,1,5,3,2,1};
    Solution solu;
    cout<<solu.threeSumClosest(nums, 42);
    return 0;
}