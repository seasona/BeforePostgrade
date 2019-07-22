# Python中的网络通信，使用TCP连接，服务器向每个连接的客户端发送一张图片

from socket import socket, SOCK_STREAM, AF_INET
from base64 import b64encode
from json import dumps
from threading import Thread


def main():
    class FileTransferHandler(Thread):
        def __init__(self, cclient):
            super().__init__()
            self._cclient = cclient

        def run(self):
            my_dict = {}
            my_dict['filename'] = '1.jpg'

            # ? 这里的data是后面声明的，但这里却可以用，而且将类放在外面就不能用了
            my_dict['filedata'] = data
            # 通过dumps函数将字典处理成JSON字符串
            json_str = dumps(my_dict)
            self._cclient.send(json_str.encode('utf-8'))
            self._cclient.close()

    server = socket(family=AF_INET, type=SOCK_STREAM)
    server.bind(('127.0.0.1', 45577))
    server.listen(512)
    print('服务器启动开始监听...')
    with open('1.jpg', 'rb') as f:
        data = b64encode(f.read()).decode('utf-8')
    while True:
        client, addr = server.accept()
        FileTransferHandler(client).start()


if __name__ == '__main__':
    main()
