#include<iostream>


struct ListNode {
    int val;
   ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if(head==NULL||head->next==NULL)
            return head;
        
        ListNode *fast=head->next,*low=head, *res;
        while(fast!=NULL&&fast->next!=NULL)
        {
            fast=fast->next;
            fast=fast->next;
            low=low->next;
        }
        fast=low->next;
        low->next=NULL;
        low=head;

        fast=sortList(fast);
        low=sortList(low);

        head=low;
        if(fast&&fast->val<low->val)
            head=fast;
        if(head==fast)
            fast=fast->next;
        else
            low=low->next;
        res=head;
       
        while(fast&&low)
        {
            if(fast->val<=low->val)
            {
                head->next=fast;
                fast=fast->next;
            }else{
                head->next=low;
                low=low->next;
            }
            head=head->next;
        }

        if(fast)
            head->next=fast;
        else
            head->next=low;
        
        return res;
    }
};

void traverse(ListNode *node)
{
    printf("list: \n");
    while(node){
        printf("->%d",node->val);
        node=node->next;
    }
    printf("\n");
}

int main(){
    ListNode *node=new ListNode(4);
    node->next =new ListNode(2);
    node->next->next = new ListNode(1);
    node->next->next->next = new ListNode(3);

    traverse(node);

    Solution solution;
    node =solution.sortList(node);
    traverse(node);
}