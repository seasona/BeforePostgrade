# python中的多态，因为是动态语言，所以函数什么传参时不需要像c++那样使用基类指针来传递子类
# 所以意义主要类似于JAVA中的接口，只要@abstractmethod了，基类就不能够实例化了

from abc import abstractmethod, ABCMeta


class Pet(object, metaclass=ABCMeta):
    def __init__(self, nickname):
        self._nickname = nickname

    @abstractmethod
    def makeVoice(self):
        pass


class Dog(Pet):
    def __init__(self, breed):
        super().__init__('badi')
        self._breed = breed

    def makeVoice(self):
        print("%s 汪汪汪 %s" % (self._nickname, self._breed))


class Cat(Pet):
    def __init__(self, breed):
        super().__init__('mimi')
        self._breed = breed

    def makeVoice(self):
        print("%s 喵喵喵 %s" % (self._nickname, self._breed))


def makeVoice(pet):
    pet.makeVoice()


if __name__ == "__main__":
    cat = Cat("波斯")
    dog = Dog("土狗")
    makeVoice(cat)
    makeVoice(dog)
