#include<iostream>
#include<vector>
using namespace std;


class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int n=nums.size();
        int bit_max=31;
        while(!(n>>bit_max)){
            bit_max-=1;
        }

        int x=0,y=0,ans=0;
        for(int bit=0;bit<=bit_max;++bit){
            x=0;
            y=0;
            for(int i=0;i<nums.size();++i)
            {
                if(nums[i]&(1<<bit))
                    x++;
                if(i&1<<bit)
                    y++;
            }
            if(x>y)
                ans|=(1<<bit);
        }
        return ans;
    }
};

int main(){
    vector<int> nums{1,2,4,3,3};
    Solution solution;
    cout<<solution.findDuplicate(nums)<<endl;
    return 0;
}