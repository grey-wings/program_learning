
最近公共祖先简称 LCA（Lowest Common Ancestor）。两个节点的最近公共祖先，就是这两个点的公共祖先里面，离根最远的那个。对于点集S，记S中所有点的最近公共祖先为LCA(S)。  

两点间的最近公共祖先必定处在树上两点间的最短路上。  
**d(u, v) = h(u) + h(v) - 2h(LCA(u, v))**，d是书上两点的距离，h代表某点到树根的距离。  

LCA可以用Tarjan算法来求。  
Tarjan是一种离线算法，是指在一次遍历中把所有询问一次性解决，所以其时间复杂度是O(n+q)    
Tarjan的基本思路是：  
1.任选一个点为根节点，从根节点开始。  
2.遍历该点u所有子节点v，并标记这些子节点v已被访问过。  
3.若是v还有子节点，返回2，否则下一步。  
4.合并v到u上。  
5.寻找与当前点u有询问关系的点v。  
6.若是v已经被访问过了，则可以确认u和v的最近公共祖先为v被合并到的父亲节点a。  

Tarjan的伪代码：  
```cpp
Tarjan(u)//marge和find为并查集合并函数和查找函数
{
    for each(u,v)    //访问所有u子节点v
    {
        Tarjan(v);        //继续往下遍历
        marge(u,v);    //合并v到u上
        标记v被访问过;
    }
    for each(u,e)    //访问所有和u有询问关系的e
    {
        如果e被访问过;
        u,e的最近公共祖先为find(e);
    }
}
```  
这个算法的执行过程参考[这个链接](https://www.cnblogs.com/JVxie/p/4854719.html)，有手动模拟  
算法的模板参考[洛谷P3379题解](https://www.luogu.com.cn/blog/Otto-Apocalypse/solution-p3379)   

[LeetCode236：二叉树的最近公共祖先](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/)    
需要用unordered_map代替数组，因为有负的下标（二叉树节点值唯一但是有负数）  
题解如下：  
```cpp
#define fu(i,r,t) for(int i=r;i<=t;i++)
class Solution {
public:
    unordered_map<int, int> fa;
    unordered_map<int, TreeNode*> mapp;
    TreeNode* pp;
    TreeNode* qq;
    int lca;
    int cnt = 0;
    int find(int x) {
        return (fa[x] == x) ? x : (fa[x] = find(fa[x]));
    }
    void tarjan(TreeNode* root) {
        mapp[root->val] = root;
        fa[root->val] = root->val;
        if (root->left != nullptr) {
            tarjan(root->left);
            fa[root->left->val] = root->val;
        }
        if (root->right != nullptr) {
            tarjan(root->right);
            fa[root->right->val] = root->val;
        }
        if (pp->val == root->val)
            lca = find(qq->val);
        if (qq->val == root->val)
            lca = find(pp->val);
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        pp = p;
        qq = q;
        tarjan(root);
        return mapp[lca];
    }
};
```  

[洛谷模板题](https://www.luogu.com.cn/problem/P3379)  
模板题题解：  
```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
#define fu(i,r,t) for(int i=r;i<=t;i++)
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(V) V.begin(),V.end()
#define print(i) cout<<(i)<<endl
#define ll long long
#define ull unsigned long long
int n;
int m, root;
int cnt = 0;
int qcnt = 0;
struct EDGE {
    int next, to;
    EDGE(int ni, int ti) {
        next = ni;
        to = ti;
    }
};
vector<EDGE> edge;
vector<EDGE> qedge;
int head[500001];
int qhead[500001];   // 存储查询关系
int lca[500001];     // 存储查询结果（下标单位：对）
bool visit[500001];
int fa[500001];
void addedge(int u,int v) //起点，终点，权值
{
    cnt++;
    edge.emplace_back(head[u], v);
    head[u]=cnt;               // 起点 u 的第一条边
}
void addqedge(int u,int v) //起点，终点，权值
{
    qcnt++;
    qedge.emplace_back(qhead[u], v);
    qhead[u]=qcnt;               // 起点 u 的第一条边
}
int find(int x) {
    return (fa[x] == x) ? x : (fa[x] = find(fa[x]));
}
void tarjan(int u) {
    visit[u] = true;
    fa[u] = u;
    for (int i = head[u]; i; i = edge[i].next) {
        if (!visit[edge[i].to]) {
            tarjan(edge[i].to);
            fa[edge[i].to] = u;
        }
    }
    for (int i = qhead[u]; i; i = qedge[i].next) {
        if (visit[qedge[i].to]) {
            lca[(i % 2 == 1) ? ((i + 1) / 2) : (i / 2)] = find(qedge[i].to);
        }
    }
}
signed main() {
    IOS
    edge.emplace_back(0, 0);
    qedge.emplace_back(0, 0);
    cin >> n >> m >> root;
    int k, l;
    fu (i, 1, n - 1) {
        cin >> k >> l;
        // 采用双向图是因为不能保证根节点第一个出现，例如根节点是4，假如输入是2 4，则无法从根节点2走到节点2
        addedge(k, l);
        addedge(l, k);
    }
    fu (i, 1, m) {
        cin >> k >> l;
        // 采用双向图是因为不能保证在tarjan函数的查询部分中谁先被查询到
        addqedge(k, l);
        addqedge(l, k);
    }
    tarjan(root);
    fu (i, 1, m) {
        print(lca[i]);
    }
    return 0;
}
```  
