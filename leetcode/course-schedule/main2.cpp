#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Solution {
    vector<vector<int>> grid;
    vector<bool> visited;

    void reset(){
        for(int i=0;i<visited.size();++i)
            visited[i]=false;
    }
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        grid = vector<vector<int>>(numCourses, vector<int>());
        visited = vector<bool>(numCourses, false);
        queue<int> q;

        for(int i=0;i<prerequisites.size();++i){
            grid[prerequisites[i][0]].push_back(prerequisites[i][1]);
        }

        for(int i=0;i<numCourses;++i){
            for(int j=0;j<grid[i].size();++j){
                q.push(grid[i][j]);
            }
            reset();
            while(!q.empty()){
                int course= q.front();
                q.pop();
                visited[course]=true;
                if(course==i)
                    return false;
                for(int k=0;k<grid[course].size();++k){
                    if(!visited[grid[course][k]])
                        q.push(grid[course][k]);
                }
            }
        }
        return true;
    }
};

int main(){
    Solution solu;
    vector<vector<int>> pre{{1,0},{0,1}};

    cout<<solu.canFinish(2,pre);
}