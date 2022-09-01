# Java中的多态、接口和泛型

## 一、多态  
在多态下，引用和对象可以是不同的类型。  
### 1.多态的引入  
```java
Animal dog = new Dog();
```  
在上面的程序中，一个Dog类的实例被赋值给了一个Animal类型的引用。  
运用多态时，任何extends过引用变量类型的对象都可以被赋值给这个引用变量，即**引用类型可以是实际对象类型的父类**。  
## 2.参数和返回类型也可以是多态  
见如下代码：  
```java
class Vet {
    public void giveShot(Animal a) {
        a.makeNoise();
    }
}
Vet v = new Vet();
Dog d = new Dog;
Hippo h = new Hippo();

v.giveShot(d);           // 执行Dog的makeNoise()
v.giveShot(h);           // 执行Hippo的makeNoise()
```  
## 3.抽象类    
有的类不应该被初始化。  
例如Animal类有Dog、Cat等子类，但不应该有Animal类的实例，因为没有意义。  
在Animal类定义前加上abstract关键词，就可以将该类定义为**抽象类**，抽象类不能被new出来。  
```java
abstract class Animal {
    // 定义
}
```  
抽象类中有些方法在没有特定的类型时没有意义。比如不同动物的eat()方法没有通用性，因此可以将它定义为**抽象方法**。
```java
public abstract void eat();
```  
如果要对Animal对象实现一个数据结构，例如AnimalList，则没必要分别编写DogList和CatList等类，直接编写AnimalList即可。  
## 4.接口  
如果需要对某些Animal对象实现Pet的一些功能，则可以设置一个Pet接口（因为Java不支持多重继承，所以不能令一个类同时继承Animal和Pet两个类）。  
接口的所有方法都是抽象的。  
## 二、泛型   
当在Java程序中看到<>这一组符号时，就代表着泛型在起作用。  
泛型意味着更好的类型安全性，假如没有泛型，各种对象，如Cat类、Car类等都可以加入到如ArrayList等集合中。这些对象只能被当做Object类来处理。  
如果应用泛型，那么可以定义形如ArrayList<Fish>这类集合，可以保证从该集合中去除的元素一定是Fish类型。  
**eg.**  
ArrayList的定义为：
```java
public class ArrayList<E> extends AbstractLIst<E> ... {
    ...
} 
```   
当定义了一个ArrayList<String>时，会将定义中的所有**E**都改成**String**  
**注意：**  
```java
public <T extends Animal> void takeThing(ArrayList<T> list)
```
和
```java
public void takeThing(ArrayList<Animal> list)
```
是不一样的。前者可以用Animal类及它的所有子类的ArrayList作为参数，而后者只有用ArrayList<Animal>才能作为参数。  
