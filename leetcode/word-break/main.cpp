#include<iostream>
#include<vector>
#include<set>
#include<string>
#include<unordered_set>
using namespace std;


class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        auto wordDictSet = unordered_set<string>();

        for(auto word: wordDict){
            wordDictSet.insert(word);
        }

        vector<bool> dp(s.size()+1, false);

        dp[0]=true;

        for(int i=1;i<=s.size();++i){
            for(int j=0;j<i;++j){
                if(dp[j]&&wordDictSet.find(s.substr(j,i-j))!=wordDictSet.end()){
                    dp[i]=true;
                }
            }
        }
        return dp[s.size()];
    }
};


int main(){
    Solution solution;

    string s = "leetcode";
    vector<string> wordDict{"leet","code"};

    cout<<solution.wordBreak(s, wordDict);
    return 0;
}