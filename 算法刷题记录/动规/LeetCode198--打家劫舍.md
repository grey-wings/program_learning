[题目链接](https://leetcode-cn.com/problems/house-robber/)  

不能偷两个相邻的房屋。  
用dp[i]来表示走到第i个房屋时，最多能偷的钱。  
每个房屋有两种选择：偷或不偷。如果偷了，dp[i] = dp[i - 2] + nums[i]，因为不能偷第i - 1个房屋。  
如果没偷，那么dp[i] = dp[i - 1]  
每个dp[i]最早是由dp[i - 2]开始算的，因此初始化dp[0]和dp[1].  
代码如下：  
```java
class Solution {
    public int rob(int[] nums) {
        if (nums.length == 1)
            return nums[0];
        int[] dp = new int[nums.length];
        dp[0] = nums[0];
        dp[1] = Math.max(nums[0], nums[1]);
        for (int i = 2; i < nums.length; i++) 
            dp[i] = Math.max(dp[i - 2] + nums[i], dp[i - 1]);
        return dp[nums.length - 1];
    }
}
```
