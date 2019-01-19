## 操作系统

* 进程间的通信方式（管道、有名管道、信号、共享内存、消息队列、信号量、套接字、文件）

### 进程与线程

对于有线程系统：
* 进程是资源分配的独立单位
* 线程是资源调度的独立单位

对于无线程系统：
* 进程是资源调度、分配的独立单位

#### 进程之间的通信方式以及优缺点

* 管道（PIPE）
    * 有名管道：一种半双工的通信方式，它允许无亲缘关系进程间的通信
        * 优点：可以实现任意关系的进程间的通信
        * 缺点：
            1. 长期存于系统中，使用不当容易出错
            2. 缓冲区有限
    * 无名管道：一种半双工的通信方式，只能在具有亲缘关系的进程间使用（父子进程）
        * 优点：简单方便
        * 缺点：
            1. 局限于单向通信 
            2. 只能创建在它的进程以及其有亲缘关系的进程之间
            3. 缓冲区有限
    * 管道的使用：[link](https://blog.csdn.net/qq_35116371/article/details/71843606)
    	1. 头文件 #include<unistd.h>
        2. 调用函数：int pipe(int filedes[2]); pipe()会建立管道，调用pipe函数时在内核中开辟一块缓冲区(称为管道)用于通信,它有一个读端一个写端,然后通过fds参数传出给用户程序两个文件描述符,filedes[0]指向管道的读端,filedes[1]指向管道的写端(很好记,就像0是标准输入1是标准输出一样)。所以管道在用户程序看起来就像一个打开的文件,通过read(fds[0]);或者write(fds[1]);向这个文件读写数据其实是在读写内核缓冲区。pipe函数调用成功返回0,调用失败返回-1。 
	
* 信号量（Semaphore）：一个计数器，可以用来控制多个线程对共享资源的访问
    * 优点：可以同步进程
    * 缺点：信号量有限
* 信号（Signal）：一种比较复杂的通信方式，用于通知接收进程某个事件已经发生
* 消息队列（Message Queue）：是消息的链表，存放在内核中并由消息队列标识符标识[link](https://blog.csdn.net/ljianhui/article/details/10287879)
    * 优点：可以实现任意进程间的通信，并通过系统调用函数来实现消息发送和接收之间的同步，无需考虑同步问题，方便
    * 缺点：信息的复制需要额外消耗CPU的时间，不适宜于信息量大或操作频繁的场合
    * 消息队列的使用：包括msgget创建和访问消息队列，msgsnd添加消息到消息队列中去，msgrcv从消息队列中获取消息，
    msgctl控制消息队列

* 共享内存（Shared Memory）：映射一段能被其他进程所访问的内存，这段共享内存由一个进程创建，但多个进程都可以访问
    * 优点：无须复制，快捷，信息量大
    * 缺点：
        1. 通信是通过将共享空间缓冲区直接附加到进程的虚拟地址空间中来实现的，因此进程间的读写操作的同步问题
        2. 利用内存缓冲区直接交换信息，内存的实体存在于计算机中，只能同一个计算机系统中的诸多进程共享，不方便网络通信
* 套接字（Socket）：可用于不同及其间的进程通信[linke](https://www.cnblogs.com/skynet/archive/2010/12/12/1903949.html)
    * 优点：
        1. 传输数据为字节级，传输数据可自定义，数据量小效率高
        2. 传输数据时间短，性能高
        3. 适合于客户端和服务器端之间信息实时交互
        4. 可以加密,数据安全性强
    * 缺点：需对传输的数据进行解析，转化成应用级的数据。
    * 使用套接字：
	套接字在本地可以通过进程PID来唯一标识一个进程，但是在网络中这是行不通的。其实TCP/IP协议族已经帮我们解决了这个问题，网络层的“ip地址”可以唯一标识网络中的主机，而传输层的“协议+端口”可以唯一标识主机中的应用程序（进程）。这样利用三元组（ip地址，协议，端口）就可以标识网络的进程了，网络中的进程通信就可以利用这个标志与其它进程进行交互。

socket服务端监听代码
```cpp
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MAXLINE 4096

int main(int argc, char** argv){
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[4096];
    int n;
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1){
        printf("error");
        exit(0);
    }
    
    //设置socket地址相关的结构体
    //其中sin_family代表设置协议族
    //sin_addr.s_addr代表设置socket要绑定的地址
    //，其中INADDR_ANY指代本机的所有地址
    //sin_port指代socket要绑定的监听端口
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family(AF_INET);
    servaddr.sin_addr.s_addr=htol(INADDR_ANY);
    servaddr.sin_port=htons(6666);
    
    //将监听的文件描述符和socket地址结构体进行一下绑定
    if(bind(listenfd, (struct sockaddr*)&servaddr
            , sizeof(ervaddr)) == -1){
            print("binding errors");
            exit(0);
    }
    
    while(true){
        if((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL) == -1))
            continue;
        n = recv(connfd, buff, MAXLINE, 0);
        close(connfd);
    }
    close(listenfd);
}
```

#### 线程之间的通信方式

* 锁机制：包括互斥锁/量（mutex）、读写锁（reader-writer lock）、自旋锁（spin lock）、条件变量（condition）
    * 互斥锁/量（mutex）：提供了以排他方式防止数据结构被并发修改的方法。
    * 读写锁（reader-writer lock）：允许多个线程同时读共享数据，而对写操作是互斥的。
    * 自旋锁（spin lock）与互斥锁类似，都是为了保护共享资源。互斥锁是当资源被占用，申请者进入睡眠状态；而自旋锁则循环检测保持着是否已经释放锁。
    * 条件变量（condition）：可以以原子的方式阻塞进程，直到某个特定条件为真为止。对条件的测试是在互斥锁的保护下进行的。条件变量始终与互斥锁一起使用。

1. 互斥锁的操作主要包括以下几个步骤：
 * 互斥锁初始化：pthread_mutex_init
 * 互斥锁锁定：pthread_mutex_lock
 * 互斥锁尝试锁定：pthread_mutex_trylock
 * 互斥锁解锁：pthread_mutex_unlock
 * 互斥锁销毁：pthread_mutex_destroy

互斥锁主要分为三种：分为快速互斥锁，递归互斥锁，检索互斥锁：这三种锁的主要区别在于其他为占有互斥锁的线程在希望得到互斥锁的时候是否需要阻塞等待：
快速互斥锁是指调用线程会阻塞直到拥有互斥锁的线程释放为止；递归互斥锁能够成功返回并且增加调用线程在互斥上加锁的次数；检索互斥锁则为快速互斥锁的阻塞版本，他会立即返回并得到一个错误。Linux系统在缺省参数情况下创建的是快速互斥锁，而一般情况下windows系统是默认采用递归互斥锁的，所以多数有经验的linux开发人员都采用递归互斥锁，以保证和windows的一致性。当然，我们需要根据程序不同的情况定义所需的互斥锁。


2. 条件变量的主要操作函数如下：
 * pthread_cond_init条件变量初始化。
 * pthread_cond_wait阻塞等待：条件不成立，则线程将一直处于阻塞状态。
 * pthread_cond_timedwait超时等待，一定时间后程序自动解除阻塞状态。
 * pthread_cond_signal在使用这个函数的时候需要注意一个问题，就是linux条件变量自动复位的问题。此函数只将一个处于阻塞的线程解除阻塞状态，即使有多个线程等待此条件发生。
 * pthread_cond_broadcast将所有等待条件发生的线程解除阻塞状态。
 * pthread_cond_destroy销毁条件变量。
    
与互斥锁不同，条件变量是用来阻塞一个线程，直到某种特定条件发生为止。条件变量使线程可以睡眠等待某种条件出现。条件变量是利用线程间共享的全局变量通信的一种机制，一个条件变量主要有两种状态：unsignaled（不成立状态）和signaled（成立状态）。而线程间通信主要有两个动作：一个线程等待（条件变量的条件成立），不成立则挂起，另外一个线程使条件成立（给出条件成立的信号）。**通常条件变量需要配合互斥锁同时使用。** 条件的检测是在互斥锁保护下进行的，如果一个条件为假（unsignaled），一个线程自动阻塞，并释放等待状态改变的互斥锁。如果另外一个线程改变条件使条件成立，它就会发信号给关联的条件变量，唤醒一个或多个等待它的线程，重新获得互斥锁，重新评价条件。  

使用条件变量和互斥锁编写生产者消费者互斥代码：

```cpp
#include <stdio.h>
#include <pthread.h>
#define SIZE 4

struct product{
    pthread_mutex_t mutux;
    pthread_cond_t notfull;
    pthread_cond_t notempty;
    int pos;
    int buf[SIZE];
};

struct product pdt;

void init(struct product * t){
    pthread_mutex_init(&t->mutux,NULL);
    pthread_cond_init(&t->notfull,NULL);
    pthread_cond_init(&t->notempty,NULL);
    t->pos=-1;
}

void put(struct product * t,int data)
{
    pthread_mutex_lock(&t->mutux);
    if(t->pos+1>SIZE-1)//the  array is full
       pthread_cond_wait(&t->notfull,&t->mutux);
    t->pos=t->pos+1;
    t->buf[t->pos]=data;
    printf("thread %d put a data %d  to  pos %d\n",pthread_self(),data,t->pos);
    pthread_cond_signal(&t->notempty);
    pthread_mutex_unlock(&t->mutux);
}
 
 
void get(struct product * t)
{
    pthread_mutex_lock(&t->mutux);
    if(t->pos<0)//the  array is full
       pthread_cond_wait(&t->notempty,&t->mutux);
    printf("thread %d get a data %d  to  pos %d\n",pthread_self(),t->buf[t->pos],t->pos);
    t->pos=t->pos-1;
    pthread_cond_signal(&t->notfull);
    pthread_mutex_unlock(&t->mutux);
}

void * putter(void *){
    int n;
    for(n=0;n<8;n++)
       put(&pdt,n);
}
 
void * getter(void *){
    int n;
    for(n=0;n<8;n++)
       get(&pdt);
}
 
int main(void ){
   int err;
   pthread_t pt1,pt2,gt1,gt2;
   void * retval;
   init(&pdt);
   err=pthread_create(&pt1,NULL,putter,0);
   err=pthread_create(&pt2,NULL,putter,0);
   err=pthread_create(>1,NULL,getter,0);
   err=pthread_create(>2,NULL,getter,0);
   //主线程等待这四个线程结束
   pthread_join(pt1,&retval);
   pthread_join(pt2,&retval);
   pthread_join(gt1,&retval);
   pthread_join(gt2,&retval);
   return 0;
 
}
```

* 信号量机制(Semaphore)
    * 无名线程信号量
    * 命名线程信号量
* 信号机制(Signal)：类似进程间的信号处理
* 屏障（barrier）：屏障允许每个线程等待，直到所有的合作线程都达到某一点，然后从该点继续执行。

线程间的通信目的主要是用于线程同步，所以线程没有像进程通信中的用于数据交换的通信机制  

> 进程线程部分知识点来源于：[进程线程面试题总结](http://blog.csdn.net/wujiafei_njgcxy/article/details/77098977)

### Linux 内核的同步方式

#### 原因

在现代操作系统里，同一时间可能有多个内核执行流在执行，因此内核其实象多进程多线程编程一样也需要一些同步机制来同步各执行单元对共享数据的访问。尤其是在多处理器系统上，更需要一些同步机制来同步不同处理器上的执行单元对共享的数据的访问。

#### 同步方式

* 原子操作
* 信号量（semaphore）
* 读写信号量（rw_semaphore）
* 自旋锁（spinlock）
* 大内核锁（BKL，Big Kernel Lock）
* 读写锁（rwlock）
* 大读者锁（brlock-Big Reader Lock）
* 读-拷贝修改(RCU，Read-Copy Update)
* 顺序锁（seqlock）

> 来自[Linux 内核的同步机制，第 1 部分](https://www.ibm.com/developerworks/cn/linux/l-synch/part1/)、[Linux 内核的同步机制，第 2 部分](https://www.ibm.com/developerworks/cn/linux/l-synch/part2/)

### 死锁

#### 产生条件

* 互斥
* 请求和保持
* 不剥夺
* 环路

#### 预防

* 打破互斥条件：改造独占性资源为虚拟资源，大部分资源已无法改造。
* 打破不可抢占条件：当一进程占有一独占性资源后又申请一独占性资源而无法满足，则退出原占有的资源。
* 打破占有且申请条件：采用资源预先分配策略，即进程运行前申请全部资源，满足则运行，不然就等待，这样就不会占有且申请。
* 打破循环等待条件：实现资源有序分配策略，对所有设备实现分类编号，所有进程只能采用按序号递增的形式申请资源。
* 有序资源分配法
* 银行家算法

### 文件系统

* Windows：FCB表 + FAT + 位图
* Unix：inode + 混合索引 + 成组连接

### 主机字节序与网络字节序

#### 主机字节序（CPU字节序）

##### 概念

主机字节序又叫CPU字节序，其不是由操作系统决定的，而是由CPU指令集架构决定的。主机字节序分为两种：

* 大端字节序（Big Endian）：高序字节存储在低位地址，低序字节存储在高位地址
* 小端字节序（Little Endian）：高序字节存储在高位地址，低序字节存储在低位地址

##### 存储方式

32位整数0x12345678是从起始位置为0x00的地址开始存放，则：

内存地址 | 0x00 | 0x01 | 0x02 | 0x03
---|---|---|---|---
大端|78|56|34|12
小端|12|34|56|78

##### 判断大端小端

可以这样判断自己CPU字节序是大端还是小端：

```cpp
#include <iostream>
using namespace std;

int main()
{
	int i = 0x12345678;

	if (*((char*)&i) == 0x12)
		cout << "大端" << endl;
	else	
		cout << "小端" << endl;

	return 0;
}
```
##### 各架构处理器的字节序

* Intel、AMD（X86架构）：小端
* ARM（ARM架构）：大端小端都支持，默认是小端
* IBM、Motorola（PowerPC架构）：大端

#### 网络字节序

网络字节顺序是TCP/IP中规定好的一种数据表示格式，它与具体的CPU类型、操作系统等无关，从而可以保重数据在不同主机之间传输时能够被正确解释。

网络字节顺序采用：大端（Big Endian）排列方式。
