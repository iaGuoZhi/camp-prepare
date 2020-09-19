#include<iostream>
#include<thread>
#include<mutex>
#include<pthread.h>
#include<condition_variable>

std::mutex mtx;
using namespace std;

condition_variable data_var;
bool flag=true;

string name="gz";

class Solution{

    static void foo(int id){

        while(true){
            unique_lock<mutex> lck(mtx);
            if(id==0)
                data_var.wait(lck, []{return flag;});
            else
            {
                data_var.wait(lck,[]{return !flag;});
            }
            
            cout<<"thread: "<<this_thread::get_id()<<" printf: "<<name[id]<<endl;
            flag=id==0?false:true;
            data_var.notify_one();
       }
    }

public:
    void run(){
        thread first(foo,0);
        thread second(foo,1);

        first.join();
        second.join();
    }
};

int main(){
    Solution solu;
    solu.run();
    return 0;
}