# Python中的异步IO
# asyncio的编程模型就是一个消息循环。我们从asyncio模块中直接获取一个EventLoop的引用，
# 然后把需要执行的协程扔到EventLoop中执行，就实现了异步IO。
# 异步IO的特点当代码需要执行一个耗时的IO操作时，它只发出IO指令，
# 并不等待IO结果，然后就去执行其他代码了。一段时间后，当IO返回结果时，再通知CPU进行处理。

import asyncio
import threading


async def hello():
    print('Hello world! (%s)' % threading.currentThread())
    r = await asyncio.sleep(1)
    print('Hello again! (%s)' % threading.currentThread())


loop = asyncio.get_event_loop()
tasks = [hello(), hello()]
loop.run_until_complete(asyncio.wait(tasks))
loop.close()
