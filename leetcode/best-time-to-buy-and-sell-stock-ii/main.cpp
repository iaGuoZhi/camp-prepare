#include<iostream>
#include<vector>
using namespace std;;

class Solution {
public:
    static int maxProfit(vector<int>& prices) {
        int res=0;
        for(int i=1;i<prices.size();++i)
        {
            if(prices[i]>prices[i-1]){
                res+=prices[i]-prices[i-1];
            }
        }
        return res;
    }
};

int main(){
    vector<int> stocks{7,1,5,3,6,4};
    cout<<Solution::maxProfit(stocks)<<endl;
    return 0;
}