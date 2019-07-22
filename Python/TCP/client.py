
from socket import socket
from json import loads
from base64 import b64decode


def main():
    client = socket()
    client.connect(('127.0.0.1', 45577))

    # 定义一个保存二进制数据的对象
    in_data = bytes()
    data = client.recv(1024)
    while data:
        in_data += data
        data = client.recv(1024)
    my_dict = loads(in_data.decode('utf-8'))
    filename = my_dict['filename']
    filedata = my_dict['filedata'].encode('utf-8')
    new_name = 'new_'+filename
    with open(new_name, 'wb') as f:
        f.write(b64decode(filedata))
    print('图片已保存')


if __name__ == '__main__':
    main()
