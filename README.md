
#forked from https://interview.huihut.com/ ,partly changed

* [OS](#OS)
* [Computer Network](#computer-network)
* [Network Programming](#network-programming)


<a id="OS"></a>
## 💻 操作系统

### 进程与线程
* 进程：execution/scheduling的基本单元(heavyweight process)，操作系统资源分配调度的基本单元
* 线程：execution/scheduling的基本单元(lightweight process)，CUP资源分配调度基本单元
* 线程的私有数据和局部数据：
    1. private data: 线程执行的函数内的数据为私有的，不会被其余线程访问
    2. local variables: 关键字_thread 使该变量对其余线程为可见的


#### 进程之间的通信方式以及优缺点

* 管道（PIPE）
    * 有名管道(named pipe)：一种半双工的通信方式，它允许无亲缘关系进程间的通信
        * 优点：可以实现任意关系的进程间的通信
        * 缺点：
            1. 长期存于系统中，使用不当容易出错
            2. 缓冲区有限
    * 无名管道(anonymous pipe)：一种半双工的通信方式，只能在具有亲缘关系的进程间使用（父子进程）
        * 优点：简单方便
        * 缺点：
            1. 局限于单向通信 
            2. 只能创建在它的进程以及其有亲缘关系的进程之间
            3. 缓冲区有限
* 信号量（Semaphore）：一个计数器，可以用来控制多个线程对共享资源的访问
    * 优点：可以同步进程
    * 缺点：信号量有限
* 信号（Signal）：一种比较复杂的通信方式，用于通知接收进程某个事件已经发生
* 消息队列（Message Queue）：是消息的链表，存放在内核中并由消息队列标识符标识
    * 优点：可以实现任意进程间的通信，并通过系统调用函数来实现消息发送和接收之间的同步，无需考虑同步问题，方便
    * 缺点：信息的复制需要额外消耗 CPU 的时间，不适宜于信息量大或操作频繁的场合
* 共享内存（Shared Memory）：映射一段能被其他进程所访问的内存，这段共享内存由一个进程创建，但多个进程都可以访问
    * 优点：无须复制，快捷，信息量大
    * 缺点：
        1. 通信是通过将共享空间缓冲区直接附加到进程的虚拟地址空间中来实现的，因此进程间的读写操作的同步问题
        2. 利用内存缓冲区直接交换信息，内存的实体存在于计算机中，只能同一个计算机系统中的诸多进程共享，不方便网络通信
* 套接字（Socket）：可用于不同计算机间的进程通信
    * 优点：
        1. 传输数据为字节级，传输数据可自定义，数据量小效率高
        2. 传输数据时间短，性能高
        3. 适合于客户端和服务器端之间信息实时交互
        4. 可以加密,数据安全性强
    * 缺点：需对传输的数据进行解析，转化成应用级的数据。


#### 线程之间的通信方式

* 锁机制：包括互斥锁/量（mutex）、读写锁（reader-writer lock）、自旋锁（spin lock）、条件变量（condition）
    * 互斥锁/量（mutex）：提供了以排他方式防止数据结构被并发修改的方法。
    * 读写锁（reader-writer lock）：允许多个线程同时读共享数据，而对写操作是互斥的。
    * 自旋锁（spin lock）与互斥锁类似，都是为了保护共享资源。互斥锁是当资源被占用，申请者进入睡眠状态；而自旋锁则循环检测保持者是否已经释放锁。
    * 条件变量（condition）：可以以原子的方式阻塞进程，直到某个特定条件为真为止。对条件的测试是在互斥锁的保护下进行的。条件变量始终与互斥锁一起使用。
* 信号量机制(Semaphore)
    * 无名线程信号量
    * 命名线程信号量
* 信号机制(Signal)：类似进程间的信号处理
* 屏障（barrier）：屏障允许每个线程等待，直到所有的合作线程都达到某一点，然后从该点继续执行。

线程间的通信目的主要是用于线程同步，所以线程没有像进程通信中的用于数据交换的通信机制  



#### 进程之间私有和共享的资源

* 私有：地址空间、堆、全局变量、栈、寄存器
* 共享：代码段，公共数据，进程目录，进程 ID

#### 线程之间私有和共享的资源

* 私有：线程栈，寄存器，程序计数器
* 共享：堆，地址空间，全局变量，静态变量

#### 多进程与多线程间的对比、优劣与选择

##### 对比

对比维度 | 多进程 | 多线程 | 总结
---|---|---|---
数据共享、同步|数据共享复杂，需要用 IPC；数据是分开的，同步简单|因为共享进程数据，数据共享简单，但也是因为这个原因导致同步复杂|各有优势
内存、CPU|占用内存多，切换复杂，CPU 利用率低|占用内存少，切换简单，CPU 利用率高|线程占优
创建销毁、切换|创建销毁、切换复杂，速度慢|创建销毁、切换简单，速度很快|线程占优
编程、调试|编程简单，调试简单|编程复杂，调试复杂|进程占优
可靠性|进程间不会互相影响|一个线程挂掉将导致整个进程挂掉|进程占优
分布式|适应于多核、多机分布式；如果一台机器不够，扩展到多台机器比较简单|适应于多核分布式|进程占优

##### 优劣

优劣|多进程|多线程
---|---|---
优点|编程、调试简单，可靠性较高|创建、销毁、切换速度快，内存、资源占用小
缺点|创建、销毁、切换速度慢，内存、资源占用大|编程、调试复杂，可靠性较差

##### 选择

* 需要频繁创建销毁的优先用线程
* 需要进行大量计算的优先使用线程
* 强相关的处理用线程，弱相关的处理用进程
* 可能要扩展到多机分布的用进程，多核分布的用线程
* 都满足需求的情况下，用你最熟悉、最拿手的方式

#### 进程的调度方式
- 非剥夺（非抢占）调度方式：当一个进程正在处理机上执行时，即使有某个更为重要或者紧迫的进程进入就绪队列，仍然让正在执行的完成。其优点是实现简单，系统开销小，适用于大多数批处理系统，但它不能用于分时系统和大多数实时系统。
- 剥夺（抢占）调度方式：当一个进程正在处理机上执行时，若有某个更为重要或紧迫的进程（优先级更高）的进程需要使用处理机，则立即暂停正在执行的进程，将处理机分配给这个更重要的进程。这种方式对提高系统吞吐率和响应效率都有明显的好处。但抢占也要遵循一定原则。
##### 调度的基本准则
- CPU利用率
- 系统吞吐量
- 周转时间
- 等待时间
- 响应时间

##### 调度算法
- 先来先服务（FCFS）调度算法
- 短作业优先（SJF）调度算法 ： 平均等待时间、平均周转时间最少
- 优先级调度算法

### Linux 内核的同步方式

#### 原因

在现代操作系统里，同一时间可能有多个内核执行流在执行，因此内核其实像多进程多线程编程一样也需要一些同步机制来同步各执行单元对共享数据的访问。尤其是在多处理器系统上，更需要一些同步机制来同步不同处理器上的执行单元对共享的数据的访问。

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

#### 同步算法
* Peterson's Algorithm:使用flag[]和turn变量当作锁
	* 可能存在blocking problem（使用c++ atomic变量优化）
* Bakery Algorithm
#### Synchronization with OS support
* OS 一般用semaphore作为处理同步问题的工具（具原子性和Bonded waiting）
* 常用的semaphore为busy waiting(do nothing while waiting),浪费CPU cycles，也成为spinlock 
	* To avoid busy waiting, Block the process waiting on a semaphore rather than make it busy waiting and wake up process when some other process executes a signal operation
* two types of semaphores
   * Binary semaphore: range between 0 and 1, the initial value is usually set to 1
   * Counting sempahore, value can exceed 1 and allows multiple processes to be excuting simultaneousely in their critical sections,initial value set to maximum number of processes that are allowed to execute.
* differences between Mutes and semaphore
	* Mutex is a binary semaphore
	* Mutex has a sense of ownership(only tha task that has lock the mutex can unlock it)
#### classic synchronization problems
* Readers and Writers Problem:allows mulitple readers,only allows single writer
	* First reader-writers :reader priority，using semaphore or mutex for solution
	* Second reader-writers: writer priority
	* Third reader-writers: equal priority
* Dining-Philosophers problem

### 死锁

#### 原因

* 系统资源不足
* 资源分配不当
* 进程运行推进顺序不合适

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

* Windows：FCB 表 + FAT + 位图
* Unix：inode + 混合索引 + 成组链接

### 主机字节序与网络字节序

#### 主机字节序（CPU 字节序）

##### 概念

主机字节序又叫 CPU 字节序，其不是由操作系统决定的，而是由 CPU 指令集架构决定的。主机字节序分为两种：

* 大端字节序（Big Endian）：高序字节存储在低位地址，低序字节存储在高位地址
* 小端字节序（Little Endian）：高序字节存储在高位地址，低序字节存储在低位地址

##### 存储方式

32 位整数 `0x12345678` 是从起始位置为 `0x00` 的地址开始存放，则：

内存地址 | 0x00 | 0x01 | 0x02 | 0x03
---|---|---|---|---
大端|12|34|56|78
小端|78|56|34|12

大端小端图片

![大端序](https://gitee.com/huihut/interview/raw/master/images/CPU-Big-Endian.svg.png)
![小端序](https://gitee.com/huihut/interview/raw/master/images/CPU-Little-Endian.svg.png)

##### 判断大端小端

判断大端小端

可以这样判断自己 CPU 字节序是大端还是小端：

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

* x86（Intel、AMD）、MOS Technology 6502、Z80、VAX、PDP-11 等处理器为小端序；
* Motorola 6800、Motorola 68000、PowerPC 970、System/370、SPARC（除 V9 外）等处理器为大端序；
* ARM（默认小端序）、PowerPC（除 PowerPC 970 外）、DEC Alpha、SPARC V9、MIPS、PA-RISC 及 IA64 的字节序是可配置的。

#### 网络字节序

网络字节顺序是 TCP/IP 中规定好的一种数据表示格式，它与具体的 CPU 类型、操作系统等无关，从而可以保证数据在不同主机之间传输时能够被正确解释。

网络字节顺序采用：大端（Big Endian）排列方式。

### 页面置换算法

在地址映射过程中，若在页面中发现所要访问的页面不在内存中，则产生缺页中断。当发生缺页中断时，如果操作系统内存中没有空闲页面，则操作系统必须在内存选择一个页面将其移出内存，以便为即将调入的页面让出空间。而用来选择淘汰哪一页的规则叫做页面置换算法。

#### 分类

* 全局置换：在整个内存空间置换
* 局部置换：在本进程中进行置换

#### 算法

全局：
* 工作集算法
* 缺页率置换算法

局部：
* 最佳置换算法（OPT）
* 先进先出置换算法（FIFO）
* 最近最久未使用（LRU）算法
* 时钟（Clock）置换算法

<a id="computer-network"></a>

## ☁️ 计算机网络

> 本节部分知识点来自《计算机网络（第 7 版）》

计算机网络体系结构：

![计算机网络体系结构](https://gitee.com/huihut/interview/raw/master/images/计算机网络体系结构.png)

### 各层作用及协议

分层 | 作用 | 协议
---|---|---
物理层 | 通过媒介传输比特，确定机械及电气规范（比特 Bit） | RJ45、CLOCK、IEEE802.3（中继器，集线器）
数据链路层|将比特组装成帧和点到点的传递（帧 Frame）| PPP、FR、HDLC、VLAN、MAC（网桥，交换机）
网络层|负责数据包从源到宿的传递和网际互连（包 Packet）|IP、ICMP、ARP、RARP、OSPF、IPX、RIP、IGRP（路由器）
运输层|提供端到端的可靠报文传递和错误恢复（ 段Segment）|TCP、UDP、SPX
会话层|建立、管理和终止会话（会话协议数据单元 SPDU）|NFS、SQL、NETBIOS、RPC
表示层|对数据进行翻译、加密和压缩（表示协议数据单元 PPDU）|JPEG、MPEG、ASII
应用层|允许访问OSI环境的手段（应用协议数据单元 APDU）|FTP、DNS、Telnet、SMTP、HTTP、WWW、NFS


### 物理层

* 传输数据的单位：比特
* 数据传输系统：源系统（源点、发送器） --> 传输系统 --> 目的系统（接收器、终点）

通道：
* 单向通道（单工通道）：只有一个方向通信，没有反方向交互，如广播
* 双向交替通信（半双工通信）：通信双方都可发消息，但不能同时发送或接收
* 双向同时通信（全双工通信）：通信双方可以同时发送和接收信息

通道复用技术：
* 频分复用（FDM，Frequency Division Multiplexing）：不同用户在不同频带，所用用户在同样时间占用不同带宽资源
* 时分复用（TDM，Time Division Multiplexing）：不同用户在同一时间段的不同时间片，所有用户在不同时间占用同样的频带宽度
* 波分复用（WDM，Wavelength Division Multiplexing）：光的频分复用
* 码分复用（CDM，Code Division Multiplexing）：不同用户使用不同的码，可以在同样时间使用同样频带通信

### 数据链路层

主要信道：
* 点对点信道
* 广播信道

#### 点对点信道

* 数据单元：帧

三个基本问题：
* 封装成帧：把网络层的 IP 数据报封装成帧，`SOH - 数据部分 - EOT`
* 透明传输：不管数据部分什么字符，都能传输出去；可以通过字节填充方法解决（冲突字符前加转义字符）
* 差错检测：降低误码率（BER，Bit Error Rate），广泛使用循环冗余检测（CRC，Cyclic Redundancy Check）

点对点协议（Point-to-Point Protocol）：
* 点对点协议（Point-to-Point Protocol）：用户计算机和 ISP 通信时所使用的协议

#### 广播信道

广播通信：
* 硬件地址（物理地址、MAC 地址）
* 单播（unicast）帧（一对一）：收到的帧的 MAC 地址与本站的硬件地址相同
* 广播（broadcast）帧（一对全体）：发送给本局域网上所有站点的帧
* 多播（multicast）帧（一对多）：发送给本局域网上一部分站点的帧

### 网络层

* IP（Internet Protocol，网际协议）是为计算机网络相互连接进行通信而设计的协议。
* ARP（Address Resolution Protocol，地址解析协议）
* ICMP（Internet Control Message Protocol，网际控制报文协议）
* IGMP（Internet Group Management Protocol，网际组管理协议）

#### IP 网际协议

IP 地址分类：
* `IP 地址 ::= {<网络号>,<主机号>}`

IP 地址类别 | 网络号 | 网络范围 | 主机号 | IP 地址范围
---|---|---|---|---
A 类 | 8bit，第一位固定为 0 | 0 —— 127 | 24bit | 1.0.0.0 —— 127.255.255.255
B 类 | 16bit，前两位固定为  10 | 128.0 —— 191.255 | 16bit | 128.0.0.0 —— 191.255.255.255
C  类 | 24bit，前三位固定为  110 | 192.0.0 —— 223.255.255 | 8bit | 192.0.0.0 —— 223.255.255.255
D  类 | 前四位固定为 1110，后面为多播地址
E  类 | 前五位固定为 11110，后面保留为今后所用

IP 数据报格式：

![IP 数据报格式](https://gitee.com/huihut/interview/raw/master/images/IP数据报格式.png)

#### ICMP 网际控制报文协议

ICMP 报文格式：

![ICMP 报文格式](https://gitee.com/huihut/interview/raw/master/images/ICMP报文格式.png)

应用：
* PING（Packet InterNet Groper，分组网间探测）测试两个主机之间的连通性
* TTL（Time To Live，生存时间）该字段指定 IP 包被路由器丢弃之前允许通过的最大网段数量

#### 内部网关协议

* RIP（Routing Information Protocol，路由信息协议）
* OSPF（Open Sortest Path First，开放最短路径优先）

#### 外部网关协议

* BGP（Border Gateway Protocol，边界网关协议）

#### IP多播

* IGMP（Internet Group Management Protocol，网际组管理协议）
* 多播路由选择协议

#### VPN 和 NAT

* VPN（Virtual Private Network，虚拟专用网）
* NAT（Network Address Translation，网络地址转换）

#### 路由表包含什么？

1. 网络 ID（Network ID, Network number）：就是目标地址的网络 ID。
2. 子网掩码（subnet mask）：用来判断 IP 所属网络
3. 下一跳地址/接口（Next hop / interface）：就是数据在发送到目标地址的旅途中下一站的地址。其中 interface 指向 next hop（即为下一个 route）。一个自治系统（AS, Autonomous system）中的 route 应该包含区域内所有的子网络，而默认网关（Network id: `0.0.0.0`, Netmask: `0.0.0.0`）指向自治系统的出口。

根据应用和执行的不同，路由表可能含有如下附加信息：

1. 花费（Cost）：就是数据发送过程中通过路径所需要的花费。
2. 路由的服务质量
3. 路由中需要过滤的出/入连接列表

### 运输层

协议：

* TCP（Transmission Control Protocol，传输控制协议）
* UDP（User Datagram Protocol，用户数据报协议）

端口：

应用程序 | FTP | TELNET | SMTP | DNS | TFTP | HTTP | HTTPS | SNMP  
--- | --- | --- |--- |--- |--- |--- |--- |---   
端口号 | 21 | 23 | 25 | 53 | 69 | 80 | 443 | 161  

#### TCP

* TCP（Transmission Control Protocol，传输控制协议）是一种面向连接的、可靠的、基于字节流的传输层通信协议，其传输的单位是报文段。

特征：
* 面向连接
* 只能点对点（一对一）通信
* 可靠交互
* 全双工通信
* 面向字节流

TCP 如何保证可靠传输：
* 确认和超时重传
* 数据合理分片和排序
* 流量控制
* 拥塞控制
* 数据校验

TCP 报文结构

![TCP 报文](https://gitee.com/huihut/interview/raw/master/images/TCP报文.png)

TCP 首部

![TCP 首部](https://gitee.com/huihut/interview/raw/master/images/TCP首部.png)

TCP：状态控制码（Code，Control Flag），占 6 比特，含义如下：
* URG：紧急比特（urgent），当 `URG＝1` 时，表明紧急指针字段有效，代表该封包为紧急封包。它告诉系统此报文段中有紧急数据，应尽快传送(相当于高优先级的数据)， 且上图中的 Urgent Pointer 字段也会被启用。
* ACK：确认比特（Acknowledge）。只有当 `ACK＝1` 时确认号字段才有效，代表这个封包为确认封包。当 `ACK＝0` 时，确认号无效。
* PSH：（Push function）若为 1 时，代表要求对方立即传送缓冲区内的其他对应封包，而无需等缓冲满了才送。
* RST：复位比特(Reset)，当 `RST＝1` 时，表明 TCP 连接中出现严重差错（如由于主机崩溃或其他原因），必须释放连接，然后再重新建立运输连接。
* SYN：同步比特(Synchronous)，SYN 置为 1，就表示这是一个连接请求或连接接受报文，通常带有 SYN 标志的封包表示『主动』要连接到对方的意思。
* FIN：终止比特(Final)，用来释放一个连接。当 `FIN＝1` 时，表明此报文段的发送端的数据已发送完毕，并要求释放运输连接。

#### UDP

* UDP（User Datagram Protocol，用户数据报协议）是 OSI（Open System Interconnection 开放式系统互联） 参考模型中一种无连接的传输层协议，提供面向事务的简单不可靠信息传送服务，其传输的单位是用户数据报。

特征：
* 无连接
* 尽最大努力交付
* 面向报文
* 没有拥塞控制
* 支持一对一、一对多、多对一、多对多的交互通信
* 首部开销小

UDP 报文结构

![UDP 报文](https://gitee.com/huihut/interview/raw/master/images/UDP报文.png)

UDP 首部

![UDP 首部](https://gitee.com/huihut/interview/raw/master/images/UDP首部.png)



#### TCP 与 UDP 的区别

1. TCP 面向连接，UDP 是无连接的；
2. TCP 提供可靠的服务，也就是说，通过 TCP 连接传送的数据，无差错，不丢失，不重复，且按序到达；UDP 尽最大努力交付，即不保证可靠交付
3. TCP 的逻辑通信信道是全双工的可靠信道；UDP 则是不可靠信道
5. 每一条 TCP 连接只能是点到点的；UDP 支持一对一，一对多，多对一和多对多的交互通信
6. TCP 面向字节流（可能出现黏包问题），实际上是 TCP 把数据看成一连串无结构的字节流；UDP 是面向报文的（不会出现黏包问题）
7. UDP 没有拥塞控制，因此网络出现拥塞不会使源主机的发送速率降低（对实时应用很有用，如 IP 电话，实时视频会议等）
8. TCP 首部开销20字节；UDP 的首部开销小，只有 8 个字节

#### TCP 黏包问题

##### 原因

TCP 是一个基于字节流的传输服务（UDP 基于报文的），“流” 意味着 TCP 所传输的数据是没有边界的。所以可能会出现两个数据包黏在一起的情况。

##### 解决

* 发送定长包。如果每个消息的大小都是一样的，那么在接收对等方只要累计接收数据，直到数据等于一个定长的数值就将它作为一个消息。
* 包头加上包体长度。包头是定长的 4 个字节，说明了包体的长度。接收对等方先接收包头长度，依据包头长度来接收包体。
* 在数据包之间设置边界，如添加特殊符号 `\r\n` 标记。FTP 协议正是这么做的。但问题在于如果数据正文中也含有 `\r\n`，则会误判为消息的边界。
* 使用更加复杂的应用层协议。

#### TCP 流量控制

##### 概念

流量控制（flow control）就是让发送方的发送速率不要太快，要让接收方来得及接收。

##### 方法

利用可变窗口进行流量控制

![](https://gitee.com/huihut/interview/raw/master/images/利用可变窗口进行流量控制举例.png)

#### TCP 滑动窗口

##### 概念

滑动窗口实现流量控制。流量控制是为了控制发送方发送速率，保证接收方来得及接收。
TCP会话的双方都各自维护一个发送窗口和一个接收窗口。接收窗口大小取决于应用、系统、硬件的限制。发送窗口则取决于对端通告的接收窗口。接收方发送的确认报文中的window字段可以用来控制发送方窗口大小，从而影响发送方的发送速率。将接收方的确认报文window字段设置为 0，则发送方不能发送数据。
#### TCP 拥塞控制

##### 概念

拥塞控制就是防止过多的数据注入到网络中，这样可以使网络中的路由器或链路不致过载。

##### 方法

* 慢开始( slow-start )
* 拥塞避免( congestion avoidance )
* 快重传( fast retransmit )
* 快恢复( fast recovery )

TCP的拥塞控制图

![](https://gitee.com/huihut/interview/raw/master/images/TCP拥塞窗口cwnd在拥塞控制时的变化情况.png)
![](https://gitee.com/huihut/interview/raw/master/images/快重传示意图.png)
![](https://gitee.com/huihut/interview/raw/master/images/TCP的拥塞控制流程图.png)

#### TCP 传输连接管理

> 因为 TCP 三次握手建立连接、四次挥手释放连接很重要，所以附上《计算机网络（第 7 版）-谢希仁》书中对此章的详细描述：<https://gitee.com/huihut/interview/raw/master/images/TCP-transport-connection-management.png>

##### TCP 三次握手建立连接

![UDP 报文](https://gitee.com/huihut/interview/raw/master/images/TCP三次握手建立连接.png)

【TCP 建立连接全过程解释】

1. 客户端发送 SYN 给服务器，说明客户端请求建立连接；
2. 服务端收到客户端发的 SYN，并回复 SYN+ACK 给客户端（同意建立连接）；
3. 客户端收到服务端的 SYN+ACK 后，回复 ACK 给服务端（表示客户端收到了服务端发的同意报文）；
4. 服务端收到客户端的 ACK，连接已建立，可以数据传输。

##### TCP 为什么要进行三次握手？

【答案一】因为信道不可靠，而 TCP 想在不可靠信道上建立可靠地传输，那么三次通信是理论上的最小值。（而 UDP 则不需建立可靠传输，因此 UDP 不需要三次握手。）

> [Google Groups . TCP 建立连接为什么是三次握手？{技术}{网络通信}](https://groups.google.com/forum/#!msg/pongba/kF6O7-MFxM0/5S7zIJ4yqKUJ)

【答案二】因为双方都需要确认对方收到了自己发送的序列号，确认过程最少要进行三次通信。

> [知乎 . TCP 为什么是三次握手，而不是两次或四次？](https://www.zhihu.com/question/24853633/answer/115173386)

【答案三】为了防止已失效的连接请求报文段突然又传送到了服务端，因而产生错误。

> [《计算机网络（第 7 版）-谢希仁》](https://gitee.com/huihut/interview/raw/master/images/TCP-transport-connection-management.png)
##### TCP第三次握手失败后会发生什么
1. Server 端 ：第三次的ACK在网络中丢失，那么Server 端该TCP连接的状态为SYN_RECV,并且会根据 TCP的超时重传机制，会等待3秒、6秒、12秒后重新发送SYN+ACK包，以便Client重新发送ACK包。
若长时间不回复则关闭连接
2. Client 端 ：第三次握手中的ACK包丢失的情况下，Client 向 server端发送数据，Server端将以 RST包响应，方能感知到Server的错误。

##### TCP 四次挥手释放连接

![UDP 报文](https://gitee.com/huihut/interview/raw/master/images/TCP四次挥手释放连接.png)

【TCP 释放连接全过程解释】

1. 客户端发送 FIN 给服务器，说明客户端不必发送数据给服务器了（请求释放从客户端到服务器的连接）；
2. 服务器接收到客户端发的 FIN，并回复 ACK 给客户端（同意释放从客户端到服务器的连接）；
3. 客户端收到服务端回复的 ACK，此时从客户端到服务器的连接已释放（但服务端到客户端的连接还未释放，并且客户端还可以接收数据）；
4. 服务端继续发送之前没发完的数据给客户端；
5. 服务端发送 FIN+ACK 给客户端，说明服务端发送完了数据（请求释放从服务端到客户端的连接，就算没收到客户端的回复，过段时间也会自动释放）；
6. 客户端收到服务端的 FIN+ACK，并回复 ACK 给客户端（同意释放从服务端到客户端的连接）；
7. 服务端收到客户端的 ACK 后，释放从服务端到客户端的连接。

##### TCP 为什么要进行四次挥手？

【问题一】TCP 为什么要进行四次挥手？ / 为什么 TCP 建立连接需要三次，而释放连接则需要四次？

【答案一】因为 TCP 是全双工模式，客户端请求关闭连接后，客户端向服务端的连接关闭（一二次挥手），服务端继续传输之前没传完的数据给客户端（数据传输），服务端向客户端的连接关闭（三四次挥手）。所以 TCP 释放连接时服务器的 ACK 和 FIN 是分开发送的（中间隔着数据传输），而 TCP 建立连接时服务器的 ACK 和 SYN 是一起发送的（第二次握手），所以 TCP 建立连接需要三次，而释放连接则需要四次。

【问题二】为什么 TCP 连接时可以 ACK 和 SYN 一起发送，而释放时则 ACK 和 FIN 分开发送呢？（ACK 和 FIN 分开是指第二次和第三次挥手）

【答案二】因为客户端请求释放时，服务器可能还有数据需要传输给客户端，因此服务端要先响应客户端 FIN 请求（服务端发送 ACK），然后数据传输，传输完成后，服务端再提出 FIN 请求（服务端发送 FIN）；而连接时则没有中间的数据传输，因此连接时可以 ACK 和 SYN 一起发送。

【问题三】为什么客户端释放最后需要 TIME-WAIT 等待 2MSL 呢？

【答案三】

1. 为了保证客户端发送的最后一个 ACK 报文能够到达服务端。若未成功到达，则服务端超时重传 FIN+ACK 报文段，客户端再重传 ACK，并重新计时。
2. 防止已失效的连接请求报文段出现在本连接中。TIME-WAIT 持续 2MSL 可使本连接持续的时间内所产生的所有报文段都从网络中消失，这样可使下次连接中不会出现旧的连接报文段。

#### TCP 有限状态机

TCP 有限状态机图片

![TCP 的有限状态机](https://gitee.com/huihut/interview/raw/master/images/TCP的有限状态机.png)

### 应用层

#### DNS

* DNS（Domain Name System，域名系统）是互联网的一项服务。它作为将域名和 IP 地址相互映射的一个分布式数据库，能够使人更方便地访问互联网。DNS 使用 TCP 和 UDP 端口 53。当前，对于每一级域名长度的限制是 63 个字符，域名总长度则不能超过 253 个字符。

域名：
* `域名 ::= {<三级域名>.<二级域名>.<顶级域名>}`，如：`blog.huihut.com`

#### FTP

* FTP（File Transfer Protocol，文件传输协议）是用于在网络上进行文件传输的一套标准协议，使用客户/服务器模式，使用 TCP 数据报，提供交互式访问，双向传输。
* TFTP（Trivial File Transfer Protocol，简单文件传输协议）一个小且易实现的文件传输协议，也使用客户-服务器方式，使用UDP数据报，只支持文件传输而不支持交互，没有列目录，不能对用户进行身份鉴定

#### TELNET

* TELNET 协议是 TCP/IP 协议族中的一员，是 Internet 远程登陆服务的标准协议和主要方式。它为用户提供了在本地计算机上完成远程主机工作的能力。

* HTTP（HyperText Transfer Protocol，超文本传输协议）是用于从 WWW（World Wide Web，万维网）服务器传输超文本到本地浏览器的传送协议。

* SMTP（Simple Mail Transfer Protocol，简单邮件传输协议）是一组用于由源地址到目的地址传送邮件的规则，由它来控制信件的中转方式。SMTP 协议属于 TCP/IP 协议簇，它帮助每台计算机在发送或中转信件时找到下一个目的地。
* Socket 建立网络通信连接至少要一对端口号（Socket）。Socket 本质是编程接口（API），对 TCP/IP 的封装，TCP/IP 也要提供可供程序员做网络开发所用的接口，这就是 Socket 编程接口。

#### WWW

* WWW（World Wide Web，环球信息网，万维网）是一个由许多互相链接的超文本组成的系统，通过互联网访问

##### URL

* URL（Uniform Resource Locator，统一资源定位符）是因特网上标准的资源的地址（Address）

标准格式：

* `协议类型:[//服务器地址[:端口号]][/资源层级UNIX文件路径]文件名[?查询][#片段ID]`
    
完整格式：

* `协议类型:[//[访问资源需要的凭证信息@]服务器地址[:端口号]][/资源层级UNIX文件路径]文件名[?查询][#片段ID]`

> 其中【访问凭证信息@；:端口号；?查询；#片段ID】都属于选填项  
> 如：`https://github.com/huihut/interview#cc`

##### HTTP

HTTP（HyperText Transfer Protocol，超文本传输协议）是一种用于分布式、协作式和超媒体信息系统的应用层协议。HTTP 是万维网的数据通信的基础。

协议特点

- HTTP允许传输任意类型的数据。传输的类型由Content-Type加以标记。
- 无状态。对于客户端每次发送的请求，服务器都认为是一个新的请求，上一次会话和下一次会话之间没有联系。
- 支持客户端/服务器模式。

请求方法

报文方式 ： 请求行、请求头部、空行和请求体四个部分组成
- 请求行：包括请求方法，访问的资源URL，使用的HTTP版本。GET和POST是最常见的HTTP方法，除此以外还包括DELETE、HEAD、OPTIONS、PUT、TRACE。
- 请求头：格式为“属性名:属性值”，服务端根据请求头获取客户端的信息，主要有cookie、host、connection、accept-language、accept-encoding、user-agent。
- 请求体：用户的请求数据如用户名，密码等。
方法 | 意义
--- | ---
OPTIONS | 请求一些选项信息，允许客户端查看服务器的性能
GET | 请求指定的页面信息，并返回实体主体
HEAD | 类似于 get 请求，只不过返回的响应中没有具体的内容，用于获取报头
POST | 向指定资源提交数据进行处理请求（例如提交表单或者上传文件）。数据被包含在请求体中。POST请求可能会导致新的资源的建立和/或已有资源的修改
PUT | 从客户端向服务器传送的数据取代指定的文档的内容
DELETE | 请求服务器删除指定的页面
TRACE | 回显服务器收到的请求，主要用于测试或诊断

状态码（Status-Code）

* 1xx：表示通知信息，如请求收到了或正在进行处理
    * 100 Continue：继续，客户端应继续其请求
    * 101 Switching Protocols 切换协议。服务器根据客户端的请求切换协议。只能切换到更高级的协议，例如，切换到 HTTP 的新版本协议
* 2xx：表示成功，如接收或知道了
    * 200 OK: 请求成功
    * 201：Created 已创建。成功请求并创建了新的资源
    * 203：Non-Authoritative Information 非授权信息。请求成功。但返回的 meta 信息不在原始的服务器，而是一个副本。
    * 202：Accepted 已接受。已经接受请求，但未处理完成。
    * 204：No Content 无内容。服务器成功处理，但未返回内容。在未更新网页的情况下，可确保浏览器继续显示当前文档
    * 205：Reset Content 重置内容。服务器处理成功，用户终端（例如：浏览器）应重置文档视图。可通过此返回码清除浏览器的表单域。
    * 206：Partial Content 部分内容。服务器成功处理了部分 GET 请求。

* 3xx：表示重定向，如要完成请求还必须采取进一步的行动
    * 301 Moved **Permanently:** 永久移动。请求的资源已被永久的移动到新 URL，返回信息会包括新的 URL，浏览器会自动定向到新 URL。今后任何新的请求都应使用新的 URL 代替
    * 302：**Found 临时移动，**与 301 类似。但资源只是临时被移动。客户端应继续使用原有URI。
    * 303：See Other 查看其它地址。与 301 类似。使用 GET 和 POST 请求查看。
    * 304：Not Modified 未修改。所请求的资源未修改，服务器返回此状态码时，不会返回任何资源。
    * 305：Use Proxy 使用代理。所请求的资源必须通过代理访问。
    * 306：Unused 已经被废弃的 HTTP 状态码
    * 307：Temporary Redirect 临时重定向。与 302 类似。使用 GET 请求重定向。
* 4xx：表示客户的差错，如请求中有错误的语法或不能完成
    * 400 Bad Request: 客户端请求的语法错误，服务器无法理解
    * 401 Unauthorized: 请求要求用户的身份认证
    * 403 Forbidden: 服务器理解请求客户端的请求，但是拒绝执行此请求（权限不够）
    * 404 Not Found: 服务器无法根据客户端的请求找到资源（网页）。通过此代码，网站设计人员可设置 “您所请求的资源无法找到” 的个性页面
    * 408 Request Timeout: 服务器等待客户端发送的请求时间过长，超时
* 5xx：表示服务器的差错，如服务器失效无法完成请求
    * 500 Internal Server Error: 服务器内部错误，无法完成请求
    * 503 Service Unavailable: 由于超载或系统维护，服务器暂时的无法处理客户端的请求。延时的长度可包含在服务器的 Retry-After 头信息中
    * 504 Gateway Timeout: 充当网关或代理的服务器，未及时从远端服务器获取请求

##### POST和GET的区别？
- GET 和 POST 最本质的区别是规范上的区别 ： get用于获取资源，仅查询 POST用于传输 会对数据增删改
- GET请求参数通过URL传递，POST的参数放在请求体中。
- GET 请求可以直接进行回退和刷新，不会对用户和程序产生任何影响；而 POST 请求如果直接回滚和刷新将会把数据再次提交。
- GET产生一个TCP数据包；POST产生两个TCP数据包。对于GET方式的请求，浏览器会把请求头和请求体一并发送出去；而对于POST，浏览器先发送请求头，服务器响应100 continue，浏览器再发送请求体。
- GET 请求一般会被缓存，比如常见的 CSS、JS、HTML 请求等都会被缓存；而 POST 请求默认是不进行缓存的。
- GET请求参数会被完整保留在浏览器历史记录里，而POST中的参数不会被保留。

##### URI和URL的区别
- URI，全称是Uniform Resource Identifier)，主要作用是唯一**标识一个资源。**
- URL，全称是Uniform Resource Location)，主要作用是提供资源的路径。打个经典比喻吧，URI像是身份证，可以唯一标识一个人，而URL更像一个住址，可以通过URL找到这个人。
##### 其他协议

* SMTP（Simple Main Transfer Protocol，简单邮件传输协议）是在 Internet 传输 Email 的标准，是一个相对简单的基于文本的协议。在其之上指定了一条消息的一个或多个接收者（在大多数情况下被确认是存在的），然后消息文本会被传输。可以很简单地通过 Telnet 程序来测试一个 SMTP 服务器。SMTP 使用 TCP 端口 25。
* DHCP（Dynamic Host Configuration Protocol，动态主机设置协议）是一个局域网的网络协议，使用 UDP 协议工作，主要有两个用途：
    * 用于内部网络或网络服务供应商自动分配 IP 地址给用户
    * 用于内部网络管理员作为对所有电脑作中央管理的手段
* SNMP（Simple Network Management Protocol，简单网络管理协议）构成了互联网工程工作小组（IETF，Internet Engineering Task Force）定义的 Internet 协议族的一部分。该协议能够支持网络管理系统，用以监测连接到网络上的设备是否有任何引起管理上关注的情况。

<a id="network-programming"></a>

## 🌩 网络编程

### Socket

> [Linux Socket 编程（不限 Linux）](https://www.cnblogs.com/skynet/archive/2010/12/12/1903949.html)

![Socket 客户端服务器通讯](https://gitee.com/huihut/interview/raw/master/images/socket客户端服务器通讯.jpg)


#### Socket 中的 read()、write() 函数

```cpp
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
```

##### read()

* read 函数是负责从 fd 中读取内容。
* 当读成功时，read 返回实际所读的字节数。
* 如果返回的值是 0 表示已经读到文件的结束了，小于 0 表示出现了错误。
* 如果错误为 EINTR 说明读是由中断引起的；如果是 ECONNREST 表示网络连接出了问题。

##### write()

* write 函数将 buf 中的 nbytes 字节内容写入文件描述符 fd。
* 成功时返回写的字节数。失败时返回 -1，并设置 errno 变量。
* 在网络程序中，当我们向套接字文件描述符写时有俩种可能。
* （1）write 的返回值大于 0，表示写了部分或者是全部的数据。
* （2）返回的值小于 0，此时出现了错误。
* 如果错误为 EINTR 表示在写的时候出现了中断错误；如果为 EPIPE 表示网络连接出现了问题（对方已经关闭了连接）。

#### Socket 中 TCP 的三次握手建立连接

我们知道 TCP 建立连接要进行 “三次握手”，即交换三个分组。大致流程如下：

1. 客户端向服务器发送一个 SYN J
2. 服务器向客户端响应一个 SYN K，并对 SYN J 进行确认 ACK J+1
3. 客户端再想服务器发一个确认 ACK K+1

只有就完了三次握手，但是这个三次握手发生在 Socket 的那几个函数中呢？请看下图：

![socket 中发送的 TCP 三次握手](http://images.cnblogs.com/cnblogs_com/skynet/201012/201012122157467258.png)

从图中可以看出：
1. 当客户端调用 connect 时，触发了连接请求，向服务器发送了 SYN J 包，这时 connect 进入阻塞状态；  
2. 服务器监听到连接请求，即收到 SYN J 包，调用 accept 函数接收请求向客户端发送 SYN K ，ACK J+1，这时 accept 进入阻塞状态；  
3. 客户端收到服务器的 SYN K ，ACK J+1 之后，这时 connect 返回，并对 SYN K 进行确认；  
4. 服务器收到 ACK K+1 时，accept 返回，至此三次握手完毕，连接建立。

#### Socket 中 TCP 的四次握手释放连接

上面介绍了 socket 中 TCP 的三次握手建立过程，及其涉及的 socket 函数。现在我们介绍 socket 中的四次握手释放连接的过程，请看下图：

![socket 中发送的 TCP 四次握手](http://images.cnblogs.com/cnblogs_com/skynet/201012/201012122157487616.png)

图示过程如下：

1. 某个应用进程首先调用 close 主动关闭连接，这时 TCP 发送一个 FIN M；
2. 另一端接收到 FIN M 之后，执行被动关闭，对这个 FIN 进行确认。它的接收也作为文件结束符传递给应用进程，因为 FIN 的接收意味着应用进程在相应的连接上再也接收不到额外数据；
3. 一段时间之后，接收到文件结束符的应用进程调用 close 关闭它的 socket。这导致它的 TCP 也发送一个 FIN N；
4. 接收到这个 FIN 的源发送端 TCP 对它进行确认。

这样每个方向上都有一个 FIN 和 ACK。
