#include<iostream>
#include<deque>
#include<vector>
using namespace std;

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if(k==0) return {};

        deque<int> window;
        vector<int> res;

        for(int i=0;i<nums.size();++i){
            if(!window.empty()&&i>=window.front()+k){
                window.pop_front();
            }

            while(!window.empty()&&nums[i]>nums[window.back()])
            {
                window.pop_back();
            }

            window.push_back(i);
            if(i>=k-1)
                res.push_back(nums[window.front()]);
        }
        return res;
    }
};

int main(){
    Solution solution;
    vector<int> nums{1,3,5,6,2,1,5,3};
    cout<<solution.maxSlidingWindow(nums,2).size();
    return 0;
}