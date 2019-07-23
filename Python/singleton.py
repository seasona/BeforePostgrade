# 利用装饰器实现线程安全的单例

from functools import wraps
from theading import Lock


def singleton(cls):
    instances = {}
    locker = Lock()

    # 双重检查锁模式，c++中因为编译器执行顺序会出现问题，需要利用原子操作进行优化
    # Python中就没有这个问题，不得不感叹c++坑之多
    @wraps(cls)
    def wrapper(*args, **kwargs):
        if cls not in instances:
            with locker:
                if cls not in instances:
                    instances[cls] = cls(*args, **kwargs)
        return instances[cls]
    return wrapper


@singleton
class President():
    pass
