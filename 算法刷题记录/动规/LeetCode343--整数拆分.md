[题目链接](https://leetcode-cn.com/problems/integer-break/submissions/)  

用动态规划解决问题。  
最初的考虑是，可以设一个二维dp数组dp[i][j]，表示将i拆成j个数的最大乘积。
当i被拆成j个数时，可以看成一个小于i的数i - c被拆成j - 1个数的情况下，再乘上c来得到。  
那么前面i - c被拆成j - 1个数的情况也需要取最大值，就是dp[i - c][j - 1]  
那么dp[i][j]的求法就是：  
dp[i][j] = max(dp[i - c][j - 1] * c), for c = 1 to i - 1（这个公式自己想的，可能有错或不完善，做过试验之前别用）  
那么这样看来j这一维是可以省略的。  
那么将dp数组设为dp[i]，表示拆分第i个数得到的最大乘积。  
初值就是dp[2] = 1;  
dp[1]是没有意义的，但是为了后面写循环方便，就把他设成1本身。
公式推导如下：  
对于一个数i，先把他拆成两个数j和i - j  
因为i可以拆分成多个数，因此可以把i - j继续拆分，不拆j是因为后面会看到j是一个循环变量，没有拆的必要。  
每一个j对应i的一种拆分方法，求出这种方法的最大值，就是求dp[i - j] * j  
然后再所有方法中求出最大值用来更新dp[i]  
用一个二重循环更新dp数组：  
for i = 3 to n
    dp[i] = max(dp[i - j] * j), for j = 1 to i - 1  
然而这个公式实际上是错的  
对于dp[4]，很显然可以得到它等于4  
但是用上面的循环来求，j = 1时，dp[i - j] * j是dp[3] * 1 = 2；j = 2时是dp[2] * 2 = 2；j = 3时是dp[1] * 3 = 3；  
因为对于dp[i]中的数i，必须被拆分成两个以上的数。而对于某些数，它的拆分的乘积并不一定大于它本身。比如dp[2] < 2  
假设对于一种拆分方案j，i - j > dp[i - j]  
那么就应该把i拆成j和i - j的乘积而不是j和i - j的拆分的乘积。比如上例中dp[4]在j = 2这个方案中的最大值是2 * 2，而不是2 * (2的拆分)也就是2 * 1 * 1  
因此更新公式改为  
for i = 3 to n
    dp[i] = max(max(i - j, dp[i - j]) * j), for j = 1 to i - 1  
代码如下：  
```java
class Solution {
    private int getmax(int a, int b, int c) {
        return Math.max(a, Math.max(b, c));
    }
    public int integerBreak(int n) {
        int[] dp = new int[n + 1];
        dp[1] = 1;
        dp[2] = 1;
        int max;
        for (int i = 3; i <= n; i++) {
            max = -1;
            for (int j = 1; j < i; j++)
                max = getmax(max, dp[i - j] * j, (i - j) * j);
            dp[i] = max;
        }
        return dp[n];
    }
}
```  
