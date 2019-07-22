
from multiprocessing import Process
from os import getpid
from random import randint
from time import time, sleep


def downlandTask(filename):
    print('启动下载进程，进程号[%d].' % getpid())
    print('开始下载%s...' % filename)
    time_to_downland = randint(5, 10)
    sleep(time_to_downland)
    print('%s下载完成！耗费了%d秒' % (filename, time_to_downland))


def main():
    start = time()
    # 创建进程，注意这里args中','不能少，因为args需要是一个元组，通过加上一个','将单个参数转换为元组
    p1 = Process(target=downlandTask, args=('python learning.pdf',))
    p2 = Process(target=downlandTask, args=('think in JAVA.pdf',))
    p1.start()
    p2.start()
    p1.join()
    p2.join()
    end = time()
    print('总共耗费了%.2f秒' % (end-start))


if __name__ == '__main__':
    main()
