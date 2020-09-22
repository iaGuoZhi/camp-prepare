#include <cctype>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include<vector>
using namespace std;


class Solution{
    int size;
    vector<pair<long,long>> hashTable;
public:
    vector<string> readFile(string fileName){
        std::ifstream istr(fileName);
        if(istr.fail()){
            throw new runtime_error("");
        }
        
        vector<string> content;
        string line;
        while(getline(istr, line)){
            content.push_back(line);
        }

        istr.close();
        return content;
    }


    void writeFile(string resultFile, vector<string> content){
        std::ofstream ostr(resultFile);
        if(ostr.fail()){
            throw new runtime_error("");
        }

        for(string s: content){
            ostr<<s<<endl;
        }
    }

    Solution(){
        hashTable=vector<pair<long,long>>(8, pair<long,long>{-1,-1});
        size=0;
    }

    void run(string fileName, string resultFile){
        vector<string> requests=readFile(fileName);
        vector<string> result;
        for(int i=0;i<requests.size();++i){
            vector<string> tokens;
            string s;
            requests[i].push_back(' ');
            for(int j=0;j<requests[i].size();++j){
                if(requests[i][j]==' '){
                    tokens.push_back(s);
                    s="";
                }
                else{
                    s.push_back(requests[i][j]);
                }
            }
            
            if(tokens[0]=="Get"){
                result.push_back(query(stol(tokens[1])));
            }else{
                if(tokens[0]=="Set"){
                    put(stol(tokens[1]), stol(tokens[2]));
                }else if(tokens[0]=="Del"){
                    delet(stol(tokens[1]));
                }
            }
        }

        writeFile(resultFile,result);
    }

    void delet(long key){
        long pos=key%hashTable.size();

        while(hashTable[pos].first!=key){
            pos=(pos+1)%(hashTable.size());
            if(pos==(key%hashTable.size()))
                return;
        }

        long mod=pos;
        long prior=pos;
        while(hashTable[pos].first!=-1&&hashTable[pos].first%hashTable.size()==mod){
            long next=(pos+1)%hashTable.size();
            if(hashTable[next].first==-1||hashTable[next].first%hashTable.size()!=mod){
                hashTable[prior]=hashTable[pos];
                if(hashTable[next].first!=-1&&hashTable[next].first%hashTable.size()!=next){
                    hashTable[pos]=hashTable[next];
                    prior=next;
                    mod=hashTable[next].first%hashTable.size();
                }
            }
            pos=next;
        }
    }


    void put(long key, long value){
        if(size==hashTable.size()/2){
            enlarge();
        }

        long pos=key%hashTable.size();

        while(hashTable[pos].first!=key&&hashTable[pos].first!=-1){
            pos=(pos+1)%(hashTable.size());
        }

        hashTable[pos]=pair<long,long>{key, value};
        size++;
    }

    string query(long key){
        long pos= key%hashTable.size();

        while(hashTable[pos].first!=key&&hashTable[pos].first!=-1){
            pos=(pos+1)%hashTable.size();
            if(pos==(key%hashTable.size()))
                return "null";
        }

        return to_string(hashTable[pos].second);
    }


    void enlarge(){
        vector<pair<long,long>> largerTable(2*hashTable.size(), pair<long,long>{-1,-1});
        //system("ls");
        long tmp;
        cout<<sizeof(tmp);
        for(auto p: hashTable){
            if(p.first!=-1){
                long pos = p.first%largerTable.size();

                while(largerTable[pos].first!=-1){
                    pos=(pos+1)%largerTable.size();
                }

                largerTable[pos]=p;
            }
        }

        hashTable = largerTable;
    }
};


int main(){
    Solution solu;
    solu.run("small.in", "mysmall.ans");
}