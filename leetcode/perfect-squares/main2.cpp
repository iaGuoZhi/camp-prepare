#include<iostream>
#include<vector>
using namespace std;


class Solution {
public:
    int numSquares(int n) {
        vector<int> choices;
        int res = 1;

        // 构造物品，即所有小于给定数字的完全平方数
        while (n / res >= res) {
            choices.push_back(res * res);
            res++;
        }

        const int size = choices.size();
        vector<int> dp(n + 1, 0);

        // init
        for (int i = 0; i <= n; ++i) {
            dp[i] = i;
        }

        // 完全背包模板
        for (int i = 1; i < size; ++i) {
            for (int j = choices[i]; j <= n; ++j) {
                dp[j] = min(dp[j], dp[j - choices[i]] + 1);
            }
        }

        return dp[n];
    }
};

int main(){
    Solution solu;
    int number;
    while(cin>>number){
        cout<<solu.numSquares(number)<<endl;
    }
}