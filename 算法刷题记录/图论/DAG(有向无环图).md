# 一、理论  
如果一个有向图无法从任意顶点出发经过若干条边回到该点，则这个图就是有向无环图，具体如下图所示。  
![](http://www.itcast.cn/files/image/202012/20201229164751920.jpg)  
能拓扑排序的图，一定是有向无环图；有向无环图一定能拓扑排序。  
判断一个图是否是DAG可以用拓扑排序。  
一些定义：  
1.在一个 DAG（有向无环图） 中，我们将图中的顶点以线性方式进行排序，使得对于任何的顶点**u**到**v**的有向边 **(u, v)**, 都可以有**u**在**v**的前面。  
2.给定一个DAG，如果从i到j有边，则认为j依赖于i。如果i到j有路径（i可达j），则称j间接依赖于i。拓扑排序的目标是将所有节点排序，使得排在前面的节点不能依赖于排在后面的节点。  

拓扑排序使用**Kahn算法（BFS）**：  
初始状态下，集合S装着所有入度（以一个顶点v为终点的边的条数称为该节点的入度）为0的点，L是一个空列表。  
从S中随意取出一个点u放入L，然后将u的所有边(u, v1)、(u, v2)、(u, v3)删除，如果删除边(u, v)后点v的入度变为0，则将v放入L中。 
不断重复如上过程，直到S为空。此时如果图中存在任何边，则说明原图中有环。如果没有，L即为拓扑排序的结果。  

时间复杂度为O(E + V)  
代码实现([参考链接](https://blog.csdn.net/qq_40859951/article/details/84832797))：
```cpp
int in[N];//节点入度
int path[N];//存储路径
vector<int> G[N];//G[i]表示i节点所指向的所有其他点
void Topsort()//拓扑排序
{
    priority_queue< int,vector<int>,greater<int> > Q;//最小值先出列
    int cnt=0;//记录可拆解的点数目
    for(int i=1;i<=n;i++)//枚举编号从1到n的点
        if(in[i]==0)//入度为0，入列
            Q.push(i);
 
    while(!Q.empty()) {
        int x=Q.top();//队列首元素
        Q.pop();
 
        path[++cnt]=x;//存储可拆点
        for(int i=0;i<G[x].size();i++){
            int y=G[x][i];
            in[y]--;//入度减一
 
            if(in[y]==0)//入度为0，出列
                Q.push(y);
        }
    }
}
```
如果需要求字典序最大/最小的拓扑排序，则把队列换成优先队列即可。  
如果不需要拓扑排序后的结果，那么可以不需要结果集列表，只需要统计被删除的节点的数量即可，如果该数量等于DAG图的节点数，那么DAG图可以被拓扑排序。  

# 二、题目  
## 1.[leetcode 207](https://leetcode-cn.com/problems/course-schedule/)  
拓扑排序检验DAG  
代码如下：  
```cpp
class Solution {
public:
    int n;
    int in[100001];//节点入度
    vector<int> g[100001];//G[i]表示i节点所指向的所有其他点
    bool Topsort()//拓扑排序
    {
        int cnt = 0;
        queue<int> q;
        for(int i = 0;i < n;i++)
            if(in[i] == 0)        //入度为0，入列
                q.push(i);

        while(!q.empty()) {
            int x=  q.front();    //队列首元素
            q.pop();
            cnt++;
            for(int y : g[x]){
                in[y]--;          //入度减一

                if(in[y] == 0)    //入度为0，出列
                    q.push(y);
            }
        }
        return cnt == n;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        n = numCourses;
        memset(in, 0, sizeof(in));
        for (auto v : prerequisites) {
            in[v[0]]++;
            g[v[1]].push_back(v[0]);
        }
        return Topsort();
    }
};
```  

## 2.[leetcode 210](https://leetcode-cn.com/problems/course-schedule-ii/submissions/)   
输出任意一种拓扑排序。  
只需要将弹出队列的点加入结果向量即可。  
代码如下：  
```cpp
class Solution {
public:
    int n;
    int in[100001];//节点入度
    vector<int> g[100001];//G[i]表示i节点所指向的所有其他点
    vector<int> ans;
    bool Topsort()//拓扑排序
    {
        int cnt = 0;
        queue<int> q;
        for(int i = 0;i < n;i++)
            if(in[i] == 0)        //入度为0，入列
                q.push(i);

        while(!q.empty()) {
            int x=  q.front();    //队列首元素
            q.pop();
            cnt++;
            ans.push_back(x);
            for(int y : g[x]){
                in[y]--;          //入度减一

                if(in[y] == 0)    //入度为0，出列
                    q.push(y);
            }
        }
        return cnt == n;
    }
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        n = numCourses;
        memset(in, 0, sizeof(in));
        for (auto v : prerequisites) {
            in[v[0]]++;
            g[v[1]].push_back(v[0]);
        }
        vector<int> b;
        return (Topsort() ? ans : b);
    }
};
```  
