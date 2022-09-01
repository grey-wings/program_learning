 [重新排列句子中的单词](https://leetcode-cn.com/problems/rearrange-words-in-a-sentence/submissions/)  

int compareTo(T t)方法说明  
定义:比较此对象与指定对象的顺序。  
返回:负整数、零或正整数。如果该对象小于、等于或大于指定对象，则分别返回负整数、零或正整数  

代码如下：  
```java  
class Str implements Comparable<Str>{
    public String s;
    public int index;
    Str (String ss, int ii) {
        s = ss;
        index = ii;
    }

    @Override
    public int compareTo(Str st) {
        if (this.s.length() < st.s.length())
            return -1;
        else if (this.s.length() > st.s.length())
            return 1;
        else return Integer.compare(this.index, st.index);
    }
}
class Solution {
    public String arrangeWords(String text) {
        String[] stri = text.split(" ");
        Str[] a = new Str[stri.length];
        stri[0] = stri[0].toLowerCase();
        for (int i = 0; i < stri.length; i++) {
            a[i] = new Str(stri[i], i);
        }
        Arrays.sort(a);
        for (int i = 0; i < stri.length; i++) {
            stri[i] = a[i].s;
        }
        stri[0] = (Character.toUpperCase(stri[0].charAt(0)) + stri[0].substring(1));
        return String.join(" ", stri);
    }
}
```  
