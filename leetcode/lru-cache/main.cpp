#include<iostream>
#include<vector>
#include<string>
#include<map>
using namespace std;

struct Node{
    Node *left;
    Node *right;
    int val;
    int key;
    Node(int k,int value){
        key =k;
        val = value;
        left= NULL;
        right = NULL;
    }
};
class LRUCache {

    map<int, Node*> cacheMap;
    Node *head, *tail;
    int size;

    void MoveToHead(Node *node){
        RemoveNode(node);
        AddToHead(node);
    }

    void AddToHead(Node *node){
        head->right->left=node;
        node->right=head->right;
        node->left=head;
        head->right=node;
    }

    void RemoveNode(Node *node){
        node->left->right=node->right;
        node->right->left=node->left;
    }

    void RemoveTail() {
        Node *node = tail->left;
        RemoveNode(node);
        cacheMap.erase(node->key);
        delete(node);
    }
public:
    LRUCache(int capacity) {
        head = new Node(0,0);
        tail = new Node(0,0);
        head->right= tail;
        tail->left = head;
        size= capacity;
    }
    
    int get(int key) {
        if(!cacheMap.count(key))
            return -1;
        Node *node = cacheMap[key];
        MoveToHead(node);
        return node->val;
    }
    
    void put(int key, int value) {
        if(!cacheMap.count(key)){
            Node *node = new Node(key,value);
            AddToHead(node);
            cacheMap[key]= node;
            if(cacheMap.size()>size){
                RemoveTail();
            }
        }else{
            Node *node = cacheMap[key];
            node->val=value;
            MoveToHead(node);
        }
    }
};

int main(){
    LRUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);
    cout<<cache.get(1);       // 返回  1
    cache.put(3, 3);    // 该操作会使得关键字 2 作废
    cache.get(2);       // 返回 -1 (未找到)
    cache.put(4, 4);    // 该操作会使得关键字 1 作废
    cache.get(1);       // 返回 -1 (未找到)
    cache.get(3);       // 返回  3
    cache.get(4);       // 返回  4
}