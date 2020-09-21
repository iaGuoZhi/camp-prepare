#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<map>
#include<queue>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x): val(x), left(NULL), right(NULL){}
};

class Solution{

public:
    string serialize(TreeNode *root){
        string content;
        vector<string> tokens;
        if(root!=NULL){
            queue<TreeNode *> arrays;
            tokens.push_back(to_string((root->val)));
            arrays.push(root);
            while(arrays.size()){
                int size=arrays.size();
                for(int i=0;i<size;++i){
                    TreeNode *node = arrays.front();
                    arrays.pop();
                    tokens.push_back(node->left?to_string(node->left->val):"null");
                    tokens.push_back(node->right?to_string(node->right->val):"null");
                    if(node->left)
                        arrays.push(node->left);
                    if(node->right)
                        arrays.push(node->right);
                }
            }
            int end=tokens.size()-1;
            while(end>=0&&tokens[end]=="null"){
                tokens.erase(tokens.end()-1);
                end--;
            }
        }
        content="[";
        for(auto t:tokens){
            content.append(t);
            content.push_back(',');
        }
        content[content.size()-1]=']';
        return content;
    }

    TreeNode* generateTree(vector<string> &tokens){
        if(tokens.size()==0||tokens[0]=="null")
            return NULL;
        queue<TreeNode *> arrays;
        TreeNode *node = new TreeNode(stoi(tokens[0]));
        arrays.push(node);
        int index=1;
        while(index<tokens.size()){
            int size=arrays.size();
            for(int i=0;i<size;++i){
                TreeNode *curNode = arrays.front();
                arrays.pop();
                if(tokens[index]!="null")
                {   
                    curNode->left=new TreeNode(stoi(tokens[index]));
                    arrays.push(curNode->left);
                }
                if(index+1<tokens.size()&&tokens[index+1]!="null"){
                    curNode->right=new TreeNode(stoi(tokens[index+1]));
                    arrays.push(curNode->right);
                }
                index+=2;
            }
        }
        return node;
    }


    TreeNode * deserialize(string data){
        data=data.substr(1, data.size()-2);
        data.push_back(',');
        vector<string> tokens;
        string s;
        for(int i=0;i<data.size();++i)
        {
            if(data[i]==','){
                tokens.push_back(s);
                s="";
            }else{
                s.push_back(data[i]);
            }
        }

        return generateTree(tokens);
    }

    string readFile(string fileName){
        char *buffer;
        FILE *fh = fopen(fileName.c_str(), "rb");
        if(fh){
            fseek(fh, 0L, SEEK_END);
            long s= ftell(fh);
            rewind(fh);
            buffer=(char *) malloc(s);
            if(buffer!=NULL){
                fread(buffer, s, 1, fh);
                fclose(fh);
                fh=NULL;
                return buffer;
            }
        }
        return "";
    }

    void writeFile(string fileName, string content){
        FILE *fh=fopen(fileName.c_str(), "wb");
        if(fh){
            fwrite(content.c_str(), content.size(), 1, fh);
            fclose(fh);
        }
    }

    void preorderTraversal(TreeNode *node){
        if(node!=NULL){
            cout<<node->val<<endl;
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }

    void run(string fileName, string outFile){
        string content=readFile(fileName);
        TreeNode *node = deserialize(content);
        preorderTraversal(node);
        string result= serialize(node);
        writeFile(outFile, result);
    }
};

int main(){
    Solution solu;
    solu.run("file.txt","out.txt");
    //solu.writeFile("file.txt", "[1,2,3,null,null,4,5]");
}