#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
using namespace std;

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n=points.size();

        vector<bool> visited(n, false);
        vector<int> distances(n, INT_MAX);

        distances[0]=0;
        int ans=0;
        for(int i=0;i<n;++i){
            int minDis=INT_MAX;
            int point;
            for(int j=0;j<n;++j){
                if(!visited[j]&&(minDis>distances[j])){
                    point=j;
                    minDis=distances[j];
                }
            }
            ans+=distances[point];
            visited[point]=true;
            
            for(int j=0;j<n;++j){
                if(point!=j&&distances[j]>(abs(points[point][0]-points[j][0])+abs(points[point][1]-points[j][1]))){
                    distances[j] = abs(points[point][0]-points[j][0])+abs(points[point][1]-points[j][1]);
                }
            }
        }
        return ans;
    }
};

int main(){
    vector<vector<int>> points{{0,0},{2,2},{3,10},{5,2},{7,0}};

    Solution solu;
    cout<<solu.minCostConnectPoints(points);
    return 0;
}