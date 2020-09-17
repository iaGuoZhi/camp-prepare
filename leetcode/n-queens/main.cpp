#include<iostream>
#include<vector>
#include<string>
using namespace std;


class Solution {
    vector<bool> column;
    vector<int> pos;
    vector<bool> down, up;
    vector<vector<string>> ans;
    int size;

    void backtrace(int level){
        if(level==size)
        {
            vector<string> templateGrid(size, string(size, '.'));
            for(int i=0;i<size;++i){
                templateGrid[i][pos[i]]='Q';
            }
            ans.push_back(templateGrid);
            return ;
        }

        for(int i=0;i<size;++i){
            if(column[i]==false&&down[level+i]==false&&up[size+i-level-1]==false){
                column[i]=true;
                pos[level]=i;
                down[level+i]=true;
                up[size+i-level-1]=true;
                backtrace(level+1);
                column[i]=false;
                down[level+i]=false;
                up[size+i-level-1]=false;
            }
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        column=vector<bool>(n, false);
        pos=vector<int>(n, -1);
        down=vector<bool>(2*n-1,false);
        up=vector<bool>(2*n-1, false);
        size=n;

        backtrace(0);
        return ans;
    }
};

int main(){
    Solution solu;
    vector<vector<string>> ans = solu.solveNQueens(10);

    for(int i=0;i<ans.size();++i){
        printf("strategy %d\n",i+1);
        for(int j=0;j<ans[i].size();++j){
            printf("%s\n", ans[i][j].c_str());
        }
        printf("\n");
    }
    return 0;
}