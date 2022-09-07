@[TOC]
# Java并发编程

[一、并发编程的底层实现原理](#一、并发编程的底层实现原理)
[定义和实现原理](#21-定义和实现原理)  
## 一、并发编程的底层实现原理  
### 1.volatile  
#### 1.1 定义和实现原理  
见P21  
如果一个字段被声明成volatile，则所有线程看到这个变量的值是一致的。  
对volatile变量写入时，这个变量所在的缓存行的数据写回到系统内存，同时会导致其他处理器的缓存无效。  
#### 1.2 volatile的内存语义  
**可见性**：对一个volatile变量的读，总是能看到**任意线程**对这个变量的最后写入。  
**原子性**：对任意单个volatile变量的写具有原子性，但不保证++操作有原子性。  
volatile读的内存语义是
写一个volatile变量时，JMM会把该线程对应的本地内存中的共享变量值刷新到主内存。  
volatile写和锁的释放有相同的内存语义；volatile读和锁的获取有相同的内存语义。  
**volatile内存语义的实现**：
插入[内存屏障](./%E6%9C%AF%E8%AF%AD%E8%A7%A3%E9%87%8A.md#1.内存屏障)  
在每个volatile写操作的前面插入StoreStore屏障，后面插入StoreLoad屏障；   
在每个volatile读操作的后面插入LoadLoad屏障，后面插入一个LoadStore屏障。    
（似乎是可以刷新所有共享变量？）  
### 2.synchronized   
#### 2.1 定义和实现原理  
见P26  
Java中的每一个对象都可以作为锁。具体表现为以下三种形式：  
对于普通同步方法，锁是当前实例对象。  
对于静态同步方法，锁是当前类的[Class对象](%E6%9C%AF%E8%AF%AD%E8%A7%A3%E9%87%8A.md#2class对象)。
对于同步方法块，锁是synchronize括号里配置的对象。  
#### 2.2 应用  
见P189  
synchronized可以修饰方法或者同步块，它保证在同一个时刻只能有一个线程在同步方法或者同步块中。  
synchronized本质是获取对象的监视器（monitor），这个过程是排他的，没有获取到监视器的线程将被阻塞。  
### 3.原子操作
#### 3.1 处理器实现原子操作  
原子操作有总线锁、缓存锁两种实现。  
总线锁只允许一个处理器在总线上写  
缓存锁启用时，当一个处理器修改缓存行中的数据，缓存锁会阻止其他处理器缓存这个缓存行。  

被操作的数据不能被缓存在处理器内部，或者操作的数据跨多个缓存行时，处理器调用总线锁定。  
#### 3.2 Java实现原子操作  
（1）自旋CAS实现原子操作  
循环进行CAS操作直到成功为止。  
该方法有三个缺点：ABA问题（通过添加版本号解决）、循环时间开销大、只能保证一个变量的原子操作（多个变量可以用锁）。  
（2）用锁实现原子操作。  

## 二、Java内存模型  
### 1.线程通信
Java线程通信示例：  
[![QQ-20220903223307.jpg](https://i.postimg.cc/J7yYYPfh/QQ-20220903223307.jpg)](https://postimg.cc/QV3qHkxL)  
### 2.锁的内存语义  
参考P100  
以ReentrantLock为例，公平锁在释放锁的最后写一个volatile变量state，获取锁时首先读这个volatile变量；非公平锁的释放和公平锁相同，以原子操作（CAS）的方式更新state变量。  
#### 2.1 为什么CAS同时具有volatile读和写的内存语义？  
以Intel x86处理器为例。  
compareAndSwapInt()方法是一个native方法，在上述处理器的汇编代码中，有一条lock前缀。添加该前缀的指令会被禁止和前面与后面的指令重排序，并且把写缓冲区中的**所有**数据刷新到内存中。  
CAS的源码见P104  
[![QQ-20220906151458.jpg](https://i.postimg.cc/0QM7gcv5/QQ-20220906151458.jpg)](https://postimg.cc/G8R4GP96)  
### 3.延迟初始化  
见P135  

## 三、Java并发编程基础  
### 1.线程的启动和终止  
见P181
线程启动用start()方法即可。  
线程终止不宜用stop()，因为该方法不保证线程的资源正确释放，可能形成死锁。  
可以使用boolean变量或者中断的方式来终止线程。  
### 2.等待/通知机制  
见P192  
等待/通知的相关方法见下图。  
[![QQ-20220905142057.png](https://i.postimg.cc/4NqD53Mx/QQ-20220905142057.png)](https://postimg.cc/2Vd9jCrs)  
等待/通知机制是指一个线程A调用了对象O的wait()方法进入等待状态，二另一个线程B调用了对象O的notify()或notifyAll()方法，线程A收到通知后从对象O的wait()方法返回。  
·wait中的线程收到通知后不会立刻返回，而是等到发出通知的线程释放锁之后，本线程获取锁才会返回。  
·notify()等待队列中的一个线程移动到同步队列中，而notifyAll()移动所有线程。  
被移动的线程状态由等待变为阻塞。  
### 3.等到超时模式  
调用一个方法等待一段时间，如果该方法能再给定的时间段之内得到结果，那么将结果立刻返回，否则超时返回默认结果。  
该模式范式见P206，示例代码见P207.  
### 4.线程池  
见P211  
### 5.Lock接口  
见P222  
用Lock接口获取锁时，不能写在try里。因为如果在获取锁的时候发生了异常，会引起锁的无故释放。  
在finally块中释放锁，保证获取锁后，锁最终能被释放。  
Lock接口提供的synchronized关键字不具备的主要特性：  
[![QQ-20220905194334.jpg](https://i.postimg.cc/KcNcVbb2/QQ-20220905194334.jpg)](https://postimg.cc/RqWz6jqs)  
Lock的API：  
[![QQ-20220905194439.png](https://i.postimg.cc/8kKccG0b/QQ-20220905194439.png)](https://postimg.cc/hhmcZkgJ)  
Lock接口的实现基本是通过聚合了一个同步器的子类来完成线程访问控制的。  
#### 5.1 同步器  
见P224
队列同步器AbstractQueuedSynchronizer使用了一个int成员变量表示同步状态，通过内置的FIFO队列完成资源获取线程的排队工作。  
[![QQ-20220906141827.jpg](https://i.postimg.cc/VNgXmqqb/QQ-20220906141827.jpg)](https://postimg.cc/Y44vxmyp)  
[![QQ-20220906150914.png](https://i.postimg.cc/8PTt2g7Z/QQ-20220906150914.png)](https://postimg.cc/5jkBzGqz)  
实现自定义同步组件时，将会调用同步器提供的模板方法。  
[![QQ-20220906151458.jpg](https://i.postimg.cc/0QM7gcv5/QQ-20220906151458.jpg)](https://postimg.cc/G8R4GP96)  
eg.独占锁  
见P226  
同步状态置1为加锁，置0为解锁。  
#### 5.2 同步器的实现  
见P229  
同步器依赖同步队列进行同步状态的管理。当线程获取同步状态失败时，会被包装成一个结点加入同步队列并阻塞，同步状态释放时会唤醒当前线程。 
同步队列的基本结构如下：  
[![QQ-20220906163001.png](https://i.postimg.cc/65Ry8RK5/QQ-20220906163001.png)](https://postimg.cc/crxsjv6V)   
同步器有一个指向头结点和一个指向尾结点的引用。  
同步器使用CAS更新尾结点。  
首节点释放同步状态时会唤醒它的后继，后继节点获取同步状态后会将自己设为首节点。这一步不需要CAS，因为只有一个线程能获取同步状态。  
#### 5.3 独占式同步状态的获取与释放  
通过acquire()方法获取独占式同步状态。  
tryAcquire保证线程安全的获取同步状态，如果获取失败，则构造同步节点并通过addWriter方法加入到同步队列（Node.EXCLUSIVE代表独占式），最后调用acquiredQueued方法，使得该节点以“死循环”的方式获取同步状态。如果获取不到则阻塞节点中的线程，而被阻塞现成的唤醒靠本线程的中断或前驱的出队实现。    
```java
public final void acquire(int arg) {
if ( !tryAcquire(arg) && acquireQueued(addWaiter(Node.EXCLUSIVE), arg) )
    selfInterrupt();
}

final boolean acquireQueued(final Node node, int arg) {
    boolean failed = true;
    try {
        boolean interrupted = false;
        for (;;) {
            // 自旋获取同步状态，如果获取到同步状态则退出，否则继续自旋并阻塞
            final Node p = node.predecessor();
            if (p == head && tryAcquire(arg)) {
                // tryAcquired独占式获取同步状态
                // 只有前驱结点才能尝试获取同步状态
                setHead(node);
                p.next = null;        // help GC
                failed = false;
                return interrupted;
        }
        if (shouldParkAfterFailedAcquire(p, node) && parkAndCheckInterru())
            interrupted = true;
        }
        } finally {
            if (failed)
            cancelAcquire(node);
    }
}

private Node addWaiter(Node mode) {
    Node node = new Node(Thread.currentThread(), mode);
    // 快速尝试在尾部添加
    Node pred = tail;
    if (pred != null) {
        // CAS更新尾结点
        node.prev = pred;
        if (compareAndSetTail(pred, node)) {
            pred.next = node;
            return node;
        }
    }
    enq(node);
    return node;
}  

private Node enq(final Node node) {
    for (;;) {
        // 只有通过CAS将结点设置为尾结点之后，当前线程才能从该方法返回
        Node t = tail;
        if (t == null) { 
            // 如果队列里没有结点，就造一个出来
            if ( compareAndSetHead( new Node() ) )
            tail = head;
        } else {
            node.prev = t;
            if (compareAndSetTail(t, node)) {
                t.next = node;
                return t;
            }
        }
    }
}
```
为什么在acquireQueued()中，只有前驱结点才能尝试获取同步状态?  
使结点的释放规则符合FIFO，也便于对过早通知（前驱结点不是头结点的线程由于中断而被唤醒）的处理。  
流程图如下：  
[![QQ-20220906163001.png](https://i.postimg.cc/VLJJ09v3/QQ-20220906163001.png)](https://postimg.cc/Vdcf3CjR)  
#### 5.4 共享式同步状态的获取与释放 
共享式获取在同一时刻可以有多个线程同时获取同步状态，适合读操作使用。  
共享式获取的自旋过程中，成功获取同步状态并退出自旋的条件是tryAcquireShared(int arg)方法返回值大于等于0.  
自旋过程中，如果当前节点的前驱为头结点，尝试获取同步状态，返回值大于等于0表示该次获取同步状态成功并退出自旋。 
#### 5.5 获取同步状态对中断的响应  
acquireInterruptibly(int arg)方法在等待获取同步状态时，如果当前线程被中断，会立即返回并抛出InterruptedException.  
#### 5.6 独占式超时获取同步状态  
同步器的doAcquireNanos可以超时获取同步状态。若在指定的时间段内获取了同步状态则返回true，否则返回false。  
```java
private boolean doAcquireNanos(int arg, long nanosTimeout) throws InterruptedException {
    long lastTime = System.nanoTime();
    final Node node = addWaiter(Node.EXCLUSIVE);
    boolean failed = true;
    try {
        for (;;) {
            // 下面这段和普通独占式相同
            final Node p = node.predecessor();
            if (p == head && tryAcquire(arg)) {
                setHead(node);
                p.next = null; // help GC
                failed = false;
                return true;
            }
            // 如果时间到还没有获取到同步状态，退出并返回false
            if (nanosTimeout <= 0)
                return false;
            // spinForTimeoutThreshold为1000ns，如果剩余时间小于这个阈值，就会自旋而不是等待，
            // 因为非常短时间的超时等待不精确
            if (shouldParkAfterFailedAcquire(p, node) && nanosTimeout > spinForTimeoutThreshold)
                LockSupport.parkNanos(this, nanosTimeout);  // 睡眠并释放资源
            long now = System.nanoTime();
            nanosTimeout -= now - lastTime;
            lastTime = now;
            // 能响应中断
            if (Thread.interrupted())
                throw new InterruptedException();
        }
    } finally {
        if (failed)
            cancelAcquire(node);
    }
}
```  
流程如下：  
[![QQ-20220906163001.png](https://i.postimg.cc/T114nVk4/QQ-20220906163001.png)](https://postimg.cc/wRK2pmYX)  
#### 5.7 自定义同步器示例  
见P243  
### 6.重入锁ReentrantLock  
见P246  
不支持可重入的锁，在线程获取锁后如果再尝试获取锁，就会被自己阻塞。synchronized支持重进入。  
重进入需要解决两个问题：第一是要能识别尝试获取锁的线程是否是占据锁的线程。第二是重复获取锁是进行计数自增，释放锁时计数自减，直到计数为0表示锁已经被完全释放。  
非公平可重入锁的tryAcquire方法如下：  
```java
final boolean nonfairTryAcquire(int acquires) {
    final Thread current = Thread.currentThread();
    int c = getState();
    if (c == 0) {
        if (compareAndSetState(0, acquires)) {
            setExclusiveOwnerThread(current);
            return true;
        }
    } else if (current == getExclusiveOwnerThread()) {
        // 如果是占有锁的线程再次获取锁，则自增计数
        int nextc = c + acquires;
        if (nextc < 0)
            throw new Error("Maximum lock count exceeded");
        setState(nextc);
        return true;
    }
    return false;
}
```  
对于公平可重入锁，在c == 0时，只有当前结点没有前驱结点时才会进行CASCAS设置同步状态，成功才会获取锁。具体表现为非公平锁的tryAcquire方法中的`if (compareAndSetState(0, acquires))`改为`if (!hasQueuedPredecessors() && compareAndSetState(0, acquires))`  
### 7.读写锁ReentrantReadWriteLock  
见P252  
读写锁允许多个线程读访问，但写访问时会阻塞其他所有读写线程。  
读写锁支持公平性选择、重进入和锁降级（写锁降级为读锁）。  
[![QQ-20220906163001.png](https://i.postimg.cc/jj930r92/QQ-20220906163001.png)](https://postimg.cc/XZfkdtn6)  
下面是一个应用读写锁的示例：  
```java
public class Cache {
    static Map<String, Object> map = new HashMap<String, Object>();
    static ReentrantReadWriteLock rwl = new ReentrantReadWriteLock();
    static Lock r = rwl.readLock();
    static Lock w = rwl.writeLock();
    // 获取一个key对应的value
    // 读取数据只需要加读锁
    public static final Object get(String key) {
        r.lock();
        try {
            return map.get(key);
        } finally {
            r.unlock();
        }
    }
    // 下面两个涉及写入的需要加写锁
    // 设置key对应的value，并返回旧的value
    public static final Object put(String key, Object value) {
        w.lock();
        try {
            return map.put(key, value);
        } finally {
            w.unlock();
        }
    }
    // 清空所有的内容
    public static final void clear() {
        w.lock();
        try {
            map.clear();
        } finally {
            w.unlock();
        }
    }
}
```  
类比ReentrantLock的状态变量是锁被重复获取的次数，读写锁用一个变量的高位和低位分别表示读和写的状态。  
如下图所示，高16位表示读，低16位表示写。  
[![QQ-20220906163001.png](https://i.postimg.cc/pr5LYSc3/QQ-20220906163001.png)](https://postimg.cc/sGyz3TrJ)  
