# Java HashMap操作  

## 1.HashMap的forEach方法遍历  
[题目链接](https://leetcode-cn.com/problems/find-duplicate-file-in-system/)  

遍历方法见代码：  
```java
class Solution {
    public List<List<String>> findDuplicate(String[] paths) {
        HashMap<String, ArrayList<String>> h = new HashMap<>();
        ArrayList<List<String>> a = new ArrayList<>();
        String s1, s2;
        for (String s : paths) {
            String[] sb = s.split(" ");
            for (int i = 1; i < sb.length; i++) {
                String[] sb1 = sb[i].split("\\(");
                s1 = sb1[1].substring(0, sb1[1].length() - 1);
                if (h.containsKey(s1)) {
                    ArrayList<String> a1 = h.get(s1);
                    a1.add(sb[0] + "/" + sb1[0]);
                    h.replace(s1, a1);
                }
                else {
                    ArrayList<String> a1 = new ArrayList<>();
                    a1.add(sb[0] + "/" + sb1[0]);
                    h.put(s1, a1);
                }
            }
        }
        h.forEach((key, value) -> {
            if (value.size() > 1) {
                a.add(value);
            }
        });
        return a;
    }
}
```  
