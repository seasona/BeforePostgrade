# Python中的协程
# 协程与线程最大的不同在于：多线程之间通信需要操作系统底层的调度，所以加锁或者信号量速度慢
# 协程在同一个线程内跳转，所以不需要加锁，调度由程序本身完成，因此速度快，但是需要语言本身支持
# Python对协程的支持是通过生成器实现的


def consumer():
    r = ''
    while True:
        n = yield r
        if not n:
            return
        print('[CONSUMER] Consuming %s...' % n)
        r = '200 OK'


def producer(c):
    # 启动consumer()，先让它在n=yield r出卡住
    # 下一步就开始赋值
    c.send(None)
    n = 0
    while n < 5:
        n = n+1
        print('[PRODUCER] Producing %s...' % n)
        r = c.send(n)
        print('[PRODUCER] Consumer return: %s' % r)
    c.close()


c = consumer()
producer(c)
