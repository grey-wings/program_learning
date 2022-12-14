## kruskal重构树  
原来的kruskalkruskal算法就是用并查集实现的，但当我们使用kruskalkruskal重构树的时候，对于每次找出的不同的两个连通块的祖先，我们都新建一个点作为两个祖先的父亲，并将当前边的边权转化为新点的点权。然而，路径压缩的时候会让我们丢失这种辛辛苦苦创造的树的形状。。。因此我们需要在使用并查集维护连通性的同时使用二叉树来维护树的形状。这样维护出来的树就是kruskal重构树。  
### 重构树性质
1.原图中的点在重构树中一定是叶子节点，其余节点都代表了一条边的边权。  
2.重构树中的点数是2n−1且以2n−1号点为根节点    
3.如果边权按照从小到大排序建立重构树，重构树的点权是一个大根堆，反之小根堆
4.对于一个x和一个值v。从x出发只经过≤v的边能到达的点集 = x的祖先节点中深度最小的点权≤v的点z的子树中的原来的点集。  
5.原树两点间的的最大边权就是kruskal重构树上两点的LCA的权值。  

解法：若一个点能通过一条路径到达，那么我们走最小生成树上的边也一定能到达该节点。  

### 补充：树上倍增  
对于在树上查找某点的祖先，如果简单的查找时间复杂度是o(n)，那么，我们可以通过倍增算法优化这个时间复杂度，将每次跳一个点变成，每次跳2的i次方个点，也就是倍增优化这个过程，将时间复杂度变为o(logn)。  
如何进行倍增？  
首先我们需要进行一遍dfs初始化，处理出每个点的深度。根据深度，初始化fa[now][i]，fa数组存的是now节点的2^i倍的祖先（eg.父亲是1倍祖先，祖父是2倍祖先）。  
对于一个查询(i, k)，代表查询结点i的第k代祖父。   
![](https://www.zhihu.com/equation?tex=%28i%2C+k%29%3D%28%28i%2C2%5Ej%29%2Ck-2%5Ej%29%2Cj%E6%98%AF%E4%BD%BF%E5%BE%972%5Ej%3C%3Dk%E7%9A%84%E6%9C%80%E5%A4%A7%E5%80%BC)  
