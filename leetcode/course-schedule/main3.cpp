#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Solution {
    vector<vector<int>> grid;
    vector<int> degree;
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        grid = vector<vector<int>>(numCourses, vector<int>());
        degree = vector<int> (numCourses, 0);
        int zero=0;
        queue<int> q;

        for(int i=0;i<prerequisites.size();++i){

            grid[prerequisites[i][0]].push_back(prerequisites[i][1]);
            degree[prerequisites[i][1]]++;
        }

        // 入度为0的进队列
        for(int i=0;i<numCourses;++i){
            if(degree[i]==0){
                q.push(i);
                zero++;
            }
        }

        while(!q.empty()){
            int course= q.front();
            q.pop();
            for(int k=0;k<grid[course].size();++k){
                degree[grid[course][k]]--;
                if(degree[grid[course][k]]==0){
                    zero++;
                    q.push(grid[course][k]);
                }
            }
        }

        return zero==numCourses;
    }
};
int main(){
    Solution solu;
    vector<vector<int>> pre{{1,0},{0,1}};

    cout<<solu.canFinish(2,pre);
}