#include<iostream>
#include<vector>
using namespace std;


class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum=0;
        for(int num:nums)
            sum+=num;
        if(sum%2==1) return false;
        sum/=2;

        vector<bool> dp(sum+1,false);
        dp[0]=true;
        for(int j=1;j<=nums.size();++j){
            for(int i=sum;i>=nums[j-1];--i){
                dp[i]=dp[i-nums[j-1]] | dp[i];
            }
        }
        return dp[sum];
    }
};

int main(){
    Solution solu;
    vector<int> nums{4,5,6,3,1,7};

    cout<<solu.canPartition(nums);
    return 0;
}