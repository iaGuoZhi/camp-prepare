#include<iostream>
#include<vector>
using namespace std;


class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> left(nums.size(), 0);
        left[0]=1;
        int prev=1;

        for(int i=1;i<nums.size();++i){
            left[i]=left[i-1]*nums[i-1];
        }
        
        for(int i=1;i<nums.size();++i)
        {
            prev*=nums[nums.size()-i];
            left[nums.size()-i-1]*=prev;
        }

        return left;
    }
};

int main(){
    return 0;
}