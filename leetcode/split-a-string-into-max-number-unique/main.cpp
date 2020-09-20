#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
using namespace std;

class Solution {
    unordered_set<string> sets;
    int ans=1;
    void dfs(string s,int pos){
        if(pos==s.size())
        {
            ans=max(ans,int(sets.size()));
            return;
        }
        if(int(s.size())-pos+(sets.size())<=ans)
            return;
        
        for(int i=pos+1;i<=s.size();++i){
            string ch=s.substr(pos, i-pos);
            if(sets.find(ch)!=sets.end())
                continue;
            sets.insert(ch);
            dfs(s, i);
            sets.erase(ch);
        }
    }
public:
    int maxUniqueSplit(string s) {
        dfs(s, 0);
        return ans;
    }
};

int main(){
    Solution solu;
    cout<<solu.maxUniqueSplit("abedfearffaarj");
    return 0;
}