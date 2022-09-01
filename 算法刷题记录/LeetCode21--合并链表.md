[题目链接](https://leetcode-cn.com/problems/merge-two-sorted-lists/)

代码  
```cpp
#include <bits/stdc++.h>
using namespace std;
#define fu(i,r,t) for(int i=r;i<=t;i++)
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(V) V.begin(),V.end()
#define print(i) cout<<(i)<<endl;
#define ll long long
#define ull unsigned long long
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    auto *l = new ListNode();
    auto *head = l;
    while (l1 != nullptr || l2 != nullptr){
        if (l1 == nullptr){
            auto *q = new ListNode(l2->val);
            l->next = q;
            l = l->next;
            l2 = l2->next;
            continue;
        }
        if (l2 == nullptr){
            auto *q = new ListNode(l1->val);
            l->next = q;
            l = l->next;
            l1 = l1->next;
            continue;
        }
        if (l1->val < l2->val){
            auto *q = new ListNode(l1->val);
            l->next = q;
            l = l->next;
            l1 = l1->next;
        }
        else{
            auto *q = new ListNode(l2->val);
            l->next = q;
            l = l->next;
            l2 = l2->next;
        }
    }
    return head->next;
}
int main() {
    int n1, n2, x;
    cin >> n1 >> n2;
    // head1和head2是ListNode型
    cin >> x;
    auto *tail1 = new ListNode(x);
    auto *head1 = tail1;
    for (int i = 1;i < n1;i++){
        cin >> x;
        auto *q = new ListNode(x);
        tail1->next = q;
        tail1 = tail1->next;
    }
    cin >> x;
    auto *tail2 = new ListNode(x);
    auto *head2 = tail2;
    for (int i = 1;i < n2;i++){
        cin >> x;
        auto *q = new ListNode(x);
        tail2->next = q;
        tail2 = tail2->next;
    }
    ListNode* head = mergeTwoLists(head1, head2);
    while (head != nullptr){
        cout << head->val << ' ';
        head = head->next;
    }
    return 0;
}

```
