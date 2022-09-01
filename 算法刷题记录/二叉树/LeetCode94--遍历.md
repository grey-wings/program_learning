相关题目链接：  
[前序遍历](https://leetcode-cn.com/problems/binary-tree-preorder-traversal/)  
[中序遍历](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)  
[后序遍历](https://leetcode-cn.com/problems/binary-tree-postorder-traversal/)  

递归写法很简单，三种遍历只需要调整输出节点数值和递归调用函数的位置就可以了。  
**前序遍历：根左右  
中序遍历：左根右  
后续遍历：左右根  
递归写法的顺序就和上面的顺序一样**    
递归和迭代法的时间复杂度差不多，但递归空间复杂度更大。在实际的工程中，更应该避免过多的递归。下面用迭代法解决遍历问题。   

# 1. 前序遍历
![image](https://user-images.githubusercontent.com/74122331/128728509-3b8ac5d6-1a2c-4416-90e7-f6c66db6ab02.png)
前序遍历的顺序：1245367  
前序遍历的递归可以看成一个栈。  
对于每一个节点，先输出它存储的值，然后依次将它的右节点和左节点压入栈（先右后左，这样出栈时就会先左后右）。  
那么操作可以如下：  
先输出节点1存储的值，然后把1的右、左儿子（3、2）依次压入栈，现在的栈（从底到顶，下同）里面的值为：[3, 2]  
然后一直循环直到栈为空（即遍历过所有节点）：  
输出当前节点的值，压入它的右、左儿子  
在本例中，输出2之后压入5、4，然后输出4，4没有儿子，下一个输出5，5没有儿子，输出3，然后相当于对以3为根节点的子树（整个二叉树的右子树）进行前序遍历，这部分过程不再赘述。  
代码如下：  
```java
class Solution {
    public List<Integer> preorderTraversal(TreeNode root) {
        ArrayList<Integer> a = new ArrayList<>();
        if (root == null)
            return a;
        Stack<TreeNode> s = new Stack<>();
        a.add(root.val);
        if (root.right != null)
            s.push(root.right);
        if (root.left != null)
            s.push(root.left);
        while (!s.empty()) {
            TreeNode p = s.pop();
            a.add(p.val);
            if (p.right != null)
                s.push(p.right);
            if (p.left != null)
                s.push(p.left);
        }
        return a;
    }
}
```  
当然这里可以先把根节点压入栈，然后省略掉循环外面压入根节点的两个子节点的代码，直接把对所有节点值的输出和所有子节点的处理放入循环，这样更为简洁（见[代码随想录](https://github.com/youngyangyang04/leetcode-master)二叉树pdf中的代码）  

# 2.中序遍历  
前面的代码思想并不能照搬到中序遍历当中。因为是在节点弹出栈的时候对它的值进行处理，在前序遍历中，出栈顺序和处理顺序是一样的，但在中序遍历中不一样。  
对应的处理过程如下（转自代码随想录）：
![Alt](https://pic.leetcode-cn.com/1600934697-oafdTT-%E4%BA%8C%E5%8F%89%E6%A0%91%E4%B8%AD%E5%BA%8F%E9%81%8D%E5%8E%86%EF%BC%88%E8%BF%AD%E4%BB%A3%E6%B3%95%EF%BC%89.gif)  
这个过程可以这么理解：  
  
代码如下：   
```java
class Solution {
    public List<Integer> inorderTraversal(TreeNode root) {
        ArrayList<Integer> a = new ArrayList<>();
        if (root == null)
            return a;
        Stack<TreeNode> s = new Stack<>();
        s.add(root);
        TreeNode p = root;
        while (!s.empty()) {
            if (p == null) {
                p = s.pop();
                a.add(p.val);
                p = p.right;
                if (p != null)
                    s.add(p);
            } else {
                p = p.left;
                if (p != null)
                    s.add(p);
            }
        }
        return a;
    }
}
```  

# 3.后序遍历  
后序遍历是左右中，前序遍历是中左右，因此只要把前序遍历的代码改成左右中然后倒过来就是后序遍历了。  
代码如下：  
```java
class Solution {
    public List<Integer> postorderTraversal(TreeNode root) {
        Stack<TreeNode> s = new Stack<>();
        s.add(root);
        ArrayList<Integer> a = new ArrayList<>();
        if (root == null)
            return a;
        while (!s.empty()) {
            TreeNode p = s.pop();
            a.add(p.val);
            if (p.left != null)
                s.add(p.left);
            if (p.right != null)
                s.add(p.right);
        }
        Collections.reverse(a);
        return a;
    }
}
```  
    
# 4.三种方法的统一  
可以看到，上面三种方法是并不共通，换一种遍历就是换一种方法，尤其是中序遍历，和另外两种差别很大。这是因为中序遍历的节点访问和处理是不同时的。为了解决这个问题，需要对节点加上标记。在下面的做法中，我们用添加null节点表示要处理的节点。  
访问就是将节点压入栈，处理就是输出节点的值（将值加入答案数组）  
这部分的参考接可以看[这里](https://mp.weixin.qq.com/s?__biz=MzUxNjY5NTYxNA==&mid=2247484687&idx=1&sn=85cd297b3c9927467e4048b1f50aa938&chksm=f9a2365eced5bf48d5a0396268d8ace02bc7d43effd824fea1925a7f27c7d35e65ed8c2cb787&scene=178&cur_album_id=1577940597036924929#rd)，里面有过程演示的动图。这里就用文字来解释这种方法进行中序遍历的过程：  
![image](https://user-images.githubusercontent.com/74122331/131216718-9a811696-29c4-47c8-8c71-45e4102a8738.png)
对于这样一颗二叉树：  
首先初始化：在栈中加入根节点，此时栈中是[5]（左边表示栈底）  
然后开始循环知道栈为空：  
对于每一个栈顶元素，先将其弹出（知道为什么这么做需要看下去直到理解这个过程），记为p  
这里假设p不为null，如果是，那么后面会讲null的处理方式  
1.依次加入p的右儿子、它本身、null和左儿子。
为什么先加右儿子？  
因为中序遍历是左中右，这样就要求入栈顺序是右中左  
而这里null的作用就是标记。p在之前被加入节点是表示它被访问了，而这时在它后面加入null，则在后续过程中读到null就知道null的下面一个元素是应当被处理（即将值加入输出数组）而不是访问（加入栈，等到后面的步骤中再加入他的孩子节点）；那么，前面弹出栈顶元素的过程就有了防止一个节点被处理两遍的功能。假设前面没有弹出，那么一开始加入的5这个节点就会被不断地访问和处理。  
如果p是null怎么办？  
这就说明搜到了需要处理的节点，这个节点就是null的下一个元素。因为null已经被弹出了，所以只要弹出现在的栈顶（也就是null的下面一个元素），记为p即可  
这个p就是要处理的节点，把它的值加入输出数组，然后弹出即可。  
可以看到，要处理的节点都是一个子树的**根节点**，为什么选择处理根节点，笔者并没有想法，只能先记着。  

整理一遍整个处理过程：  
开始时，栈的内容为[5]  
弹出5，加入5的右儿子6、5和null、5的左儿子4，此时栈为[6, 5, null, 4]  
然后弹出4，加入4的右儿子2、4和null、4的左儿子1，此时栈为[6, 5, null, 2, 4, null, 1]
然后弹出1,1没有右儿子所以先什么都不加，然后加入1和null，1也没有左儿子，所以也不再加别的东西，此时栈为[6, 5, null, 2, 4, null, 1, null]  
然后弹出null，接着弹出1并将其加入输出数组，此时栈为[6, 5, null, 2, 4, null]  
然后弹出null，接着弹出4，加入数组，此时数组为[1, 4]，此时栈为[6, 5, null, 2]  
2没有左右儿子，加入null后进行处理，数组变为[1, 4, 2]，栈变为[6, 5, null]  
弹出null和5，数组变为[1, 4, 2, 5]，栈变为[6]  
后面过程不再写下去，但应该很好理解接下来的过程。  
代码如下：  
```java
class Solution {
    public List<Integer> inorderTraversal(TreeNode root) {
        ArrayList<Integer> a = new ArrayList<>();
        if (root == null)
            return a;
        Stack<TreeNode> s = new Stack<>();
        s.add(root);
        TreeNode p;
        while (!s.empty()) {
            p = s.pop();
            if (p != null) {
                if (p.right != null)
                    s.add(p.right);
                s.add(p);
                s.add(null);
                if (p.left != null)
                    s.add(p.left);
            } else {
                a.add(s.pop().val);
            }
        }
        return a;
    }
}
```  

那么前序遍历呢？  
前序遍历是中左右，因此只要换一下访问节点时将节点加入栈的顺序即可。  
为了方便理解，列出过程：  
开始时，栈的内容为[5]  
弹出5，加入5的右儿子6、5的左儿子4、5和null，此时栈为[6, 4, 5, null]  
然后弹出null，弹出5，加入数组（后面该部分简称为“处理”），此时数组为[5]，栈为[6, 4]  
弹出4，加入4的右儿子2、4的左儿子1、4和null，此时栈为p[6, 2, 1, 4, null]  
处理4，此时数组为[5, 4]，栈为[6, 2, 1]
弹出1，1没有左右儿子，则加入1和null  
处理1，数组为[5, 4, 1]，栈为[6, 2]  
后面不再做说明，自己推导。  
那么代码也只要将p != null时的几个语句调换一下位置：  
```java
class Solution {
    public List<Integer> preorderTraversal(TreeNode root) {
        ArrayList<Integer> a = new ArrayList<>();
        if (root == null)
            return a;
        Stack<TreeNode> s = new Stack<>();
        s.add(root);
        TreeNode p;
        while (!s.empty()) {
            p = s.pop();
            if (p != null) {
                if (p.right != null)
                    s.add(p.right);
                if (p.left != null)
                    s.add(p.left);
                s.add(p);
                s.add(null);
            } else {
                a.add(s.pop().val);
            }
        }
        return a;
    }
}
```  

同样，对于后序遍历，也只要调换一下语句的位置。后序遍历是左右中，因此只要把加入节点的顺序变为中右左即可。  
代码如下：  
```java
class Solution {
    public List<Integer> postorderTraversal(TreeNode root) {
        ArrayList<Integer> a = new ArrayList<>();
        if (root == null)
            return a;
        Stack<TreeNode> s = new Stack<>();
        s.add(root);
        TreeNode p;
        while (!s.empty()) {
            p = s.pop();
            if (p != null) {
                s.add(p);
                s.add(null);
                if (p.right != null)
                    s.add(p.right);
                if (p.left != null)
                    s.add(p.left);
            } else {
                a.add(s.pop().val);
            }
        }
        return a;
    }
}
```  
