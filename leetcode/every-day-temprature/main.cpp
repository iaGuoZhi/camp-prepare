#include<iostream>
#include<vector>
#include<stack>
using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        stack<int> st;
        vector<int> ans(T.size(),0);
        for(int i=0;i<T.size();++i){
            while(!st.empty()&&T[st.top()]<T[i]){
                int index= st.top();
                ans[index] =i-index;
                st.pop();
            }
            st.push(i);
        }
        return ans;
    }
};

int main(){
    Solution solu;
    vector<int> nums{73,74,75,71,69,72,76,73};
    vector<int> res = solu.dailyTemperatures(nums);
    for(auto num: res)
        printf("%d\t", num);
    return 0;
}