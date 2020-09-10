#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Solution {
    bool equal(char s, char p){
        return s==p||p=='?';
    }

public:
    bool isMatch(string s, string p) {
        int sSize = s.size(), pSize = p.size();

        vector<vector<bool>> table(pSize+1,vector<bool>(sSize+1,false));
        table[0][0] =true;

        for(int i=0;i<pSize;++i)
        {
            if(p[i]!='*')
                break;
            table[i+1][0]=true;
        }

        for(int i=0;i<pSize;++i){
            for(int j=0;j<sSize;++j)
            {
                if(equal(s[j], p[i])){
                    table[i+1][j+1]=table[i][j];
                }
                if(p[i]=='*'){
                    for(int k=j+1;k>=0;--k){
                        if(table[i][k]==true){
                            table[i+1][j+1]=true;
                            break;
                        }
                    }
                }
            }
        }

        return table[pSize][sSize]==true;
    }
};

int main(){
    Solution solution;
    cout<<solution.isMatch("123455","**?5");
}