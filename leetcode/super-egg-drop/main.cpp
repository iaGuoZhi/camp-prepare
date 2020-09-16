#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


class Solution {
public:
    /*int superEggDrop(int K, int N) {
        if(N<=0)
            return 0;
        if(K==1||N==1)
            return N;

        int ans = INT_MAX;
        for(int i=1;i<=N;++i){
            int res= max(superEggDrop(K-1, i-1),superEggDrop(K, N-i))+1;
            ans = min(ans, res);
        }
        return ans;
    }*/

    int superEggDrop(int K, int N){
        if(K==1||N==1)
            return N;
        
        vector<vector<int>> dp(K+1, vector<int> (N+1, 0));

        for(int i=0;i<=N;++i){
            dp[1][i]=i;
        }

        for(int i=2;i<=K;++i){
            for(int k=1;k<=N;++k)
            {
                int num=0;
                for(int j=1;j<=k;++j){
                    num=max(dp[i-1][j-1], dp[i][k-j])+1;
                    dp[i][k]=dp[i][k]==0?num:min(num, dp[i][k]);
                }
            }
        }

        return dp[K][N];
    }
};

int main(){
    Solution solu;

    cout<<solu.superEggDrop(7,101);
    return 0;
}