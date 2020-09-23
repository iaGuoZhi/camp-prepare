#include<iostream>
#include<vector>
using namespace std;


class Solution{
public:
    void sift_down(vector<int> &nums, int pos,int size){
        int left= pos*2+1, right=pos*2+2;
        int next=pos;
        if(left<size&&nums[left]>nums[next]){
            next=left;
        }
        if(right<size&&nums[right]>nums[next]){
            next=right;
        }
        if(next!=pos){
            swap(nums[next], nums[pos]);
            sift_down(nums, next, size);
        }
    }

    void build_heap(vector<int> &nums){
        int size=nums.size();
        while(size){
            for(int i=size/2;i<size;++i){
                sift_down(nums, i, nums.size());
            }
            size/=2;
        }
    }

    void heap_sort(vector<int> &nums){
        build_heap(nums);
        int end=nums.size()-1;
        while(end){
            swap(nums[0], nums[end]);
            sift_down(nums, 0, end);
            end--;
        }
    }
};

void traverse(vector<int> nums){
    for(auto num: nums){
        cout<<num<<" ";
    }
    cout<<endl;
}

int main(){
    vector<int> nums{4,2,6,1,7,12,73,8,1,6,10,-2,-45};
    traverse(nums);
    Solution solu;
    solu.heap_sort(nums);
    traverse(nums);
}