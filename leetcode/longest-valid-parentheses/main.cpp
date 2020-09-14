#include<iostream>
#include<string>
#include<map>
using namespace std;


class Solution {
public:
    int longestValidParentheses(string s) {
        map<int,int> mp;
        mp[0]=-1;
        int base=0;
        int ans=0;
        for(int i=0;i<s.size();++i){
            if(s[i]=='('){
                base+=1;
                
                mp[base]=i;
            }else{
                base-=1;
                if(base<0){
                    mp.clear();
                    mp[0]=i;
                    base=0;
                }
                if(mp.count(base)){
                    ans=max(i-mp[base], ans);
                }
            }
        }
        return ans;
    }
};

int main(){
    string s="((())()()))))()()";

    Solution solu;
    cout<<solu.longestValidParentheses(s);
    return 0;
}