#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& requests) {
        vector<long> table(nums.size(),0);
        for(auto &req:requests)
        {
            table[req[0]]++;
            if(req[1]+1<nums.size())
            table[req[1]+1]--;
        }

        for(int i=1;i<table.size();++i){
            table[i]+=table[i-1];
        }

        sort(nums.rbegin(),nums.rend());
        sort(table.rbegin(), table.rend());
        
        long ans=0;
        long mod=1e9+7;
        for(int i=0;i<table.size();++i){
            ans=(ans+nums[i]*table[i])%(mod);
        }
        return ans;
    }
};

int main(){
    return 0;
}