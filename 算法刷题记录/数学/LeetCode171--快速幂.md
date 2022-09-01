[题目链接](https://leetcode-cn.com/problems/excel-sheet-column-number/)  

快速幂：  
设要求a^b  
将b分解为二进制，例如当b为11时，b = (1011)2  
则a^b = a^(2^3) * a^(2^1) * a^0;
可以看到，这个分解式中的每一个指数都是2的幂，即可以通过a不断平方得到，这样减少了计算次数，复杂度为O(log n)  

### 实际操作时要开long long甚至高精度避免见祖宗，这里因为数据范围是int以内所以不改。
```cpp
class Solution {
public:
    int ksm(int x){
        long long a = 1, k = 26;
        while (x > 0){
            if (x & 1)
                a *= k;
            k *= k;
            x >>= 1;
        }
        return a;
    }
    int titleToNumber(string columnTitle) {
        int ans = 0;
        reverse(all(columnTitle));
        for (int i = 0;i < columnTitle.length();i++){
            ans += (columnTitle[i] - 'A' + 1) * ksm(i);
        }
        return ans;
    }
};
```

## 快速幂取模  
(a*b) mod c = ((a mod c)*(b mod c)) mod c  
那么根据上面的定理可以推导出另一个定理：  
(a^b) mod c = (a mod c)^b mod c  
代码如下：  
```cpp
int ksm(int n, int index, int mod) {
        int k = n;
        int ans = 1;
        while (index > 0) {
            if (index & 1)
                ans = ans * k % mod;
            k = k * k % mod;
            index >>= 1;
        }
        return ans;
    }
```
