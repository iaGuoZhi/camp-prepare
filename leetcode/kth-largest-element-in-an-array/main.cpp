#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
    void maxHeapSiplify(vector<int> &nums, int i, int heapSize)
    {
        int lchild= 2*i+1, rchild=2*i+2, replace=i;
        if(lchild<heapSize&&nums[lchild]>nums[replace]){
            replace=lchild;
        }
        if(rchild<heapSize&&nums[rchild]>nums[replace]){
            replace=rchild;
        }

        if(replace!=i){
            swap(nums[i], nums[replace]);
            maxHeapSiplify(nums, replace, heapSize);
        }
    }

    void buildMaxHeap(vector<int>&nums, int heapSize){
        for(int i=heapSize/2;i>=0;--i){
            maxHeapSiplify(nums, i, heapSize);
        }
    }


public:
    int findKthLargest(vector<int>& nums, int k) {
        buildMaxHeap(nums, nums.size());

        for(int i=0;i<k-1;++i){
            swap(nums[0], nums[nums.size()-i-1]);

            maxHeapSiplify(nums, 0, nums.size()-i-1);
        }
        return nums[0];    
    }
};

int main(){
    vector<int> nums{3,2,3,1,2,4,5,5,6};
    Solution solution;
    cout<<solution.findKthLargest(nums, 4);
    return 0;
}