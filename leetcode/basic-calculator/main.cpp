#include<iostream>
#include<vector>
#include<numeric>
using namespace std;

class Solution {
    int calHelper(string s, int &index){
        vector<int> nums;
        int op=1;
        int num=0;

        while(index<s.size()){
            if(s[index]=='('){
                index++;
                num=calHelper(s, index);    
                continue;
            }

            if(index<s.size()&&s[index]==')'){
                index++;
                break;
            }

            if(index<s.size()&&s[index]=='+'){
                nums.push_back(op*num);
                op=1;
                num=0;
            }

            if(index<s.size()&&s[index]=='-'){
                nums.push_back(op*num);
                op=-1;
                num=0;
            }
            
            if(index<s.size()&&s[index]>='0'&&s[index]<='9')
            {
                num*=10;
                num+=s[index]-'0';
            }
            index++;
        }
        nums.push_back(op*num);

        return accumulate(nums.begin(),nums.end(),0);
    }
public:
    int calculate(string s) {
        int index=0;
        return calHelper(s, index);
    }
};


int main(){
    Solution solu;
    cout<<solu.calculate("(1+(4+5+2)-3)+(6+8)");
    return 0;
}