# python中的装饰器


def newDecorator(func):
    def wrapTheFunction():
        print('I am doing something before executing func()')
        func()
        print('I am doing something after executing func()')

    return wrapTheFunction


@newDecorator
def functionRequireDecoration():
    print('I am the function!')


# 使用装饰器的作用在于直接运行需要被装饰的函数
functionRequireDecoration()

# 不使用装饰器就需要这样使用
newDecorator(functionRequireDecoration)()
