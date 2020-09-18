#include<iostream>
#include<vector>
#include<map>

using namespace std;


class Solution {
    vector<pair<int,int>> heap;

    void siplify(int index){
        int left=index*2+1;
        int right=index*2+2;
        int next =index;

        if(left<heap.size()&&heap[left].second<heap[next].second)
            next=left;
        if(right<heap.size()&&heap[right].second<heap[next].second)
            next=right;

        if(next==index)
            return;
        swap(heap[next],heap[index]);
        siplify(next);
    }
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        map<int,int> table;
        for(auto num:nums)
            table[num]++;

        for(auto &[num,time]: table){
            if(heap.size()<k){
                int index=heap.size();
                heap.push_back(pair<int,int>{num,time});   
                while(index>0)
                {
                    siplify((index-1)/2);
                    index=(index-1)/2;
                }
            }
            else{
                if(time>heap[0].second){
                    heap[0]=pair<int,int>{num, time};
                    siplify(0);
                }
            }
        }

        vector<int> ans;
        for(auto &[num, time]: heap)
            ans.push_back(num);
        return ans;
    }
};

int main(){
    Solution solu;
    vector<int> nums{3,5,6,3,2,1,5,2,4,6,0};
    cout<<solu.topKFrequent(nums, 4);
    return 0;
}