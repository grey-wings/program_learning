[题目链接](https://leetcode-cn.com/problems/water-and-jug-problem/)  

最大公约数求法：
```cpp
int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}
```  
时间复杂度为O(log n)  

最小公倍数记为lcm，有**gcd(a, b) * lcm(a, b) == a * b**  
裴蜀定理的内容为：  
![image](https://user-images.githubusercontent.com/74122331/153813059-940bdb24-695a-40dc-9667-1660d0b22e3f.png)  

证明见[oiWiki](https://oi-wiki.org/math/number-theory/bezouts/)  
  
