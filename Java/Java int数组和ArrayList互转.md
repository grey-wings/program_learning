# int[]转ArrayList  
```java
a = (ArrayList<Integer>) Arrays.stream(nums).boxed().collect(Collectors.toList());  
```  
解析：  
Arrays.stream(arr) 可以替换成IntStream.of(arr)。  
1.使用Arrays.stream将int[]转换成IntStream。  
2.使用IntStream中的boxed()装箱。将IntStream转换成Stream<Integer>。  
3.使用Stream的collect()，将Stream<T>转换成List<T>，因此正是List<Integer>。  
4.类型转换，不转报错。  
  
# ArrayList转int[]  
 ```java
a.stream().mapToInt(Integer::valueOf).toArray();
```  
