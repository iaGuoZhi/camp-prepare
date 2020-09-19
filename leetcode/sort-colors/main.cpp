#include<iostream>
#include<numeric>
#include<vector>
using namespace std;


class Solution {
public:
    void sortColors(vector<int>& nums) {
        int p0=0;
        int p2= nums.size()-1,p1=p2;

        int val=nums[p0];

        while(p1>=p0){
            while(p2>p0&&nums[p2]==2)
                p2--;
            while(p1>=p0&&nums[p1]>0){
                if(nums[p1]==2&&p1<p2){
                    swap(nums[p1],nums[p2]);
                    while(p2>p0&&nums[p2]==2)
                        p2--;
                }
                p1--;
            }
            if(p1>p0)
                swap(nums[p0], nums[p1]);
            while(p1>=p0&&nums[p0]==0)
                p0++;
            if(p1>p0)
                swap(nums[p0], nums[p1]);

        }
    }
};

int main(){
    Solution solu;
    vector<int> colors{1,2,0,0,0,1};
    solu.sortColors(colors);
    return 0;
}