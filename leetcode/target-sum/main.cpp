#include<iostream>
#include<vector>
#include<numeric>
using namespace std;


class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int S) {
        int sum = accumulate(nums.begin(), nums.end(),0);

        if(sum<S||(sum+S)%2==1) 
            return 0;
        int capacity = (sum+S)/2;

        vector<vector<int>> dp(nums.size()+1, vector<int>(capacity+1,0));
        for(int i=0;i<nums.size();++i)
            dp[i][0]=1;

        for(int i=1;i<=nums.size();++i){
            for(int j=0;j<=capacity;++j){
                if(j>=nums[i-1])
                    dp[i][j]=dp[i-1][j]+dp[i-1][j-nums[i-1]];
                else 
                    dp[i][j]= dp[i-1][j];
            }
        }
        return dp[nums.size()][capacity];
    }
};


int main(){
    vector<int> nums{5,6,7,8,4,1,3,1,3,1,5,2,12};
    Solution solu;
    cout<<solu.findTargetSumWays(nums, 20);
    return 0;
}