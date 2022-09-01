# 一、dfs概述  
本部分参考链接：[oiWiki](https://oi-wiki.org/graph/dfs/)  
DFS 最显著的特征在于其 递归调用自身。同时与 BFS 类似，DFS 会对其访问过的点打上访问标记，在遍历图时跳过已打过标记的点，以确保 每个点仅访问一次。符合以上两条规则的函数，便是广义上的 DFS。  
具体地说，DFS 大致结构如下：  
```cpp
DFS(v) // v 可以是图中的一个顶点，也可以是抽象的概念，如 dp 状态等。
  在 v 上打访问标记
  for u in v 的相邻节点
    if u 没有打过访问标记 then
      DFS(u)
    end
  end
end
```  
该算法通常的时间复杂度为O(n + m)，空间复杂度为O(n)，其中n表示点数,m表示边数。注意空间复杂度包含了栈空间，栈空间的空间复杂度是O(n)的。在平均O(1)遍历一条边的条件下才能达到此时间复杂度，例如用前向星或邻接表存储图；如果用邻接矩阵则不一定能达到此复杂度。

以[链式前向星](https://github.com/grey-wings/cpp_learning_process/blob/main/%E4%B8%80%E4%BA%9B%E8%87%AA%E5%B7%B1%E5%86%99%E7%9A%84%E5%9E%83%E5%9C%BE%E9%A2%98/%E5%9B%BE%E8%AE%BA/%E5%9B%BE%E7%9A%84%E8%A1%A8%E7%A4%BA.md)为例（与上面的模板一一对应）：  
```cpp
// C++ Version
void dfs(int u) {
  vis[u] = 1;
  for (int i = head[u]; i; i = edge[i].next) {
    if (!vis[edge[i].to]) {
      dfs(edge[i].to);
    }
  }
}
```   
示例：  
![](https://cdn.luogu.com.cn/upload/pic/43957.png)  
输入第一个点：edge[1].next = head[1]; edge[1].to = 2;head[1] = 1;    
输入第二个点：edge[2].next = head[1]; edge[2].to = 3;head[1] = 2;  
输入第三个点：edge[3].next = head[1]; edge[3].to = 4;head[1] = 3;表示当前第1个点的边集合被遍历时的第一条边是edge[3];edge[3]被遍历完以后的下一条边是edge[2]，再后面是edge[1]  
输入第四个点：edge[4].next = head[2]; edge[4].to = 3;head[2] = 4;  
比如从1号顶点开始遍历：  
先把1号顶点标记为遍历过，然后进入for循环：    
i的初值是head[1] = 3，edge[3].to=4，即4号顶点，没有遍历过，因此进入dfs(4)  
标记4号顶点，head[4] = 0，则for的第二个表达式为假，不执行循环，退出dfs(4)，回到dfs(1)  
i的值变为edge[3].next = 2；edge[2].to = 3，即3号顶点，没有遍历过，进入dfs(3)  
标记3号顶点，head[3] = 0，退出  
i的值变为edge[2].next = 1；edge[1].to = 2，即2号顶点，没有遍历过，进入dfs(2)  
标记2号顶点。至此，所有顶点都被遍历完，剩下的遍历中都会因为已经标记过而不执行新的dfs函数。  

## 欧拉回路  
```cpp
void Euler(int u) {
    int v;
    for (v = 0; v < n; v++) {
        if (grapg[u][v] == 1) {
        graph[u][v] = graph[v][u] = 0;
        Euler(v);
        path[pc++] = v;
        }
    }
}
// 调用代码
Euler(s);
path[pc++] = s;
```  
对于下图：  
![image](https://user-images.githubusercontent.com/74122331/162561502-3673a8b2-67ce-4a6e-841c-00eb01148446.png)
path的值为：1 5 4 3 2 8 7 6 2 1  
