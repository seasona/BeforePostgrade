### IO多路复用
IO多路复用就是原本端口监听需要分配进程来检测，但是端口一多，分配进程肯定不是个好办法。Linux内核可以通过select或poll等来完成检测端口也就是文件的作用。

这个网址讲的比较详细:
<https://devarea.com/linux-io-multiplexing-select-vs-poll-vs-epoll/>

