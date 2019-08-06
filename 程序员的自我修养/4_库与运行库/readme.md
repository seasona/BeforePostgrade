<!-- TOC -->

- [函数返回值传递](#函数返回值传递)
    - [C++中的返回值优化](#c中的返回值优化)
        - [返回值优化（RVO）](#返回值优化rvo)
        - [具命返回值优化（NRVO）](#具命返回值优化nrvo)

<!-- /TOC -->

# 函数返回值传递

函数返回值的传递，如果小于4个字节，一般直接使用寄存器eax存储，如果5～8个字节，采用eax和edx联合返回。重点在于结构体等超过8字节的返回类型，下列是具体步骤：

- 首先main函数在栈上额外开辟了一片空间，并将这块空间的一部分作为传递返回值的临时对象，这里称为temp
- 将temp对象的地址作为隐藏参数传递给return_test函数
- return_test函数将数据拷贝给temp对象，并将temp对象的地址用eax传出
- return_test返回之后，main函数将eax指向的temp对象的内容拷贝给n

所以如果返回值的尺寸太大，c语言在函数返回时会使用一个临时的栈上内存作为中转，结果返回值对象会被拷贝两次。因此不到万不得已，不要轻易返回大尺寸的对象。

## C++中的返回值优化

```cpp
#include <iostream>
using namespace std;

class CppObj {
public:
    CppObj() { cout << "ctor\n"; }
    CppObj(const CppObj& c) { cout << "copy ctor\n"; }
    CppObj& operator=(const CppObj& chs) {
        cout << "operator=\n";
        return *this;
    }
    ~CppObj() { cout << "dtor\n"; }
};

CppObj returnTest() {
    CppObj b;
    cout << "before return\n";
    return b;
}

int main() {
    CppObj n;
    n = returnTest();
    return 0;
}
```

如上代码，按道理来说输出应该为：

```
ctor
ctor
before return
copy ctor
dtor
operator=
dtor
dtor
```

但实际上的输出为：

```
ctor
ctor
before return
operator=
dtor
dtor
```

按照道理来说，return_test()返回CppObj为临时对象，应该先调用CppObj类的复制构造函数，然后对b调用析构函数，但最终着两步是不存在的，这其实就牵涉到C++的编译器优化——返回值优化（RVO）与具命返回值优化（NRVO）：

### 返回值优化（RVO）

```cpp
CppObj returnTest(){
    return CppObj();
}
```

这种场合下，这个临时对象会消耗一个构造函数的调用、一个复制构造函数的调用以及一个析构函数的调用的代价，通过返回值优化，可以将后两步省略，只会消耗一个构造函数的成本。

具体的方式是编译器通过直接传递n = returnTest()中的n的引用，利用n取代returnTest()中的匿名对象

### 具命返回值优化（NRVO）

```cpp
CppObj returnTest() {
    CppObj b;
    cout << "before return\n";
    return b;
}
```

对于按值返回“具名对象”（就是有名字的变量）时的优化手段，其实道理是一样的，但由于返回的值是具名变量，情况会复杂很多，所以，能执行优化的条件更苛刻。

具体的细节部分看这个[博客](https://www.cnblogs.com/xkfz007/articles/2506022.html)

