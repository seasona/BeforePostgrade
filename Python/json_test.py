# python处理json确实方便，类型对应共通的

import json


def jsonTest():
    mydict = {
        'name': "Tim",
        'age': 22,
        'qq': 345435345,
        'friends': ['Jack', 'Sarah'],
        'car': [
            {'brand': 'BYD', 'max_speed': 220},
            {'brand': 'AUTO', 'max_speed': 230},
            {'brand': 'BENZI', 'max_speed': 240}
        ]
    }

    try:
        with open('data.json', 'w', encoding='utf-8') as fs:
            json.dump(mydict, fs)
    except IOError as e:
        print(e)
    finally:
        print('save data success.')


if __name__ == '__main__':
    jsonTest()
