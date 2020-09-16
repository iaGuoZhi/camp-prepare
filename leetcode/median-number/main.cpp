#include<iostream>
#include<vector>
using namespace std;

class Solution{
public:
    int medianNUmber(vector<int> nums){
        int index =-1, mid= nums.size()/2;
        int begin=0, end=nums.size()-1;
        while(index!=mid){
            if(index<mid)
                begin=index+1;
            else end=index-1;
            index= partition(nums, begin, end);
        }

        return nums[index];
    }

    int partition(vector<int> &nums, int begin , int end){
        int num=nums[begin];

        while(begin<end){
            while(begin<end&&nums[end]>num) end--;
            if(begin<end)
                nums[begin]=nums[end];
            while(begin<end&&nums[begin]<num) begin++;
            if(begin<end)
                nums[end]=nums[begin];
        }
        
        nums[begin]=num;
        return begin;
    }
};

int main(){
    vector<int> nums{3,4,6,2,1};
    Solution solu;
    cout<<solu.medianNUmber(nums);
    return 0;
}