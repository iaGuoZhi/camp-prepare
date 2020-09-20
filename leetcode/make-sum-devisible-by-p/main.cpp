#include<iostream>
#include<map>
#include<vector>
#include<limits.h>
using namespace std;

class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        long sum=0,mod=0;
        for(auto &num:nums)
        {
            mod=(mod+num)%p;
            sum+=p;
        }
        if(mod==0)
            return 0;
        if(sum<=p)
            return -1;

        map<long,int> table;
        table[0]=-1;
        long base=0;
        int minLen=INT_MAX;
        for(int i=0;i<nums.size();++i){
            base=(base+nums[i])%p;
            table[base]=i;
            if(table.count((base-mod+p)%p)){
                minLen=min(i-table[(base-mod+p)%p],minLen);
            }
        }
        if(minLen>=nums.size())
            return -1;
        return minLen;
    }
};

int main(){
    Solution solu;
    vector<int> nums{9,42,153,23,13,63,32,62};
    cout<<solu.minSubarray(nums, 8);
    return 0;
}