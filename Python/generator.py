# Python中的生成器
# 一个带有yield的函数就是一个generator，它和普通函数不同，生成一个generator看起来像函数调用，但不会执行任何函数代码，直到对其调用next()才开始执行。
# 虽然执行流程仍按函数的流程执行，但每执行到一个yield语句就会中断，并返回一个迭代值，下次执行时从yield的下一个语句继续执行。
# 看起来就好像一个函数在正常执行的过程中被yield中断了数次，每次中断都会通过yield返回当前的迭代值。
# yield的好处是显而易见的，把一个函数改写为一个generator就获得了迭代能力，比起用类的实例保存状态来计算下一个next()的值，不仅代码简洁，而且执行流程异常清晰。


def fib(num):
    a, b = 0, 1
    for _ in range(num):
        a, b = b, a+b
        yield a


f = fib(5)

for n in fib(5):
    print(n)

print(next(f))
print(next(f))
