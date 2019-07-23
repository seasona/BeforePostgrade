# 利用互译无线短信接口来发送短信

import urllib.parse
import http.client
import json


def main():
    host = "106.ihuyi.com"
    sms_send_uri = "/webservice/sms.php?method=Submit"
    # 下面的参数需要填入自己注册的账号和对应的密码
    params = urllib.parse.urlencode({'account': 'C86632796', 'password': '8d56e7164781086f203f24545e8ed4bd ',
                                     'content': '您的验证码是：121254。请不要把验证码泄露给其他人。', 'mobile': '18357194758', 'format': 'json'})
    headers = {'Content-type': 'application/x-www-form-urlencoded',
               'Accept': 'text/plain'}
    conn = http.client.HTTPConnection(host, port=80, timeout=30)
    conn.request('POST', sms_send_uri, params, headers)
    response = conn.getresponse()
    response_str = response.read()
    jsonstr = response_str.decode('utf-8')
    print(json.loads(jsonstr))
    conn.close()


if __name__ == '__main__':
    main()
