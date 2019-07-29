# Python中的迭代器
# 凡是可作用于for循环的对象都是Iterable类型；生成器都是Iterable类型；
# 凡是可作用于next()函数的对象都是Iterator类型，它们表示一个惰性计算的序列；
# 集合数据类型如list、dict、str等是Iterable但不是Iterator，不过可以通过iter()函数获得一个Iterator对象。
# Python的for循环本质上就是通过不断调用next()函数实现的


class Fib(object):
    def __init__(self, num):
        self._num = num
        self._a, self._b = 0, 1
        self._idx = 0

    def __iter__(self):
        return self

    def __next__(self):
        if self._idx < self._num:
            self._a, self._b = self._b, self._a+self._b
            self._idx += 1
            return self._a
        raise StopIteration


f = Fib(5)

print(next(f))
print(next(f))

for n in Fib(5):
    print(n)
