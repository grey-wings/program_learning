[题目链接](https://leetcode-cn.com/problems/implement-strstr/)  

参考：  
https://www.cnblogs.com/dusf/p/kmp.html  
https://blog.csdn.net/v_july_v/article/details/7041827  

## 一、关于kmp算法的一些理解  
### 1. i和j指针的定义  
i指向主串中的某个字符，j指向模式串中的某个字符。  
![](https://images0.cnblogs.com/blog/416010/201308/17083647-9dfd3e4a709c40dd98d9817927651960.png)  
如果i和j指向的字符相等，那么i和j都后移。  
![](https://images0.cnblogs.com/blog/416010/201308/17083659-e6718026bf4f48a0be2d5d6076be4c55.png)  

### 2. 当i和j指向的字符不匹配时，j移动到哪里？（下标从0开始）
当匹配失败时，j要移动的下一个位置k，存在着这样的性质：最前面的k个字符和j之前的最后k个字符是一样的。  
即k = next[j]
即P[0 ~ k-1] == P[j-k ~ j-1]  
关于这个公式的理解：  
![](https://images0.cnblogs.com/blog/416010/201308/17084056-66930855432b4357bafbf8d6c76c1840.png)  
举例示意：  
1.
![](https://images0.cnblogs.com/blog/416010/201308/17083912-49365b7e67cd4877b2f501074dae68d2.png)  
最前面的1个字符和最后面的1个字符一样，所以移动到第1位。  
![](https://images0.cnblogs.com/blog/416010/201308/17083929-a9ccfb08833e4cf1a42c30f05608f8f5.png)  
2.  
![](https://images0.cnblogs.com/blog/416010/201308/17084030-82e4b71b85a440c5a636d57503931415.png)  
最前面的2个字符和最后面的2个字符一样，所以移动到第2位。  
![](https://images0.cnblogs.com/blog/416010/201308/17084037-cc3c34200809414e9421c316ceba2cda.png)  ']

#### 特殊地，当j == 0时，i后移一位。

### 3. Next数组
#### 计算某个字符对应的next值，就是看这个字符之前的字符串中有多大长度的相同前缀后缀。  
比如：  
![](https://img-blog.csdn.net/20140728110939595)  
这里的“最大长度值”，就是最长相等前后缀的长度。  
已知next[0]到next[j]，如何求出next[j + 1]?  
#### 1. 当j为0时，不匹配  
![](https://images0.cnblogs.com/blog/416010/201308/17084258-efd2e95d3644427ebc0304ed3d7adefb.png)  
j已经在最左边了，不可能再移动了，这时候要应该是i指针后移。所以next[0]=-1  
#### 2. j为1，不匹配  
![](https://images0.cnblogs.com/blog/416010/201308/17084310-29f9f8dbb6034151a383e7ccf6f5583e.png)  
j只能移到0，即next[1]=0  
#### 3. 匹配的情况
这里next[j] == k  
![](https://images0.cnblogs.com/blog/416010/201308/17084327-8a3cdfab03094bfa9e5cace26796cae5.png)![](https://images0.cnblogs.com/blog/416010/201308/17084342-616036472ab546c082aa991004bb0034.png)  
当P[k] == P[j]时，有next[j + 1] == next[j] + 1  
#### 4. 一般不匹配情况  
当P[k] != P[j]时  
要往前找一个k'，使得P[k'] = P[j]，并且P[0 ~ k'] = P[j-k' ~ j]  
用下面这个图来辅助理解。  
![](https://img-blog.csdn.net/20150812214857858)  
当P[k] != P[j]时：
由上面第3点得，图中两个大括号括起来的长度为k的区域是相等的。  
在图中画出黄色的P[next[k]]的位置，则蓝色的四块相等。  
如果P[next[k]] == P[j]，那么P[0 ~ j]的最长相等前后缀的长度就是next[k] + 1，否则就继续往前找。  
如果找不到这个k'，那么next[j + 1]就等于0  

## 二、题解
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
    static void getNext(const string& s, int* next){
        // 计算某个字符对应的next值，就是看这个字符之前的字符串中有多大长度的相同前缀后缀。
        // 默认next长度大于2，在下面的程序中长度为1和0的情况已经被处理了。
        next[0] = -1;next[1] = 0;
        // 因为next[j]求的是0 ~ (j-1)之间的字符串的最长相等前后缀
        // 所以i从1循环到s.length() - 1
        for (int i = 1;i < s.length() - 1;i++){
            int k = next[i];
            while (k >= 0 and s[k] != s[i])
                k = next[k];
            next[i + 1] = k + 1;
        }
    }
    int strStr(string haystack, string needle) {
        if (needle == haystack)
            return 0;
        if (needle.length() >= haystack.length())
            return -1;
        if (needle.length() == 0)
            return 0;
        if (needle.length() == 1){
            int x = haystack.find(needle[0]);
            return (x == std::string::npos) ? -1 : x;
        }
        int next[needle.length()];
        getNext(needle, next);
        int i = 0, j = 0;
        while (i < haystack.length() and j < needle.length()){
            if (haystack[i] == needle[j]){
                i++;
                j++;
            }
            else if (j == 0)
                i++;
            else
                j = next[j];
        }
        if (j == needle.length())
            return i - j;
        else
            return -1;
    }
};
int main() {
    string haystack, needle;
    cin >> haystack >> needle;
    Solution sl;
    cout << sl.strStr(haystack, needle);
    return 0;
}
```
关于结束时的判定  
![](https://user-images.githubusercontent.com/74122331/125785968-16364db2-41e3-48ed-87ec-9b9af70eacec.png)  
![](https://user-images.githubusercontent.com/74122331/125786223-c703e2e8-6738-481c-8120-698a55365b7e.png)  
![image](https://user-images.githubusercontent.com/74122331/125788582-09970df0-05e6-45a8-b1cf-a3c1fba9778c.png)  

