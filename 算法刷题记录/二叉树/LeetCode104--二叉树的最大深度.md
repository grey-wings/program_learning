[题目链接](https://leetcode-cn.com/problems/maximum-depth-of-binary-tree/)  

## 解法1  
魔改前序遍历  
本解法能做出题目，但是没有在题解中看到类似的（可能也是看的不仔细）。  
```cpp
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
class Solution {
public:
    stack<int> s;
    int maxn = 0;
    void qxbl(TreeNode* root){
        if (root == nullptr){
            return;
        }
        s.push(root->val);
        qxbl(root->left);
        qxbl(root->right);
        maxn = max(maxn, int(s.size()));
        s.pop();
    }
    int maxDepth(TreeNode* root) {
        qxbl(root);
        return maxn;
    }
};
```

## 解法2  
最大深度就是根节点的高度。在[LeetCode110--平衡二叉树](https://github.com/grey-wings/cpp_learning_process/blob/main/%E4%B8%80%E4%BA%9B%E8%87%AA%E5%B7%B1%E5%86%99%E7%9A%84%E5%9E%83%E5%9C%BE%E9%A2%98/%E4%BA%8C%E5%8F%89%E6%A0%91/LeetCode110--%E5%B9%B3%E8%A1%A1%E4%BA%8C%E5%8F%89%E6%A0%91.md)这一章中，提到了高度应该以后序遍历计算，因此这道题就采取后序遍历的方式，计算这棵树的深度（根节点的高度）。  
设一个递归函数height(TreeNode root)来计算root这个节点的高度。root不一定要是整棵树的根节点，因为在计算高度的时候可以只考虑以要计算的那个节点作为根节点的子树。root这个节点的高度就是max(左子树的高度，右子树的高度)+1；如果root是叶节点，那么它的高度就是1.  
因此代码如下：  
```java
class Solution {
    private int height(TreeNode root) {
        if (root == null)
            return 0;
        int l = (root.left != null) ? height(root.left) : 0;
        int r = (root.right != null) ? height(root.right) : 0;
        return Math.max(l, r) + 1;
    }
    public int maxDepth(TreeNode root) {
        return height(root);
    }
}
```
