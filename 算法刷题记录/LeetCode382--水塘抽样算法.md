[题目链接](https://leetcode-cn.com/problems/linked-list-random-node/)  

在一个很大的集合中保证随机地抽取一个样本。由于题目中是链表，因此常规的做法：遍历链表，存储所有的值在随机取需要O(n)的空间复杂度，O(1)的查询时间复杂度和O(n)的建立时间复杂度。在某些实际问题上，比如几个T的文件中随机取一个，那么会消耗大量的内存。  
水塘抽样算法的时间复杂度是O(n)（每次抽样），空间复杂度为O(1)，具体操作如下：
![image](https://user-images.githubusercontent.com/74122331/151315488-81cf24f6-5ca1-4db0-9d71-0e3612d575d9.png)
