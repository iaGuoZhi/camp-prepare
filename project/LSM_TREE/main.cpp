#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<limits.h>
#include<cassert>

using namespace std;


class KVPair{
public:
    int key;
    int offset;
    string value;
    KVPair(int k,int off, string v){
        key=k;
        offset=off;
        value=v;
    }
};

class SSTable{
public:
    int nKeys;
    int fileSize;
    int time;
    vector<KVPair> pairs;
};

class Solution{
    vector<SSTable> srcSSTables;
    vector<KVPair> sortedKVpairs;
    vector<KVPair> cleanKVPairs;
    string dir;

public:
    void insertSSTable(SSTable table){
        int begin=0;
        while(begin<srcSSTables.size()&&srcSSTables[begin].time<table.time)
            begin++;
        srcSSTables.insert(srcSSTables.begin()+begin,table);
    }

    void loadSSTables(string dir, int fileNumber){
        vector<string> fileNames;
        this->dir=dir;

        for(int i=0;i<fileNumber;++i){
            string s;
            char sb[100];
            sprintf(sb,"%ssstable-%d.sst", dir.c_str(), i+1);
            s=sb;
            fileNames.push_back(s);

            int fd=open(s.c_str(), O_RDONLY, 0);
            int num=0;
            SSTable ssTable;
            read(fd, &num, 4);
            ssTable.fileSize=num;
            read(fd, &num, 4);
            ssTable.time=num;

            int nkeys=0;
            read(fd, &nkeys, 4);
            ssTable.nKeys=nkeys;
            
            //store key and offset in a list
            vector<KVPair> kvpairs;
            for(int i=0;i<nkeys;++i){
                int key=0, offset=0;
                read(fd, &key, 4);
                read(fd, &offset, 4);
                KVPair kvpair(key,offset,"");
                kvpairs.push_back(kvpair);
            }
            
            //read value
            for(int i=0;i<nkeys;++i){
                int len=0;
                if(i==nkeys-1)
                    len=ssTable.fileSize-kvpairs[i].offset;
                else
                {
                    len = kvpairs[i+1].offset-kvpairs[i].offset;
                }
                char *sb=new char[len+1];
                read(fd, sb, len);
                sb[len]='\0';
                kvpairs[i].value=sb;
            }

            ssTable.pairs=kvpairs;
            insertSSTable(ssTable);
            cout<<ssTable.pairs[0].key<<" "<<ssTable.pairs[ssTable.nKeys-1].key<<endl;
        }
    }

    void sortSSTables(){
        int curSum=0;
        int expectedSum=0;
        vector<int> curIndex(srcSSTables.size(),0);
        
        for(int i=0;i< srcSSTables.size();++i){
            expectedSum+=srcSSTables[i].nKeys;
        }
        while(curSum<expectedSum){
            int curKey=INT_MAX;
            int curTable=-1;
            for(int i=0;i<curIndex.size();++i){
                if(curIndex[i]<srcSSTables[i].nKeys&&(srcSSTables[i].pairs[curIndex[i]].key<curKey)){
                    curKey=srcSSTables[i].pairs[curIndex[i]].key;
                    curTable=i;
                }
            }
            if(curTable==-1)   
                break;
            sortedKVpairs.push_back(srcSSTables[curTable].pairs[curIndex[curTable]]);
            curIndex[curTable]++;
            curSum++;
        }
        cout<<sortedKVpairs[0].key<<" "<<sortedKVpairs[sortedKVpairs.size()-1].key<<endl;
    }

    void cleanSSTables(){
        for(int i=0;i<sortedKVpairs.size();++i)
        {
            if(i<sortedKVpairs.size()-1&&sortedKVpairs[i].key==sortedKVpairs[i+1].key)
                continue;
            if(sortedKVpairs[i].value=="")
                continue;
            cleanKVPairs.push_back(sortedKVpairs[i]);
        }
        cout<<cleanKVPairs.size()<<" "<<cleanKVPairs[0].key<<" "<<cleanKVPairs[cleanKVPairs.size()-1].key<<endl;
    }
    
    void saveFile(int begin,int end,int label,int size){
        char sb[100];
        sprintf(sb, "%smy-output-%d.sst", this->dir.c_str(), label);
        int fd = open(sb, O_RDWR|O_CREAT|O_TRUNC, 0);
        int time=0x00ffffff;
        int nKeys= end-begin+1;
        //write metadata
        write(fd, &size, 4);
        write(fd, &time, 4);
        write(fd, &nKeys, 4);
        
        int offset =12+8*(end-begin+1);

        for(int i=begin;i<=end;++i){
            write(fd, &(cleanKVPairs[i].key),4);
            write(fd,&offset,4);
            offset+=cleanKVPairs[i].value.size();
        }
        cout<<offset<<" "<<size<<endl;
        assert(offset == size);

        for(int i=begin;i<=end;++i){
            write(fd, &(cleanKVPairs[i].value), cleanKVPairs[i].value.size());
        }
        close(fd);
    }

    void saveSSTables(){
        int curTableSize=12;
        int fileNum=0;
        int prevPair=0;
        for(int i=0;i<=cleanKVPairs.size();++i)
        {
            int pairSize=0;
            if(i<cleanKVPairs.size()){
                pairSize+=8;
                pairSize+=cleanKVPairs[i].value.size();
            }
        
            if(i==cleanKVPairs.size()||curTableSize+pairSize>256*1024)
            {
                saveFile(prevPair, i-1, fileNum+1, curTableSize);
                fileNum++;
                prevPair=i;
                curTableSize=0;
            }
            curTableSize+=pairSize;
        }
        cout<<fileNum<<endl;
    }

};

int main(){
    Solution solu;
    solu.loadSSTables("./small-case/", 3);

    
    solu.sortSSTables();
    solu.cleanSSTables();
    solu.saveSSTables();
}