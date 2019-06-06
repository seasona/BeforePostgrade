### IO总结
IO一般分为五种：
- Blocking IO - 阻塞IO
- NoneBlocking IO - 非阻塞IO
- IO multiplexing - IO多路复用
- signal driven IO - 信号驱动IO
- asynchronous IO - 异步IO

在讨论之前先说明一下IO发生时涉及到的对象和步骤，对于一个network IO，它会涉及到两个系统对象：
- application 调用这个IO的进程
- kernel 系统内核

那他们经历的两个交互过程是：

- 阶段1 wait for data 等待数据准备
- 阶段2 copy data from kernel to user 将数据从内核拷贝到用户进程中

#### 阻塞IO
简单的说就是，内核还没准备好数据，用户进程就堵塞起来知道内核数据准备好

#### 非堵塞IO
内核还没准备好数据也不会把进程堵塞起来，而是立刻返回一个结果。从用户进程角度讲 ，它发起一个操作后，并没有等待，而是马上就得到了一个结果。用户进程其实是需要不断的主动询问kernel数据好了没有。一旦kernel中的数据准备好了，并且又再次收到了用户进程的system call，那么它马上就将数据拷贝到了用户内存，然后返回。

#### IO多路复用
I/O多路复用(multiplexing)是网络编程中最常用的模型，像我们最常用的select、epoll都属于这种模型。
看起来它与blocking I/O很相似，两个阶段都阻塞。但它与blocking I/O的一个重要区别就是它可以等待多个数据报就绪（datagram ready），即可以处理多个连接。这里的select相当于一个“代理”，调用select以后进程会被select阻塞，这时候在内核空间内select会监听指定的多个datagram (如socket连接)，如果其中任意一个数据就绪了就返回。此时程序再进行数据读取操作，将数据拷贝至当前进程内。由于select可以监听多个socket，我们可以用它来处理多个连接。
在select模型中每个socket一般都设置成non-blocking，虽然等待数据阶段仍然是阻塞状态，但是它是被select调用阻塞的，而不是直接被I/O阻塞的。select底层通过轮询机制来判断每个socket读写是否就绪。
当然select也有一些缺点，比如底层轮询机制会增加开销、支持的文件描述符数量过少等。为此，Linux引入了epoll作为select的改进版本。


这个网址讲的比较详细:
<https://devarea.com/linux-io-multiplexing-select-vs-poll-vs-epoll/>
<https://www.jianshu.com/p/397449cadc9a>

