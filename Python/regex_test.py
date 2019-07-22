import re


def qqRegex():
    username = input('请输入用户名:')
    qq = input('请输入qq:')
    if not re.match(r'^[\d\w_]{6,20}$', username):
        print('请输入正确的用户名')
    if not re.match(r'^[\d]{4,11}$', qq):
        print('请输入正确的qq号码')
    print('成功输入')


if __name__ == '__main__':
    qqRegex()
