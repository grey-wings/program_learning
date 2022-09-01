[题目链接](https://leetcode-cn.com/problems/majority-element/)  

[摩尔投票法解析](https://www.zhihu.com/question/49973163)  

基本思想是两个不同的数1对1抵消，最后剩下的一个数就是众数。  
可以类比为多个国家战争，1对1同归于尽，不管某个特定的人和哪个国家的人打，只要不打自己人，最后获胜的一定是人最多的国家。  
在投票中，要得出选哪个候选人的人数最多，可以这么操作:  
先设一个major（随便选一个候选人，就设为num[0]），和一个count（当前选这个候选人的个数） 
然后遍历这个数组，假设当前major已经有一个值，遍历到了某个选民。  
如果下一个人选了major，那么count++;  
如果下一个人选的不是major，那么就和选major的同归于尽，即major--;  
如果减完以后major等于0，说明已经遍历过的选民全部同归于尽，就可以把这部分已经遍历过的数组去掉。  
那么major就选下一个遍历到的数组值。  

代码如下：  
```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int major = nums[0], count = 1;
        for (int i = 1;i < nums.size();i++){
            if (count == 0)
                major = nums[i];
            if (major == nums[i])
                count++;
            else
                count--;
        }
        return major;
    }
};
```
