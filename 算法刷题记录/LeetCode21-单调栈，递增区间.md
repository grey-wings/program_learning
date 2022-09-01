[题目链接：买卖股票的最佳时机（单次）](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/)  

单调栈解法：  
单调栈栈底到栈顶递增。用当前读到的prices[i]和a.top()比较，如果prices[i] > a.top()，则有可能卖出更高的价格；  
如果prices[i] < bottom，则从prices[i]开始买入，有可能有更大的收益。  
当然也有可能没有，所以要记录下当前的最大收益，然后才能清空栈。  
当bottom < prices[i] < a.top()时，不需要什么操作。因为假设后面在任意price[j]处卖出，在bottom处买入的收益肯定比在price[i]处买入的收益大。  
代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define fu(i,r,t) for(int i=r;i<=t;i++)
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(V) V.begin(),V.end()
#define print(i) cout<<(i)<<endl;
#define ll long long
#define ull unsigned long long
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty() or prices.size() == 1)
            return 0;
        stack<int> a;
        int ans = 0, head, tail, bottom = prices[0];
        a.push(bottom);
        for (int i = 1;i < prices.size();i++){
            if (prices[i] > a.top())
                a.push(prices[i]);
            else if (prices[i] == a.top())
                continue;
            else {
                if (prices[i] < bottom){
                    tail = a.top();
                    while (a.size() > 1)
                        a.pop();
                    head = a.top();
                    a.pop();
                    ans = max(ans, tail - head);
                    a.push(prices[i]);
                    bottom = prices[i];
                }
            }
        }
        ans = max(ans, a.top() - bottom);
        return ans;
    }
};
int main() {
    Solution sl;

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0;i < n;i++){
        cin >> a[i];
    }
    cout << sl.maxProfit(a);
    return 0;
}

```

[题目链接：买卖股票的最佳时机（多次）](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/)  

有上题的铺垫，解法并不难想。  
遍历一遍prices数组，当prices[i]比prices[i - 1]小的时候，那么就应当在i - 1处卖出，在i处买入。  
即寻找这个数组中所有的单调连续增区间。  
代码如下：
```cpp
#include <bits/stdc++.h>
using namespace std;
#define fu(i,r,t) for(int i=r;i<=t;i++)
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(V) V.begin(),V.end()
#define print(i) cout<<(i)<<endl;
#define ll long long
#define ull unsigned long long
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty() or prices.size() == 1)
            return 0;
        int ans = 0, buy = prices[0];
        for (int i = 1;i < prices.size();i++){
            if (prices[i] < prices[i - 1]){
                ans += prices[i - 1] - buy;
                buy = prices[i];
            }
        }
        ans += prices[prices.size() - 1] - buy;
        return ans;
    }
};
int main() {
    Solution sl;

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0;i < n;i++){
        cin >> a[i];
    }
    cout << sl.maxProfit(a);
    return 0;
}
```
