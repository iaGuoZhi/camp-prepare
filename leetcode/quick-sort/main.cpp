#include<iostream>
#include<vector>

using namespace std;

class Solution {

    void quickSortInner(vector<int> &nums, int begin, int end){
        if(begin>=end)
            return;
        
        int value=nums[begin];

        int head=begin, tail=end;
        
        while(head<tail){
            while(head<tail&&nums[tail]>=value){
                tail--;
            }

            if(head<tail&&nums[tail]<value){
                nums[head]=nums[tail];
            }

            while(head<tail&&nums[head]<=value){
                head++;
            }

            if(head<tail&&nums[head]>value)
            {
                nums[tail]=nums[head];
            }
        }

        nums[head] = value;

        quickSortInner(nums, begin, head-1);
        quickSortInner(nums, head+1, end);
    }
public:
    void quickSort(vector<int> &nums){
        quickSortInner(nums, 0 , nums.size()-1);
    }
};

void traverse(vector<int> nums){
    for(auto num: nums)
        printf("  %d", num);
    
    printf("\n");
}


int main(){
    vector<int> nums{4,3,5,2,1,5,7,8,5,4};
    Solution solu;
    traverse(nums);
    solu.quickSort(nums);
    traverse(nums);
    return 0;
}

