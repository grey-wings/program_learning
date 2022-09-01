[题目链接](https://leetcode-cn.com/problems/combinations/)  

本文参考[代码随想录](https://github.com/youngyangyang04/leetcode-master)关于回朔算法的pdf。  
回溯算法一般需要用到递归和循环，直接理解比较困难，可以用树形结构来理解。  
eg. 四个数取两个数的组合   
![image](https://user-images.githubusercontent.com/74122331/131249641-8f297423-ae53-46a8-b13e-1b569e49a92d.png)
回溯采用的是递归+循环的方式。递归需要一个退出条件，这里就是这颗树搜到叶节点的时候；循环是指在同一层里面遍历。  
总结一下，就是递归完成纵向遍历，循环完成横向遍历。  
回溯模板的框架如下：  
![image](https://user-images.githubusercontent.com/74122331/131249557-287102a0-4db7-48e4-b46a-49949ac67591.png)
这个框架在初学时没必要理解，可以先看例题，结合例题的代码理解这个结构。  

根据LeetCode第77题介绍回溯算法  
以样例为例，在1-4四个数中取两个  
这里直接借用[代码随想录](https://github.com/youngyangyang04/leetcode-master)的图：  
![image](https://user-images.githubusercontent.com/74122331/131249880-5f43b110-da43-4f5b-83a9-6de01daa13b6.png)
然后根据[代码随想录](https://github.com/youngyangyang04/leetcode-master)提供的“回溯三部曲”分析题目：  
**1.递归函数的返回值以及参数  
2.回溯函数终⽌条件  
3.单层搜索的过程**  
返回值显然是符合条件的组合，需要一个Integer型的list变量path（用于存储当前的路径）和一个list型的list变量a（用于存储答案），这里为了方便起见，全部放在全局变量中，返回值取void；参数首先需要n（代表取数的范围）和k（取数的个数），这两个参数在代码随想录中是作为函数的参数的，但是也可以放到全局变量中；还需要一个startIndex，因为每次向后搜索，能取的数范围都会变小，因此用startIndex来体现这一点。  
终止条件则是当前选择的路径已经有k个数的时候。  
单层搜索过程就是从startIndex开始遍历，一直到n结束（或者剪枝所要求的退出位置）  

还有一个问题是剪枝。  
考虑如下的情况（图来自代码随想录）：
![image](https://user-images.githubusercontent.com/74122331/131251061-d871e1e0-171f-4ff9-8630-a55b6643d1dc.png)
在这棵树的第二层中，如果从2开始选，就是剩下3个数备选，不能满足4个数的条件，所以这条路根本不用去试。同理，从3开始选只剩下两个备选数，因此也不用尝试。  
那么就加一个对剩下的数是否满足k个的判断。  
那么，发生剪枝行为时，每个for循环的结束位置i，满足i~n的数的个数刚好等于k - path.size()，也就是n - i + 1 = k - path.size()，即循环到n - (k - path.size()) + 1  

在写代码时还会碰到一个问题：在将path添加至a的时候，不能直接用a.add(path)，否则a里面的数据会随path的改变而改变，这里可以用深拷贝，但是更简单的方法是a.add(new ArrayList<Integer>(s))  
代码如下（这里的path用s来代替了）：  
```java
class Solution {
    int nn, kk;
    List<List<Integer>> a = new ArrayList<>();
    List<Integer> s = new ArrayList<>();
    private void f(int startIndex) {
        if (s.size() == kk) {
            a.add(new ArrayList<Integer>(s));
            return;
        }
        for (int i = startIndex; i <= nn - (kk - s.size()) + 1; i++) {
            s.add(i);
            f(i + 1);
            s.remove(s.size() - 1);
        }
    }
    public List<List<Integer>> combine(int n, int k) {
        nn = n;
        kk = k;
        f(1);
        return a;
    }
}
```
