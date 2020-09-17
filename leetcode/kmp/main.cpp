#include<iostream>
#include<vector>
#include<string>
using namespace std;


class Solution {
    vector<int> buildNext(string needle){
        int i=0, t=-1;
        vector<int> ans(needle.size(),-1);

        while(i<needle.size()-1){
            if(t<0||needle[i]==needle[t]){
                i++;
                t++;
                ans[i]=t;
            }else{
                t=ans[t];
            }
        }

        return ans;
    }
public:
    int strStr(string haystack, string needle) {
        if(needle.size()==0)
            return 0;
        vector<int> next=buildNext(needle);
        int i=0,j=0, ilen=haystack.size(), jlen=needle.size();

        while(i<ilen&&j<jlen){
            if(j<0||haystack[i]==needle[j]){
                i++;
                j++;
            }else{
                j=next[j];
            }
        }

        if(i==ilen&&j!=jlen)
        return -1;

        return i-j;
    }
};

int main(){
    Solution solu;
    cout<<solu.strStr("hello", "ll");
    return 0;
}