# 利用qq邮箱的SMTP服务器发送邮件

from smtplib import SMTP
from email.header import Header
from email.mime.text import MIMEText
from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart

import urllib


def sendMessage():
    message = MIMEMultipart()
    text_content = MIMEText('附件中有本月数据请查收', 'plain', 'utf-8')
    message['Subject'] = Header('本月数据', 'utf-8')
    message.attach(text_content)

    # 附件有些问题
    with open('data.json', 'r') as f:
        txt = MIMEText(f.read(), 'base64', 'utf-8')
        txt['Content-Type'] = 'text/plain'
        txt['Content-Dispostion'] = 'attachment;filename=data.json'
        message.attach(txt)

    smtper = SMTP('smtp.qq.com')
    sender = '396438446@qq.com'
    receivers = ['451629463@qq.com']
    smtper.login(sender, 'eohwqoqryffvbgjc')
    smtper.sendmail(sender, receivers, message.as_string())
    smtper.quit()
    print('发送完成')


if __name__ == '__main__':
    sendMessage()
