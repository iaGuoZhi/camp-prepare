#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int totalGas=0,totalCost=0;
        int size = gas.size();;
        for(int i=0;i<size;++i)
        {
            totalGas+=gas[i];
            totalCost+=cost[i];
        }

        if(totalCost>totalGas) return -1;
        int curGas =0;
        for(int i=0;i<size;++i){
            int j=i;
            curGas=0;
            for(j=i;j<size;++j){
                curGas+=gas[j];
                curGas-=cost[j];
                if(curGas<0){
                    i=j;
                    break;
                }
            }
            if(j==size){
                return i;
            }
        }
        return -1;
    }
};


int main(){
    Solution solution;
    vector<int> arr1{3,6,7,8,2}, arr2{4,2,6,4,4};
    cout<<solution.canCompleteCircuit(arr1,arr2);
}