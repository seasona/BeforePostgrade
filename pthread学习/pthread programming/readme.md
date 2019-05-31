
### 总结

<https://computing.llnl.gov/tutorials/pthreads/>
在线看的学习pthread的一本书，逻辑清晰，内容详尽，非常不错，英语看起来也毫无压力，有很多例子练习和问题，非常适合pthread入门。

### 一些问题

#### thread被create之后什么时候run？

之前一直在思考这个问题，pthread_create或者c11中的thread构造之后，这个线程什么时候开始运行呢？是create之后立即开始执行吗？
<p>其实执行的时间是由操作系统决定的，所以无法知道确切的时间，因此需要设计的时候避免线程按序运行的情况