## 一、图的bfs概述  

参考链接：[oiWiki](https://oi-wiki.org/graph/bfs/)  

bfs伪代码：  
```cpp
bfs(s) {
  q = new queue()
  q.push(s), visited[s] = true
  while (!q.empty()) {
    u = q.pop()
    for each edge(u, v) {
      if (!visited[v]) {
        q.push(v)
        visited[v] = true
      }
    }
  }
}
```  

