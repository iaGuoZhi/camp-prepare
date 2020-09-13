#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
    static bool compare(vector<int> num1, vector<int> num2){
        return num1[0]>num2[0]||(num1[0]==num2[0]&&num1[1]<num2[1]);
    }
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
       sort(people.begin(),people.end(), compare);

        vector<vector<int>> ans;
        for(int i=0;i<people.size();++i)
        {
            ans.insert(ans.begin()+people[i][1], people[i]);
        }
        return ans;
    }
};

int main(){
    return 0;
}