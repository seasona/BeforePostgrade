### 学习Makefile机制进行工程管理
-	了解Makefile的基本规则
-	了解变量定义VPATH和vpath的用法
-	了解%、$@、$<、$%等各类符号的意义
-	了解autoconf & automake的基本知识
具体要求：能看懂较为复杂的Makefile文件，可以按照需要修改已有的Makefile文件，通过Makefile对3个以上的子目录、10个以上的源代码文件进行管理。

#### makefile默认使用make只执行第一条命令
```Makefile
all: spdlog_test benchmark_test

spdlog_test: spdlog_test.cc
	g++ -o $@ $(CXXFLAGS) $^
benchmark_test: benchmark_test.cc
	g++ -o $@ $^ -std=c11 -pthread -lbenchmark $(CXXFLAGS) 
```
如果不写all，make只执行spdlog_test为止

#### 下面这个网址讲述的非常详细：
<https://seisman.github.io/how-to-write-makefile/index.html>
