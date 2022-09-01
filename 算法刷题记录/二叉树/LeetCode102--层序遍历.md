[题目链接](https://leetcode-cn.com/problems/binary-tree-level-order-traversal/)  
[算法介绍链接](https://www.cnblogs.com/hapjin/p/5409921.html)  

层序遍历可以用队列来实现，方法如下：  
先把树的根节点加入队列  
![image](https://user-images.githubusercontent.com/74122331/128623292-c9a0b75b-3446-4b92-afb1-405b3c888464.png)  
此时队列中有：[1]  
然后循环直到队列为空：  
弹出队列的第一个值，然后把他的儿子插入队列  
示例：弹出1后加入2、3，此时队列中有：[2, 3]  
然后弹出2，加入2的儿子4、5，此时队列中有：[3, 4, 5]  
然后弹出3，加入3的儿子6、7，此时队列中有：[4, 5, 6, 7]  
后面这四个节点没有子节点，则直接逐个弹出。  

代码如下（转自上面的[算法介绍链接](https://www.cnblogs.com/hapjin/p/5409921.html)）：
```java
private void levelTraverse(BinaryNode<T> root){
    if(root == null)
        return;
    Queue<BinaryNode<T>> queue = new LinkedList<>();//层序遍历时保存结点的队列
    queue.offer(root);//初始化
    while(!queue.isEmpty()){ 
        BinaryNode<T> node = queue.poll();
        System.out.print(node.element + " ");//访问节点
        if(node.left != null) 
            queue.offer(node.left);
            if(node.right != null) 
                queue.offer(node.right);
    }
}
```  
这样的算法还不足以解决LeetCode上的这个问题，因为原题要求每一层的遍历结果用一个容器装起来。  
为了解决这个问题，可以在前面层序遍历步骤中加入“记录队列长度”的步骤。  
方法修改如下：
先把树的根节点加入队列  
此时队列中有：[1]  
然后记录当前队列的长度l = 1；  
弹出1，这时l--，l == 0，输出数组[1]，然后将儿子2、3加入队列，l = 2；
然后弹出2，l--，第二个数组加入值2，然后将儿子4、5加入队列；  
然后弹出3，l--，第二个数组加入3，然后将儿子6、7加入队列。这时l == 0，因此输出第二个数组，令l = 4（第三层的数字个数）  
直到遍历完所有节点。  
代码如下：  
```java
class Solution {
    public List<List<Integer>> levelOrder(TreeNode root) {
        Queue<TreeNode> q = new LinkedList<>();
        q.offer(root);
        TreeNode t;
        int l = 1;
        List<List<Integer>> list = new ArrayList<>();
        if (root == null)
            return list;
        List<Integer> ls = new ArrayList<>();
        while (!q.isEmpty()) {
            t = q.poll();
            ls.add(t.val);
            l--;
            if (t.left != null)
                q.offer(t.left);
            if (t.right != null)
                q.offer(t.right);
            if (l == 0) {
                List<Integer> ll = new ArrayList<>(ls);
                list.add(ll);
                ls.clear();
                l = q.size();
            }
        }
        return list;
    }
}
```  

