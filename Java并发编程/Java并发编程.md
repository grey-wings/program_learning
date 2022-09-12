# Java并发编程

## 一、并发编程的底层实现原理  
### 1.volatile  
#### 1.1 定义和实现原理  
见P21  
如果一个字段被声明成volatile，则所有线程看到这个变量的值是一致的。  
对volatile变量写入时，这个变量所在的缓存行的数据写回到系统内存，同时会导致其他处理器的缓存无效。  
volatile类型的变量能被多线程同时读，但只能被单线程同时写（除非写入的值不依赖于原值）。  
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

## 四、Java中的锁  
### 1.Lock接口  
见P222  
用Lock接口获取锁时，不能写在try里。因为如果在获取锁的时候发生了异常，会引起锁的无故释放。  
在finally块中释放锁，保证获取锁后，锁最终能被释放。  
Lock接口提供的synchronized关键字不具备的主要特性：  
[![QQ-20220905194334.jpg](https://i.postimg.cc/KcNcVbb2/QQ-20220905194334.jpg)](https://postimg.cc/RqWz6jqs)  
Lock的API：  
[![QQ-20220905194439.png](https://i.postimg.cc/8kKccG0b/QQ-20220905194439.png)](https://postimg.cc/hhmcZkgJ)  
Lock接口的实现基本是通过聚合了一个同步器的子类来完成线程访问控制的。  
#### 1.1 同步器  
见P224
队列同步器AbstractQueuedSynchronizer使用了一个int成员变量表示同步状态，通过内置的FIFO队列完成资源获取线程的排队工作。  
[![QQ-20220906141827.jpg](https://i.postimg.cc/VNgXmqqb/QQ-20220906141827.jpg)](https://postimg.cc/Y44vxmyp)  
[![QQ-20220906150914.png](https://i.postimg.cc/8PTt2g7Z/QQ-20220906150914.png)](https://postimg.cc/5jkBzGqz)  
实现自定义同步组件时，将会调用同步器提供的模板方法。  
[![QQ-20220906151458.jpg](https://i.postimg.cc/0QM7gcv5/QQ-20220906151458.jpg)](https://postimg.cc/G8R4GP96)  
eg.独占锁  
见P226  
同步状态置1为加锁，置0为解锁。  
#### 1.2 同步器的实现  
见P229  
同步器依赖同步队列进行同步状态的管理。当线程获取同步状态失败时，会被包装成一个结点加入同步队列并阻塞，同步状态释放时会唤醒当前线程。 
同步队列的基本结构如下：  
[![QQ-20220906163001.png](https://i.postimg.cc/65Ry8RK5/QQ-20220906163001.png)](https://postimg.cc/crxsjv6V)   
同步器有一个指向头结点和一个指向尾结点的引用。  
同步器使用CAS更新尾结点。  
首节点释放同步状态时会唤醒它的后继，后继节点获取同步状态后会将自己设为首节点。这一步不需要CAS，因为只有一个线程能获取同步状态。  
#### 1.3 独占式同步状态的获取与释放  
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
#### 1.4 共享式同步状态的获取与释放 
共享式获取在同一时刻可以有多个线程同时获取同步状态，适合读操作使用。  
共享式获取的自旋过程中，成功获取同步状态并退出自旋的条件是tryAcquireShared(int arg)方法返回值大于等于0.  
自旋过程中，如果当前节点的前驱为头结点，尝试获取同步状态，返回值大于等于0表示该次获取同步状态成功并退出自旋。 
#### 1.5 获取同步状态对中断的响应  
acquireInterruptibly(int arg)方法在等待获取同步状态时，如果当前线程被中断，会立即返回并抛出InterruptedException.  
#### 1.6 独占式超时获取同步状态  
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
#### 1.7 自定义同步器示例  
见P243  
### 2.重入锁ReentrantLock  
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
### 3.读写锁ReentrantReadWriteLock  
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
#### 3.1 写锁的获取和释放  
写锁是一个可重入的排它锁。如果当前线程已经获取了写锁，则增加写状态；如果当前线程获取写锁时，读锁已被获取（读状态不为0）或者该线程不是已经获取写锁的线程，那么就等待。  
#### 3.2 读锁的获取和释放  
如果其他线程获取了写锁，则等待；如果当前线程获取了写锁或写锁未被获取，则当前线程增加读状态。  
#### 3.3 锁降级  
锁降级是指继续持有当前所拥有的写锁，在获取读锁，最后释放写锁的过程。  
读写锁不支持锁升级。因为如果其中一个占据读锁的线程升级为写锁，它对数据的改变是其他获取了读锁的线程不可见的。  
### 4.LockSupport工具  
LockSupport用于阻塞和唤醒线程。它定回忆了一组park开头的方法来阻塞线程，以及unpark方法来唤醒线程。  
[![QQ-20220906163001.png](https://i.postimg.cc/PJWCM8Nm/QQ-20220906163001.png)](https://postimg.cc/ZvqYbn8R)  
上表中的前三个方法是可以添加一个Object对象作为第一个参数（例如：parkNanos(Object blocker, long nanos)），blocker用来表示当前线程在等待的对象（下面称为阻塞对象），有阻塞对象的park类方法能够传递给开发人员更多的现场信息。  
### 5.Condition接口  
任意一个Java对象都拥有一组监视器方法，在java.lang.Object上，主要包括wait(), notify(), notifyAll()等方法。Condition接口也提供了类似的监视器方法，与Lock配合。  
Condition接口与Object的监视器方法的区别见P263  
Condition接口依赖Lock对象：`Condition condition = lock.newCondition();`  
Condition的实现是同步器的内部类，因此每个Condition示例都能访问同步器提供的方法，相当于每个Condition都拥有所属同步器的引用。  
Condition的部分方法介绍：  
[![QQ-20220906163001.png](https://i.postimg.cc/GmgYSGhR/QQ-20220906163001.png)](https://postimg.cc/gxRnxwZt)  
下面的例子是一个有界队列，应用了Condition接口：  
```java
public class BoundedQueue<T> {
    private Object[] items;
    // 添加的下标，删除的下标和数组当前的数据量
    private int addIndex, removeIndex, count;
    private Lock lock = new ReentrantLock();
    private Condition notEmpty = lock.newCondition();
    private Condition notFull = lock.newCondition();
    public BoundedQueue(int size) {
        items = new Object[size];
    }
    // 添加一个元素，如果数组满，则添加线程进入等待状态，直到有空位
    public void add(T t) throws InterruptedException {
        lock.lock();
        try {
            // 如果数组已满，就在notFull上等待，等待时释放锁
            while (count == items.length)  
                notFull.await();
            // 添加元素
            items[addIndex] = t;
            if (++addIndex == items.length)
                addIndex = 0;
            ++count;
            // 通知等待在notEmpty上的线程，表示已经有数据可以获取
            notEmpty.signal();
        } finally {
            lock.unlock();
        }
    }
    // 由头部删除一个元素，如果数组空，则删除线程进入等待状态，直到有新元素被添加
    @SuppressWarnings("unchecked")  // 该注解抑制编译器产生的警告
    public T remove() throws InterruptedException {
        lock.lock();
        try {
            while (count == 0)
                notEmpty.await();
            Object x = items[removeIndex];
            if (++removeIndex == items.length)
                removeIndex = 0;
            --count;
            notFull.signal();
            return (T) x;
        } finally {
            lock.unlock();
        }
    }
}
```  
使用while而不是if是为了防止过早或意外的通知，类似于等待-通知模式。 
#### 5.1 Condition的实现  
Condition
##### 5.1.1.等待队列  
等待队列是一个FIFO队列，存储调用了Condition.await()的线程。等待队列的节点定义和同步队列相同。  
等待队列添加节点不需要CAS，因为调用await()的线程必定是获取了锁的线程。等待队列的添加通过锁来保证线程安全。  
在Object的监视器模型上，一个对象有一个同步队列和一个等待队列。而Lock拥有一个同步队列和多个等待队列，它们的示意图如下：  
[![QQ-20220906163001.png](https://i.postimg.cc/FzTdnWMh/QQ-20220906163001.png)](https://postimg.cc/sGZgMcfL)  
#### 5.1.2 等待  
**从await()返回时，当前线程一定获取了Condition相关的锁。**  
调用await()方法时，相当于同步队列的首节点移动到Condition的等待队列中。  
等待中的结点被中断会抛出InterruptedException.  
#### 5.1.3 通知  
调用signal()方法的前提是获取了锁。  
执行signal()方法时，等待队列中的头结点被线程安全地移动到同步队列，然后被唤醒，从await()方法中的while循环中退出，然后调用同步器的acquireQueued()竞争获取同步状态，若成功获取锁，则从await()方法返回。  
## 五、Java并发容器和框架  
### 1.ConcurrentHashMap  
ConcurrentHashMap利用了锁分段技术。一个锁只锁容器中的一部分数据，可以提高并发访问效率。而同样线程安全的HashTable只有一把锁，效率低下。  
ConcurrentHashMap由Segment和HashEntry两种数组组成。Segment是一种可重入锁，HashEntry用于存储k-v对。一个ConcurrentHashMap包含一个Segment数组，每个Segment守护着一个HashEntry数组里的元素，每个HashEntry是一个链表结构的元素。  
#### 1.1 初始化  
见P279  
#### 1.2 get操作  
get操作不需要加锁，如果读到空值才会加锁重读。这是因为get方法里要用到的共享变量全部是volatile类型，如用于统计当前Segment大小的count字段和HashEntry的value。  
#### 1.3 put操作  
put操作需要对共享变量进行写操作，因此需要加锁。  
put方法首先定位到Segment，然后判断是否需要对Segment里的HashEntry数组进行扩容，然后定位添加元素的位置，将其放在HashEntry数组里。  
如果HashEntry超过了容量，那么进行扩容。扩容时会创建一个容量是原来两倍的数组，然后将原数组里的元素rehash进型的数组里。ConcurrentHashMap只会对某个segment进行扩容。  
#### 1.4 size操作  
统计整个ConcurrentHashMap里元素的数量。  
相加时可以获取每个Segment的count的最行之，但可能累加前count发生了变化。因此先尝试2次不锁Segment的方式统计各个Segment的大小，如果统计的过程中，容器的count发生了变化，再采用加锁的方式统计所有Segment的大小。容器是否发生变化由一个变量modCount判断，put, remove, clean方法都会使modCount变量加1，则在统计size前后如果modCount没有变化，则得知容器大小没有变化。  
### 2.ConcurrentLinkedQueue：非阻塞的线程安全队列  
ConcurrentLinkedQueue由head和tail结点组成，每个结点由节点元素item和指向下一个节点的引用next组成。**默认情况下存储的元素为空，tail == head。  
#### 2.1 入队  
入队做两件事情：第一是吧入队节点设成当前队列尾结点的下一个结点；二是如果tail的next不为空就将入队节点设为tail，否则将入队节点设为tail的next结点。**所以tail结点不总是尾结点。**  
入队的示意图如下：  
[![QQ-20220908104238.png](https://i.postimg.cc/66zMD66W/QQ-20220908104238.png)](https://postimg.cc/mhz39sFJ)  
入队需要采用CAS算法，首先定位尾结点，其次使用CAS算法将入队结点设置成尾结点的next结点，如不成功则重试。    
为什么不让tail永远是队列的尾结点？  
如果这样做，每次都需要用循环CAS更新tail结点，现有的做法减少了CAS操作的数量，提高了效率。tail和尾结点允许有1个结点的距离，实际上是用volatile变量的读操作来减少对volatile变量的写操作。  
#### 2.2 出队  
出队的一个例子示意如下：  
[![QQ-20220908104238.png](https://i.postimg.cc/05FjMCtL/QQ-20220908104238.png)](https://postimg.cc/NL8BZRv4)  
head结点有元素时，直接弹出head结点里的元素（赋值为null），而不会更新head结点；head结点为空时，出队操作才会更新head结点。这也是通过减少CAS更新head结点的消耗来提高效率。  
### 3.阻塞队列  
阻塞队列支持阻塞的插入和移除方法。  
插入阻塞的插入方法：当队列满时队列会阻塞插入元素的线程，直到队列不满。  
插入阻塞的移除方法：当队列空时获取元素的线程会等待队列变为非空。  
在阻塞队列不可用时
[![QQ-20220908212707.jpg](https://i.postimg.cc/2yGJwK7C/QQ-20220908212707.jpg)](https://postimg.cc/0K6c5Z44)  
返回特殊值是指插入成功返回true，移除失败返回null。  
Java中有7种阻塞队列，见P298.  
#### 3.1 DelayQueue：一个支持延时获取元素的无界阻塞队列  
该结构用优先队列实现，队列中的元素必须实现Delayed接口。只有延迟期满才能从队列中提取元素。  
DelayQueue可以用于：
·设计缓存系统，用于保存缓存元素的有效期。用一个线程轮询DelayQueue，如果能获取到元素，说明缓存有效期到了。  
·定时任务调度：使用DelayQueue保存当天将要执行的任务和执行时间见，一旦从DelayQueue中获取到任务就开始执行、  
##### 3.1.2 实现Delay接口  
见P300  
第一步，在对象创建的时候，使用time来记录当前对象延迟到什么时候才能使用，并使用sequenceNumbei来标识元素在队列中的先后顺序。  
第二步，实现getDelay方法，该方法返回当前元素还需要延时多长时间，单位是纳秒。  
第三步，实现compareTo方法来指定元素的顺序，比如延时时间最长的放在队列末尾。  
#### 3.2 SynchronousQueue：不储存元素的阻塞队列  
每一个put操作必须等待一个take操作，否则不能继续添加元素。  
它可以看成一个传球手，适合传递性场景。SynchronousQueue的吞吐量高于LinkedBlockingQueue和ArrayBlockingQueue。  
#### 3.3 LinkedTransferQueue：无界阻塞TransferQueue队列  
相比其他队列，它多了tryTransfer和transfer方法。  
##### 3.3.1 transfer方法  
如果当前有消费在等待接收元素（消费者使用take()方法或者带时间限制的poll()方法时），transfer方法可以把生产者传入的元素立刻transfer给消费者。如果没有消费者在等待，transfer方法会将元素存放在队列的tail结点，并等到该元素被消费了才返回。  
##### 3.3.2 tryTransfer方法  
试探生产者传入的元素能否直接传给消费者。如果没有消费者等待接收元素，则返回false。和transfer的区别是tryTransfer方法无论消费者是否接受，方法立即返回，而transfer方法必须等到消费后才返回。  
有时间限制的tryTransfer(E e, long timeout, TimeUnit unit)方法，超时还没消费元素则返回false，否则返回true。  
#### 3.4 LinkedBlockingDeque：双向阻塞队列  
双向队列多了一个操作队列的入口，多线程同时入队时，也就减少了一半的竞争。  
#### 3.5 阻塞队列的实现原理  
·使用通知模式。生产者往满的队列里添加元素时会阻塞生产者，当消费者消费了一个元素后，会通知生产者当前队列可用。在JDK源码中使用了Condition来实现。  
### 4.Fork/Join框架  
Fork/Join框架是一个用于并行执行任务的框架，是一个把大任务分割成若干小人物，然后汇总的框架。例如，计算1到10000的求和，可以分成10个子任务，分别求1到1000，1001到2000……的和，然后再将这些结果相加。  
#### 4.1 工作窃取算法  
是指某个线程从其他队列里窃取任务来执行。通常使用双端队列，被窃取的线程（工作做不完的线程）从头部取任务执行，窃取任务的线程（工作做完有空闲的线程）从队列尾部取任务来执行。  
优点：充分利用线程进行并行计算，减少了线程间的竞争。  
缺点：某些情况下还是存在竞争（比如只有双端队列中一个任务的时候），创建线程和多个队列也会消耗系统资源。  
#### 4.2 Fork/Join的设计  
首先分割任务。把大任务分割成子任务，如果子任务还是很大，需要继续分割。  
其次执行任务并合并结果。分割的子任务放在双端队列里，由几个线程分别取任务执行；结果统一放在一个队列里，启动一个线程拿数据，然后合并他们。  
Fork/Join需要两个类完成以上任务：
·ForkJoinTask：提供在任务中执行fork()和join()操作的机制。一般需要继承RecursiveAction（用于有返回结果的任务）或RecursiveTask（用于无返回结果的任务）。  
·ForkJoinPool：ForkJoinTask需要ForkJoinPool来执行。  
#### 4.3 Fork/Join示例  
见P314  
#### 4.4 Fork/Join的异常捕获  
ForkJoinTask执行时的异常不能在主线程中捕获。设task是一个ForkJoinTask类子类的实例，可以用task.isCompletedAbnormally()检查是否抛出异常或被取消，并可以通过task.getException方法来获取异常。  

## 六、Java中的原子操作类  
### 1.原子更新基本类型类  
包括AtomicBoolean、AtomicInteger和AtomicLong。这3个类的方法基本一样。  
以整型为例，常用方法如下：  
·int addAndGet(int delta)：加法  
·boolean compareAndSet(int expect, int update)：CAS  
·int getAndIncrement()：自增1，并返回**自增前**的值。  
·int getAndSet(int newValue)：以原子方式设置为新的值，并返回**旧的值**。  
getAndIncrement会不断地用CAS尝试将原值更新为原值+1，直到成功。  
### 2.原子更新数组  
包括AtomicIntegerArray（整型）、AtomicLongArray（长整型）、AtomicReferenceArray（引用型）  
整型原子数组主要有以下操作方法：  
·int addAndGet(int i, int delta)：将数组中下标为i的元素加上delta。  
·boolean compareAndSet(int i, int expect, int update)：对于给定下标中的元素，如果当前值等于预期值，则更新。
原子数组构造：  
```java  
static AtomicIntegerArray ai = new AtomicIntegerArray(value);
```  
value数组不会随ai改变。  
### 3.原子更新引用类型AtomicReference  
还有AtomicReferenceFieldUpdater——原子更新引用类型里的字段、AtomicMarkableReference——原子更新带有标志位的引用类型。  
### 4.原子更新字段类  
用于原子更新某个类里的某个字段。  
·AtomicIntegerFieldUpdater：原子更新整型字段的更新器。  
·AtomicLongFieldUpdater：原子更新长整型字段的更新器。  
·AtomicStampedReference：原子更新有版本号的引用类型。可以解决CAS的ABA问题。  
原子更新字段类的使用方法如下：  
```java
public class AtomicIntegerFieldUpdaterTest {
    // 创建原子更新类，并设置需要更新的对象类和对象的属性
    private static AtomicIntegerFieldUpdater<User> a = AtomicIntegerFieldUpdater.
    newUpdater(User.class􅇞 "old");
    public static void main(String[] args) {
        // 设置柯南的年龄是10岁
        User conan = new User("conan"􅇞 10);
        // 柯南长了一岁，但是仍然会输出旧的年龄
        System.out.println(a.getAndIncrement(conan));
        // 输出现在的年龄
        System.out.println(a.get(conan));
    }
    public static class User {
        private String name;
        public volatile int old;
        public User(String name􅇞 int old) {
            this.name = name;
            this.old = old;
        }
        public String getName() {
            return name;
        }
        public int getOld() {
            return old;
        }
    }
}
```  
## 七、Java中的并发工具类  
### 1.CountDownLatch  
CountDownLatch允许一个或多个线程等待其他线程完成操作。  
例如：要解析一个Excel里面每个sheet的数据，用多线程解析，主线程等到所有子线程完成解析。最简单的方法是join()。而CountDownLatch也可以实现join()的功能，并且功能更多。  
CountDownLatch的构造函数接收一个int类型的参数作为计数器：  
```java
staticCountDownLatch c = new CountDownLatch(2);
```  
想等待N个点完成，就传入N作为参数。这里的N个点可以是N个线程，可以是1个线程里的N个执行步骤。用在多个线程时，只要把这个CountDownLatch的引用传入对应线程即可。  
每当调用CountDownLatch的countDown方法时，N就会减1；CountDownLatch的await方法会阻塞当前线程，知道N变成0。await方法也可以指定超时。  
### 2.同步屏障CyclicBarrier  
让一组线程达到一个屏障（或者叫同步点）的时候被阻塞，直到最后一个线程到达屏障时，屏障才会开门，所有被屏障拦截的线程才会继续运行。  
使用`new CyclicBarrier(int parties)`来初始化CyclicBarrier类，参数表示屏障拦截的线程数量。每个线程调用await()方法告诉CyclicBarrier已经到达屏障，然后当前线程被阻塞。  
另有一个更高级的构造函数`CyclicBarrier(int parties, Runnable barrierAction)`。  
CyclicBarrier可以用于多线程计算数据，最后合并计算结果的场景。  
### 3.CountDownLatch和CyclicBarrier的区别  
CountDownLatch的计数器只能使用一次，而CyclicBarrier的计数器可以用reset()方法重置，所以CyclicBarrier能处理更复杂的业务场景，例如，如果计算发生错误，可以重置计数器并让线程重新执行。  
CyclicBarrier还有getNumberWaiting方法获得阻塞的线程数量，isBroken方法了解阻塞的线程是否中断等。  
### 4.控制线程数的Semaphore
Semaphore（信号课）用来控制同时访问特定资源的线程数量，可以把它比作控制流量的红绿灯。  
主要应用在流量控制，尤其是公有资源有限的场景，比如数据库。  
构造方法是`Semaphore(int peimits)`, 接受一个整型变量表示可用的许可证数量，即最大并发数。线程使用Semaphore的acquire()方法获得一个许可证，用release()归还许可证。还可以用tryAcquire()方法获取许可证。  
Semaphore的其他方法见P345.  
### 5.线程间交换数据的Exchanger  
Exchanger用于线程间的数据交换，它提供一个同步点，在这个同步点，两个线程可以交换彼此的数据。两个线程通过exchanger方法交换数据，如果第一个线程先执行exchange()方法，它会一直等待第二个线程也执行exchange方法，当两个线程都到达同步点时，这两个线程就可以交换数据。    
Exchanger可以用于遗传算法、校对工作等。例如由两个人进行录入数据，都录入完成后进行比对。  
```java
public class ExchangerTest {
    private static final Exchanger<String>exgr = new Exchanger<String>();
    private static ExecutorServicethreadPool = Executors.newFixedThreadPool(2);
    public static void main(String[] args) {
        threadPool.execute(new Runnable() {
            @Override
            public void run() {
                try {
                    String A = "银行流水A";  // A录入银行流水数据
                    exgr.exchange(A);
                } catch (InterruptedException e) {
                }
            }
        });
        threadPool.execute(new Runnable() {
            @Override
            public void run() {
                try {
                        String B = "银行流水B";  // B录入银行流水数据
                        String A = exgr.exchange("B");
                        System.out.println("A和B数据是否一致" + A.equals(B) + "，A录入的是："
                        + A + "，B录入的是：" + B);
                } catch (InterruptedException e) {
                }
            }
        });
        threadPool.shutdown();
    }
}
```  
exchange也可以设置超时等待。  
## 八、Java中的线程池  
线程池有以下三个好处：  
·降低资源消耗。线程池重复使用已经创建的线程，减少了线程的创建和销毁。  
·提高响应速度。当任务到达时，不需要等到线程创建完毕即可执行。  
·提高现成的可管理性。  
线程池的主要处理流程如下：  
[![QQ-20220910144611.jpg](https://i.postimg.cc/KzhmP0QQ/QQ-20220910144611.jpg)](https://postimg.cc/GBz0rJWs)  
ThreadPoolExecutor执行execute方法分下面四种情况：  
（1）如果当前运行的线程数少于corePoolSize，则创建新线程来执行任务（需要获取全局锁）。  
（2）如果运行的线程数大于等于corePoolSize，则将任务加入BlockingQueue。  
（3）如果无法将任务加入BlockingQueue（队列已满），则创建新的线程来处理任务（需要获取全局锁）。  
（4）如果新线程将使当前运行的线程超出maximumPoolSize，任务将被拒绝。  
ThreadPoolExecutor设计时尽可能避免获取全局锁。  
**工作线程**：线程池创建线程时，会将线程封装成工作线程Worker，Worker在执行完任务后还会循环获取工作队列里的任务来执行。  
### 1.线程池的创建  
```java
public ThreadPoolExecutor(int corePoolSize,
                          int maximumPoolSize,
                          long keepAliveTime,
                          TimeUnit unit,
                          BlockingQueue<Runnable> workQueue,
                          ThreadFactory threadFactory,
                          RejectedExecutionHandler handler)
```  
参数解析如下：  
·corePoolSize：核心线程池大小。当一个任务提交到线程池时，就会创造一个线程。即使池中还有其他线程空闲，也会创造线程直到数量达到corePoolSize。  
·runnableTaskQueue：用于保存等待执行的任务的阻塞队列。可选的队列类型见P356。  
·maximumPoolSize：线程池允许创建的最大线程数。如果任务队列采用无界队列，此参数无效。  
·threadFactory：用来给线程起一个有意义的名字。  
·RejectedExecutionHandler：饱和策略。当队列和线程池都满了，就要采取饱和策略来处理提交的新任务。几种饱和策略定义如下：    
[![QQ-20220910144611.jpg](https://i.postimg.cc/c47ds0XL/QQ-20220910144611.jpg)](https://postimg.cc/0bNTngTT)  
### 2.向线程池提交任务  
有execute()和submit()两种方法。  
execute()用于提交不需要返回值的任务，所以无法判断是否执行成功。参数是一个Runnable类的实例。  
submit()用于提交需要返回值的任务。线程池会返回一个future类型的对象，这个对象可以判断任务是否执行成功，并且可以通过future的get()方法来获取返回值，该方法会阻塞当前线程直到任务完成。get加时间参数也可变为超时方法。    
### 3.关闭线程池  
有shutdown和shutdownNow两种方法。它们的原理是遍历池中所有线程，逐个将其中断，因此无法响应中断的线程可能无法终止。shutdownNow会将线程池的状态设为STOP，然后停止所有正在执行或暂停任务的线程；shutdown将线程池的状态设为SHUTDOWN，然后中断所有没有在执行任务的线程。  
调用这两个方法，isShutdown就返回true；所有任务关闭后，isTerminated返回true。通常使用shutdown方法来关闭线程池，如果任务不一定要执行完，可以调用shutdownNow。  
### 4.合理配置线程池  
线程池的配置要根据任务特性来决定。一般考察以下特性：  
·任务的性质：CPU密集型任务、IO密集型任务、混合型任务  
·任务的优先级  
·任务的执行时间  
·任务的依赖性：是否依赖其他系统资源，如数据库链接  
CPU密集型任务应配置尽可能小的线程，如CPU数量+1；IO密集型任务中，线程不是一直在执行任务，则应配置较多的线程，如CPU数量的两倍；如果可以将任务拆分为一个CPU密集型任务和一个IO密集型任务，且两者时间相差不大，则应拆分以获取更高的吞吐量；若时间差较大则不应拆分。可以通过Runtime.getRuntime().availableProcessors()方法获取CPU个数。  
优先级不同的任务可以使用PriorityBlockingQueue来处理。  
执行时间不同的任务可以建立多个线程池分别处理，也可使用优先队列，先执行短的任务。  
需要数据库连接池的任务，因为需要等到数据库返回结果，则线程数应该设置多一点，否则CPU空闲时间较长。  
建议使用有界队列，根据需求可以大一点，比如几千的容量。eg.数据库出错导致执行SQL十分缓慢，会阻塞大量工作线程。有界队列会在满之后抛出异常（或其他处理策略），但无界队列会不断继续添加任务，可能撑满内存。  
### 5.线程池的监控  
见P363  

## 九、Executor框架  
Java中的线程既是工作单元，也是执行机制。从JDK5开始，把工作单元和执行机制分离开来。工作单元包括Runnable和Callable，而执行机制由Executor框架提供。  
Executor框架采用两级调度模型。应用程序通过Executor框架控制上层的调度，而下层的调度由OS内核控制，不受应用程序控制：  
[![QQ-20220911102906.png](https://i.postimg.cc/XNGqdrkH/QQ-20220911102906.png)](https://postimg.cc/NLtQwfVm)  
Executor框架主要由三大部分组成：  
·任务。被执行任务需要实现Runnable或Callable接口。  
·任务的执行。包括任务执行机制的核心接口Executor，以及继承自Executor的ExecutorService接口。Executor框架的两个关键类ThreadPoolExecutor和ScheduledThreadPoolExecutor实现了ExecutorService接口。  
·异步计算的结果。包括接口Future和实现Future接口的FutureTask类。  
关于这些类和接口的简介如下：  
[![QQ-20220910144611.jpg](https://i.postimg.cc/28Ddz03m/QQ-20220910144611.jpg)](https://postimg.cc/grgLsqvB)  
Executor的执行过程见P370  
### 1.ThreadPoolExecutor  
可以创建以下3种类型的ThreadPoolExecutor：  
·FixedThreadPool。线程数固定，适用于为了满足资源管理的需求，而需要限制当前线程数量的应用场景，适用于负载较重的服务器。  
·SingleThreadExecutor。适用于需要保证顺序地执行各个任务，并且在任意时间点不会有多个线程是活动的应用场景。   
·CachedThreadPool。是一个大小无界的线程池，会根据需要创建新线程。适用于执行很多短期异步任务的小程序，或者是负载较轻的服务器。  
### 2.ScheduledThreadPoolExecutor  
可以创建以下2种类型的ScheduledThreadPoolExecutor： 
·ScheduledThreadPoolExecutor。包含若干个线程的ScheduledThreadPoolExecutor，适用于多个后台线程执行**周期任务**，同时为了满足资源管理的需求需要限制后台线程数量的应用场景。  
·SingleThreadScheduledExecutor。只包含一个线程的ScheduledThreadPoolExecutor，适用于需要单个后台线程执行**周期任务**，并且需要保证顺序地执行各个任务的应用场景。  
此类的相关API见P372  
### 3.Future接口  
Future接口和实现该接口的FutureTask类用来表示异步计算的结果。当我们把Runnable接口或Callable接口的实现submit给ThreadPoolExecutor或ScheduledThreadPoolExecutor会向我们返回一个FutureTask对象。对于的API如下：  
```java
<T> Future<T> submit(Callable<T> task)
<T> Future<T> submit(Runnable task, T result)
Future<> submit(Runnable task)
```  
### 4.Runnable接口和Callable接口  
这些接口实现类都可以被ThreadPoolExecutor和ScheduledThreadPoolExecutor执行。Runnable不会返回结果但Callable会。  
可以使用Executor的callable()方法把Runnable包装成Callable。然后用submit()提交给Executor执行，并返回一个FutureTask对象。可以用FutureTask.get()方法等待任务执行完成。    
### 5.ThreadPoolExecutor详解  
Executor框架最核心的类是ThreadPoolExecutor，它是线程池的实现类，主要由下列4个组件构成。  
[![QQ-20220910144611.jpg](https://i.postimg.cc/dVBjbyYq/QQ-20220910144611.jpg)](https://postimg.cc/688ZRTqS)  
通过Executor框架的工具类Executors，可以创建3种类型的ThreadPoolExecutor：FixedThreadPool、SingleThreadExecutor和CachedThreadPool。  
#### 5.1 FixedThreadPool  
FixedThreadPool被称为可重用固定线程数的线程池。它的定义如下：    
```java
public static ExecutorService newFixedThreadPool(int nThreads) {
    return new ThreadPoolExecutor(nThreads, nThreads, 0L, TimeUnit.MILLISECONDS,
                                  new LinkedBlockingQueue<Runnable>());
}
```  
corePoolSize和maximumPoolSize都被设置为nThreads。当线程池中的线程数大于corePoolSize时，keepAliveTime为多余的空闲线程等待新任务的最长时间，超过这个时间后多余的线程将被终止。这里的keepAliveTime被设置为0，意味着多余的线程会被立即终止（然而这个参数卵用没有，原因如下）。  
FixedThreadPool使用无界队列作为工作队列，它会产生一下影响：
·线程池中的线程数达到corePoolSize后，新任务将在无界队列中等待，因此线程池中的线程数不会超过corePoolSize。  
·maximumPoolSize和keepAliveTime无效。  
·任务不会被拒绝。  
#### 5.2 SingleThreadExecutor  
使用单个线程，源码如下：  
```java
public static ExecutorService newSingleThreadExecutor() {
    return new FinalizableDelegatedExecutorService
            (new ThreadPoolExecutor(1, 1, 0L, TimeUnit.MILLISECONDS,
            new LinkedBlockingQueue<Runnable>()));
}
```   
corePoolSize和maximumPoolSize都被设置为1，其余参数与FixedThreadPool相同。工作队列是无界队列，其作用见前一节。  
#### 5.3 CachedThreadPool  
它会根据需要创建新线程。  
