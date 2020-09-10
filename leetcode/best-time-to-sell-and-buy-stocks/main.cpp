#include<iostream>
#include<vector>
#include<limits.h>
#include<algorithm>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxprofit =0;
        int minprice = INT_MAX;
        for(int i=0;i<prices.size();++i)
        {
            maxprofit = max(maxprofit, prices[i]-minprice);
            minprice=min(minprice, prices[i]);
        }
        return maxprofit;
    }
};

int main(){
    Solution solution;
    vector<int> nums{2,5,7,3,1,6,9,2};
    cout<<solution.maxProfit(nums);
    return 0;
}


