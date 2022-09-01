[题目链接](https://leetcode-cn.com/problems/replace-words/)  

[算法原理参考1](https://blog.csdn.net/weixin_39778570/article/details/81990417)  
[算法原理参考2](https://www.cnblogs.com/fusiwei/p/11972776.html)  
字典树是一个如下图所示的数据结构，它用边来存储字符：  
![](https://img-blog.csdn.net/20180823222102694?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3dlaXhpbl8zOTc3ODU3MA==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)  

用一个二维数组来代表Trie，设为trie[MAXN][CHARSET + 1]。MAXN为树的最大节点数目，CHARSET为字符集的最大字符数目（比如假设单词只有小写字符，那么CHARSET就设为26），**这里默认trie的第一维下标从0开始，第二维下标从1开始，即trie[0]代表树的根节点，trie[x][1]代表字符a**  
trie[i][j]的值如果为0，表示trie树的第i号节点没有任何连出去的边（是叶子），如果不为0则表示trie树中i号节点有一条连出去的边，满足边上的字符标识是字符集中第j个字符，并且这条边的终点是trie[i][j]号节点.  同时设置end数组，用于表示词汇表中每个单词结尾的节点编号。  

代码如下：
```java
class Trie {
    public int[][] trie = new int[100010][27];
    public int tot = 1; // tot表示总共的节点数（包括根节点）
    public int[] end = new int[200301]; // end[i]表示第i个词结尾节点的下标
    public void insert(String s, int id) {
        // s为要插入的字符串，id为这个词的编号（对应end[i]中的下标），id从1开始
        int now = 0;
        for (int i = 0; i < s.length(); i++) {
            char ch = s.charAt(i);
            int pos = ch - 'a' + 1;
            if (trie[now][pos] == 0) {
                // 如果当前这个子树上没有对应下一个字母的分支，那么加上该分支
                trie[now][pos] = tot;
                tot++;
            }
            now = trie[now][pos];
        }
        end[now] = id;
    }
    public boolean search(String s) {
        int now = 0;
        for (int i = 0; i < s.length(); i++) {
            char ch = s.charAt(i);
            int pos = ch - 'a' + 1;
            if (trie[now][pos] == 0)
                return false;
            else
                now = trie[now][pos];
        }
        return end[now] != 0; // 检测待测单词的末尾是否是词汇表单词的末尾，防止出现子串的情况
    }
    public boolean startsWith(String prefix) {
    // 查找字典树中是否存有以prefix为前缀的单词，等于prefix的单词也包括在内  
    // 这个算法参考LeetCode677的题解（在下面0）  
        int now = 0;
        ArrayList<Integer> a = new ArrayList<>();
        for (int i = 0; i < prefix.length(); i++) {
            char ch = prefix.charAt(i);
            int pos = ch - 'a' + 1;
            if (trie[now][pos] == 0)
                return false;
            else
                now = trie[now][pos];
        }
        if (end[now] != 0)
            return true;
        for (int i = 0; i < trie[now].length; i++) {
            if (trie[now][i] != 0)
                return true;
        }
        return false;
    }
}
```  
对于[LeetCode648](https://leetcode-cn.com/problems/replace-words/)而言，需要查找的是给定字符串的前缀。因此沿根节点搜索，如果某个节点所引出的边对应的字母均与待查词的下一个字母不匹配，就返回-1（找不到），如果某个字母是字典树中某个词的结尾节点，并且和待查词的下一个字母一致，则说明该待查词能被替换。  
在Trie类中新增针对本题的searchSubString函数，解法如下：  
```java
class Trie {
    public int[][] trie = new int[100010][27];
    public int tot = 1; // tot表示总共的节点数（包括根节点）
    public int[] end = new int[2003]; // end[i]表示第i个词结尾节点的下标
    public void insert(String s, int id) {
        // s为要插入的字符串，id为这个词的编号（对应end[i]中的下标），id从1开始
        int now = 0;
        for (int i = 0; i < s.length(); i++) {
            char ch = s.charAt(i);
            int pos = ch - 'a' + 1;
            if (trie[now][pos] == 0) {
                // 如果当前这个子树上没有对应下一个字母的分支，那么加上该分支
                trie[now][pos] = tot;
                tot++;
            }
            now = trie[now][pos];
        }
        end[now] = id;
    }
    public boolean search(String s) {
        int now = 0;
        for (int i = 0; i < s.length(); i++) {
            char ch = s.charAt(i);
            int pos = ch - 'a' + 1;
            if (trie[now][pos] == 0)
                return false;
            else
                now = trie[now][pos];
        }
        return end[now] != 0; // 检测待测单词的末尾是否是词汇表单词的末尾，防止出现子串的情况
    }
    public int searchSubString(String s) {
        int now = 0;
        for (int i = 0; i < s.length(); i++) {
            char ch = s.charAt(i);
            int pos = ch - 'a' + 1;
            if (end[now] != 0)
                return end[now];
            if (trie[now][pos] == 0)
                return -1;
            else
                now = trie[now][pos];
        }
        return -1;
    }
}
class Solution {
    public String replaceWords(List<String> dictionary, String sentence) {
        String[] s = sentence.split(" ");
        Trie t = new Trie();
        for (int i = 0; i < dictionary.size(); i++) {
            t.insert(dictionary.get(i), i + 1);
        }
        for (int i = 0; i < s.length; i++) {
            int idx = t.searchSubString(s[i]);
            if (idx > 0)
                s[i] = dictionary.get(idx - 1);
        }
        List<String> ls = Arrays.asList(s);
        return String.join(" ", ls);
    }
}
```  

下面一个例子仍然是字典树匹配前缀的例子：
[LeetCode677--键值映射](https://leetcode-cn.com/problems/map-sum-pairs/)  
代码如下：  
```java
class Trie {
    public int[][] trie = new int[100010][27];
    public int tot = 1; // tot表示总共的节点数（包括根节点）
    public int[] end = new int[2003]; // end[i]表示第i个词结尾节点的下标
    public void insert(String s, int id) {
        // s为要插入的字符串，id为这个词的编号（对应end[i]中的下标），id从1开始
        int now = 0;
        for (int i = 0; i < s.length(); i++) {
            char ch = s.charAt(i);
            int pos = ch - 'a' + 1;
            if (trie[now][pos] == 0) {
                // 如果当前这个子树上没有对应下一个字母的分支，那么加上该分支
                trie[now][pos] = tot;
                tot++;
            }
            now = trie[now][pos];
        }
        end[now] = id;
    }

    public boolean search(String s) {
        int now = 0;
        for (int i = 0; i < s.length(); i++) {
            char ch = s.charAt(i);
            int pos = ch - 'a' + 1;
            if (trie[now][pos] == 0)
                return false;
            else
                now = trie[now][pos];
        }
        return end[now] != 0; // 检测待测单词的末尾是否是词汇表单词的末尾，防止出现子串的情况
                              // end[now]值不为0的节点应该是trie[now] == 0的节点（如果这个词不作为词典中其他词的前缀）
    }

    private void bianli(List<Integer> a, int now) {
        if (end[now] != 0)
            a.add(end[now]);
        for (int i = 0; i < trie[now].length; i++) {
            if (trie[now][i] != 0)
                bianli(a, trie[now][i]);
        }
    }
    public List<Integer> searchSubString(String s) {
        int now = 0;
        ArrayList<Integer> a = new ArrayList<>();
        for (int i = 0; i < s.length(); i++) {
            char ch = s.charAt(i);
            int pos = ch - 'a' + 1;
            if (trie[now][pos] == 0)
                return a;
            else
                now = trie[now][pos];
        }
        bianli(a, now);
        return a;
    }

}
class MapSum {
    public ArrayList<String> a = new ArrayList<>();
    public HashMap<String, Integer> h = new HashMap<>();
    public Trie t = new Trie();
    public MapSum() {
        a.add("");
    }

    public void insert(String key, int val) {
        a.add(key);
        h.put(key, val);
        t.insert(key, a.size() - 1);
    }

    public int sum(String prefix) {
        List<Integer> aa = t.searchSubString(prefix);
        int ans = 0;
        for (Integer i : aa) {
            ans += h.get(a.get(i));
        }
        return ans;
    }
}
```  
