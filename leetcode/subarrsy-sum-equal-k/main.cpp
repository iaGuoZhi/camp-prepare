#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;


class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> mp;
        mp[0]=1;
        int pre=0,ans=0;
        for(auto num:nums){
            pre+=num;
            if(mp.count(pre-k))
                ans+=mp[pre-k];
            mp[pre]++;
        }
        return ans;
    }
};

int main(){
    vector<int> nums{-1,1,-1,1};
    Solution solu;
    cout<<solu.subarraySum(nums,0);
    return 0;
}