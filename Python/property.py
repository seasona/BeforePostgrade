# 使用@property装饰器可以比较方便的读取和修改类中的属性
# 但是无论怎样，python中类的成员都是公有的，可以随意修改


class Person(object):
    __slots__ = ('_name', '_age', '_retarded')

    def __init__(self, name, age):
        self._name = name
        self._age = age

    @property
    def name(self):
        return self._name

    # 装饰器-getter方法
    @property
    def age(self):
        return self._age

    @age.setter
    def age(self, age):
        self._age = age

    def play(self):
        if self._age < 13:
            print("%s watch xiyangyang" % self._name)
        else:
            print("%s watch rick and motiy" % self._name)

    @staticmethod
    def isRetarded(retarded):
        if retarded == True:
            print("Is a idiot, can't watch TV.")

    # classmethod相比较staticmethod的优势在于可以使用cls来实例化对象
    @classmethod
    def newPerson(cls, name):
        return cls(name, 12)


def main():
    retarded = True
    if(Person.isRetarded(retarded)):
        p = Person('Tom', 11)
        p._age = 10
        print(p._age)  # python类中成员始终都是公有的
        print(p._name)
        p.play()
        print(p.age)
        p.age = 20
        p.play()


if __name__ == "__main__":
    main()
