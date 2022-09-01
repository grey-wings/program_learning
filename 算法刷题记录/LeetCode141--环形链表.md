[题目链接](https://leetcode-cn.com/problems/linked-list-cycle/)  

[算法参考](https://www.cnblogs.com/kyoner/p/11087755.html)  
解法：双指针  
这里用双指针里面的快慢指针解决问题。  
在这样一个有环的链表中，设置两个指针，他们的起点都设为head节点。一个快指针，一次走两格，一个慢指针，一次走一格。  
![](https://img2018.cnblogs.com/blog/1566782/201906/1566782-20190626075016458-1495003044.jpg)  
如果链表中没有环，那么显然快指针会到达链表的末尾。  
如果有环，那么两个指针都会进入环中绕圈子。快指针最终会套慢指针一圈，两者相遇。  
因此，如果快慢指针最后相遇，则说明链表有环。  

代码如下：  
```cpp
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == nullptr or head->next == nullptr)
            return false;
        ListNode* p1 = head;
        ListNode* p2 = head;
        while (p2->next != nullptr and p2->next->next != nullptr){
            p1 = p1->next;
            p2 = p2->next->next;
            if (p1 == p2)
                return true;
        }
        return false;
    }
};
```
