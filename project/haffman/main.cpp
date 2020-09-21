#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<cstdio>
#include<assert.h>
#include<map>
using namespace std;


struct Tree {
    vector<int> codes;
    int weight;
    char charactor;
    Tree *left;
    Tree *right;

    Tree(int w, char ch){
        weight=w;
        charactor =ch;
        left=NULL;
        right=NULL;
        codes = vector<int>{};
    }
};

class Solution{
    Tree *root;
    static bool compare(Tree *t1, Tree *t2){
        return t1->weight>t2->weight;
    }

public:
    void search(Tree *root, vector<int> parentCodes){
        if(root==NULL)
            return;
        for(int i=0;i<parentCodes.size();++i){
            root->codes.insert(root->codes.begin()+i, parentCodes[i]);
        }
        search(root->left, root->codes);
        search(root->right, root->codes);
    }

    vector<Tree *> generateRoot(string srcFile){
        int fd = open(srcFile.c_str(), O_RDWR, 0);
        vector<Tree *> table(26,NULL);
        for(int i=0;i<26;++i){
            table[i]=new Tree(0, i+'a');
        }
        char ch;
        while(read(fd, &ch, 1)!=0){
            assert(ch>='a'&&ch<='z');
            assert(table[ch-'a']);
            table[ch-'a']->weight+=1;
        }

        sort(table.begin(), table.end(), compare);

        cout<<table[0]->weight;

        for(int i=0;i<table.size();++i){
            if(table[i]->weight==0){
                table.erase(table.begin()+i, table.end());
                break;
            }
        }

        cout<<table.size();
        if(table.size()==0){
            return table;
        }

        int end=table.size()-1;
        while(end>0){
            sort(table.begin(), table.end(), compare);
            Tree *node1= table[end];
            Tree *node2 = table[end-1];
            node1->codes.push_back(0);
            node2->codes.push_back(1);
            Tree *parent = new Tree(node1->weight+node2->weight, ' ');
            parent->left=node1;
            parent->right=node2;
            table.insert(table.begin()+end-1, parent);
            end-=1;
        }

        root= table[0];
        search(root, vector<int>{});
        return table;
    }

    void encode(string srcFile, string outFile){
        vector<Tree *> table=generateRoot(srcFile);    
        map<char, vector<int>> charToCodesMap;
        for(auto t: table){
            if(t->charactor!=' '&&!charToCodesMap.count(t->charactor))
            {
                charToCodesMap[t->charactor]=t->codes;
            }
        }

        for(auto it: charToCodesMap){
            cout<<it.first<< " "<<it.second.size()<<endl;
        }

        
    }

    void decode(string srcFile, string outFile){

    }
};

int main(){
    Solution solu;
    solu.encode("file.txt", "out1.txt");
}