[题目链接--验证外星语词典](https://leetcode-cn.com/problems/verifying-an-alien-dictionary/)  

题目不难，主要记录一下java里面数组自定义排序的写法。  
代码如下：  
```java
class Solution {
    public boolean isAlienSorted(String[] words, String order) {
        int[] w = new int[123];
        for (int i = 0; i < order.length(); i++) {
            w[order.charAt(i)] = i;
        }
        String[] s = new String[words.length];
        System.arraycopy(words, 0, s, 0, words.length);
        Arrays.sort(words, new Comparator<String>() {
            @Override
            public int compare(String o1, String o2) {
                for (int i = 0; i < Math.min(o1.length(), o2.length()); i++) {
                    if (w[o1.charAt(i)] > w[o2.charAt(i)])
                        return 1;
                    else if (w[o1.charAt(i)] < w[o2.charAt(i)])
                        return -1;
                }
                return o1.length() - o2.length();
            }
        });
        return Arrays.equals(s, words);
    }
}
```
