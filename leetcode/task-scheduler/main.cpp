#include<iostream>
#include<string>
#include <algorithm> 
#include<vector>
using namespace std;
class Solution {
    static bool compare(pair<int,int> p1,pair<int,int> p2){
        return p1.second>p2.second||(p1.second==p2.second&&p1.first<=p2.first);
    }

    void arrange(vector<pair<int,int>> &task_list){
        sort(task_list.begin(),task_list.end(),compare);
        for(int i=0;i<task_list.size();++i){
            if(task_list[i].first==0){
                task_list.erase(task_list.begin()+i);
                i--;
            }
        }
    }

    void wait(vector<pair<int,int>> &task_list, int time)
    {
        for(int i=0;i<task_list.size();++i)
        {
            task_list[i].second= task_list[i].second>time?task_list[i].second-time:0;
        }
    }
public:
    int leastInterval(vector<char>& tasks, int n) {
        vector<pair<int,int>> task_list(26,pair<int,int>{0,0});

        int len = tasks.size();
        for(int i=0;i<len; ++i){
            task_list[tasks[i]-'A'].first++;
        }

        int res=0;
        while(len>0){
            arrange(task_list);
            res+=task_list[0].second;
            task_list[0].first--;
            wait(task_list,task_list[0].second+1);
            task_list[0].second=n;
            len--;
            res++;
        }
        return res;
    }
};

int main(){
    vector<char> tasks{'A','A','A','B','B','B'};
    Solution solution;

    printf("result of schedule: %d", solution.leastInterval(tasks,2));
    return 0;
}