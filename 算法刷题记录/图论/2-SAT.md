# 定义   
有n个集合，每个集合里有两个元素且必须选一个，再给出若干条限制条件，比如选了i元素就不能j元素，求可行的选择方案。  
对于一串布尔变量的方程，可以把每个变量用2个点表示。x0表示这个点状态为反，x1表示这个点状态为正  
如果选A必须选B，那么就连一条有向边，从A1->B1  
如果选A就不能选B，那么就连一条有向边，从A1->B0  
这样构成一个图，如果图中出现了一个强连通分量，那么这个强连通分量的每一个点都必须选。如果点x1与x0在同一个强连通分量中，那么这个分量不可行。 
输出方案：  
因为A连B表示选A必须选B，所以A的拓扑序肯定大于B  
注意这里是选A就必须选B，但是选B不一定选A  
所以对于每个点的两种状态，可以选拓扑序大的，舍弃掉另一个（选一个就不能选另一个了）  
每个点都判断与对立点谁的拓扑序大  
注意这里可以不用再搞一遍拓扑排序，因为Tarjan求强连通分量每个点所在的强连通分量编号可以代替拓扑序  
编号和拓扑序是相反的，即要每两对点找编号小的  
输出每个点状态就行了  
下面有一些基本关系：  
A,B不能同时存在：A->B',B->A'  
A,B必须同时存在：A->B,A'->B'  
A,B必须存在其中一个：A'->B,B'->A  
A,B不能同时存在：A->B',B->A'  
A不能存在：A->A'  

代码如下：  
```cpp
#include <bits/stdc++.h>
using namespace std;
//#define int long long
#define fu(i,r,t) for(int i=r;i<=t;i++)
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define all(V) V.begin(),V.end()
#define print(i) cout<<(i)<<endl
#define int long long
#define ll long long
#define ull unsigned long long

#define N 2000005
#define M 2000010
struct Edge {
    int next, to;
//    int w;
//    Edge(int next, int to, int w) {
//        this->next = next;
//        this->to = to;
//        this->w = w;
//    }
}edge[M];
int n, m;
int head[N];
int cnt = 1, timer = 0, num = 0;
// timer表示u点时第几个被dfs到的，num表示是第几个连通分量
stack<int> s;
bool instack[N];
int dfn[N], low[N], belong[N];
int result[N];
// belong代表每个点所属的强连通分量的编号
void addedge(int u, int v, int w = 1) {
    cnt++;
    edge[cnt].next = head[u];
//    edge[cnt].w = w;
    edge[cnt].to = v;
    head[u] = cnt;
}
void tarjan(int u) {
    low[u] = dfn[u] = ++cnt;
    int v;
    s.push(u);  // 未处理的结点入栈
    instack[u] = true;
    for (int i = head[u]; i; i = edge[i].next) {
        v = edge[i].to;
        if (!dfn[v]) {
            // 如果v未被访问，那么访问它更新low[u]
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (instack[v]) {
            // 如果v已被访问并且在栈中，就用low[v]更新low[u]
            low[u] = min(low[u], low[v]);
        }
    }
    if (dfn[u] == low[u]) {
        // 搜到了强连通分量
        num++;
        v = 0;
        do {
            v = s.top();
            s.pop();
            instack[v] = false;
            belong[v] = num;  // 强连通分量编号可以代替拓扑序，顺序相反
        } while (u != v);  // 将u和u之后入栈的结点全部出栈，这些都是u的搜索树上的子树，同属于一个强连通分量
    }
}
signed main() {
    IOS
    cin >> n >> m;
    int a, b, k, l;
    fu (i, 1, m) {
        cin >> a >> k >> b >> l;
        // 结点1~n表示a[i] = 0, n + 1 ~ 2n表示a[i] = 1;
        addedge((k ? a : a + n), (l ? b + n : b));
        addedge((l ? b : b + n), (k ? a + n : a));
    }
    fu (i, 1, 2 * n) {
        if (!dfn[i])
            tarjan(i);
    }
    fu (i, 1, n) {
        if (belong[i] == belong[i + n]) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";
//    print("POSSIBLE");
//    fu (i, 1, n) cout << result[i] << ' ';
    return 0;
}
```
