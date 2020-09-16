#include<iostream>
#include<vector>

using namespace std;

class Solution {
    vector<vector<int>> grid;
    vector<bool> visited;

    bool check(int num){
        if(visited[num]==true) 
            return false;
        visited[num]=true;

        for(int i=0;i<grid[num].size();++i){
            if(check(grid[num][i])==false)
                return false;
        }

        visited[num]=false;
        return true;
    }
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        grid = vector<vector<int>>(numCourses, vector<int>());
        visited = vector<bool>(numCourses, false);

        for(int i=0;i<prerequisites.size();++i){
            grid[prerequisites[i][0]].push_back(prerequisites[i][1]);
        }

        for(int i=0;i<numCourses;++i){
            if(!check(i))
                return false;
        }
        return true;
    }
};

int main(){
    Solution solu;
    vector<vector<int>> pre{{1,0},{0,1}};

    cout<<solu.canFinish(2,pre);
}