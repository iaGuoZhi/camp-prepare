#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;

class Solution {
    vector<int> parent;

    void unions(int p, int q){
        int rootP =find(p);
        int rootQ = find(q);

        if(rootP==rootQ)
            return;
        
        if(rootP<rootQ)
            parent[rootQ]=rootP;
        else
            parent[rootP]=rootQ;
    }

    int find(int p){
        while(parent[p]!=p){
            parent[p]=parent[parent[p]];
            p=parent[p];
        }
        return p;
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        if(grid.size()==0)
            return 0;
        
        parent = vector<int>(grid.size()*grid[0].size(), 0);

        for(int i=0;i<grid.size();++i)
        {
            for(int j=0;j<grid[i].size();++j)
                if(grid[i][j]=='1')
                parent[i*grid[i].size()+j]=i*grid[i].size()+j;
                else
                parent[i*grid[i].size()+j]=-1;
        }

        for(int i=0;i<grid.size();++i){
            for(int j=0;j<grid[i].size();++j){
                if(grid[i][j]=='1'){
                    for(int k=-1;k<=1;++k){
                        for(int t=-1;t<=1;++t)
                        {
                            if(t!=k&&t+k!=0&&i+k>=0&&i+k<grid.size()&&j+t>=0&&j+t<grid[0].size()&&grid[i+k][j+t]=='1')
                            unions(i*grid[0].size()+j,(i+k)*grid[0].size()+j+t);
                        }
                    }
                }
            }
        }

        int ans=0;
        unordered_set<int> land;
        for(int i=0;i<grid.size()*grid[0].size();++i){
            if(parent[i]!=-1)
            {
                int p=parent[i];
                while(p!=parent[p])
                    p=parent[p];

                if(!land.count(p)){
                    ans++;
                    land.insert(p);
                }
            }
        }
        return ans;
    }
};

int main(){
    Solution solu;
    vector<vector<char>> grid{{'1','1','1','1','0'},{'1','1','0','1','0'},{'1','1','0','0','0'},{'0','0','0','0','0'}};
    cout<<solu.numIslands(grid);

    return 0;
}