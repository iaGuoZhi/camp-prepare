#include<iostream>
#include<algorithm>
#include<vector>
#include<limits.h>

using namespace std;


class Solution{
    vector<int> squares;


public:
    void initSquare(int n){
        for(int i=1;i*i<n;++i){
            squares.push_back(i*i);
        }
    }

    int minSquareNumber(int n){
        if(n<=1)
            return 1;
        int minVal=INT_MAX;
        for(int i=0;i<squares.size();++i)
        {
            if(squares[i]>n)
                break;
            if(squares[i]==n)
                return 1;
            minVal=min(minVal,minSquareNumber(n-squares[i]));
        }
        return minVal+1;
    }
};

int main(){
    int number;
    while(cin>>number){
        Solution solu;
        solu.initSquare(number);
        cout<<solu.minSquareNumber(number);
    }
    return 0;
}