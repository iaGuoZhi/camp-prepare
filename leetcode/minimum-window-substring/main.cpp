#include<iostream>
#include<vector>
#include<string>
#include<limits.h>
using namespace std;


class Solution {
    
public:
    string minWindow(string s, string t) {
        int need= t.size();
        int m[128]={0};

        for(auto ch: t)
            m[ch]++;

        int i=0,j=0,minLen=INT_MAX,minIndex=-1;
        while(i<s.size()){
            if(m[s[i]]>0)
            {
                need--;
            }

            --m[s[i]];
            while(need==0){
                ++m[s[j]];
                if(m[s[j]]>0)
                {
                    if(i-j+1<minLen){
                        minLen=i-j+1;
                        minIndex=j;
                    }
                    need++;
                }
                j++;
            }
            i++;
        }

        if(minIndex==-1)
            return "";
        return s.substr(minIndex, minLen);
    }
};

int main(){
    Solution solu;
    cout<<solu.minWindow("abceadgaaarfvaaawaabaee", "ada");
    return 0;
}