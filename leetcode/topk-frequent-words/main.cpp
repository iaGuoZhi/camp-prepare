#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<algorithm>
using namespace std;

class Solution {
public:
    //题解：用map代替前缀树
    vector<string> topKFrequent_1(vector<string>& words, int k) {
        if(words.empty()||k==0)return {};
        map<string,int> record_1;//单词->该单词出现的个数
        vector<string> result;
        for(const auto& word:words){
            record_1[word]++;
        }
        //由于map不支持value的sort排序，所以必须将map转换为vector才能进行sort自定义排序
        vector<pair<string,int>> record_2(record_1.begin(),record_1.end());
        //sort的第三个参数是lambda表达式，其实和传普通函数一样，sort的第三个参数是支持二元谓词的
        sort(record_2.begin(),record_2.end(),
             [](const pair<string,int>& a,const pair<string,int>& b)
             {
                 if(a.second==b.second)return a.first<b.first;
                 else return a.second>b.second;
              }
            );
        //将vector的前k个元素添加到result中
        for(const auto& r:record_2)
        {
            if(k--==0)break;
            result.push_back(r.first);
        }
        return result;
    }
};

int main(){
    return 0;
}