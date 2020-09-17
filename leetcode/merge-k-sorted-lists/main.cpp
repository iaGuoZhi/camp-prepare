#include<iostream>
#include<vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
    ListNode* merge2Lists(ListNode *list1, ListNode *list2){
        ListNode *ans;
        if(list1==NULL)
            return list2;
        if(list2==NULL)
            return list1;

        ans = (list1->val<=list2->val)?list1:list2;
        list1=(list1->val>list2->val)?list1:list2;

        ListNode *tail=ans;
        while(list1){
            if(tail->next==NULL){
                tail->next=list1;
                break;
            }
            if(list1->val<tail->next->val){
                ListNode *node=list1;
                list1=list1->next;
                node->next=tail->next;
                tail->next=node;
                tail=tail->next;
            }else{
                tail=tail->next;
            }
        }
        return ans;
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        vector<ListNode *> next;
        for(int i=0;i<lists.size()/2;++i){
            next.push_back(merge2Lists(lists[2*i],lists[2*i+1]));
        }
        if(lists.size()%2==1)
            next.push_back(lists[lists.size()-1]);
        if(next.size()==1)
            return next[0];
        if(next.size()==0)
            return NULL;
        return mergeKLists(next);
    }
};

int main(){
    Solution solu;
    return 0;
}