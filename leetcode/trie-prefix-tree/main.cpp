#include<iostream>
#include<string.h>
#include<string>
using namespace std;

class Trie {
    bool isEnd;
    Trie* children[26];
public:
    /** Initialize your data structure here. */
    Trie() {
        isEnd=false;
        //初始化为空指针,防止访问野指针
        memset(children,0, sizeof(children));
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie *node = this;
        for(int i=0;i<word.size();++i)
        {
            if(node->children[word[i]-'a']==NULL){
                node->children[word[i]-'a']=new Trie();
            }
            node=node->children[word[i]-'a'];
        }
        node->isEnd=true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Trie *node=this;
        for(int i=0;i<word.size();++i){
            if(node->children[word[i]-'a']==NULL){
                return false;
            }
            node=node->children[word[i]-'a'];
        }
        return node->isEnd;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Trie *node = this;
        for(auto n:prefix){
            if(node->children[n-'a']==NULL)
                return false;
            node=node->children[n-'a'];
        }
        return true;
    }
};


int main(){
    Trie trie;

    trie.insert("apple");
    cout<<trie.search("apple");   // 返回 true
    cout<<trie.search("app");     // 返回 false
    trie.startsWith("app"); // 返回 true
    trie.insert("app");   
    trie.search("app");     // 返回 true
}