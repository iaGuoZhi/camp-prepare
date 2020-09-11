#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<string,vector<string>> tables;
        vector<vector<string>> res;

        for(int i=0;i<strs.size();++i){
            string s = strs[i];
            sort(s.begin(),s.end());

            tables[s].push_back(strs[i]);
        }

        for(auto i: tables){
            res.push_back(i.second);
        }
        return res;
    }
};


int main(){
    Solution solution;
    vector<string> strs{"eat", "tea", "tan", "ate", "nat", "bat"};
    solution.groupAnagrams(strs);
    return 0;
}