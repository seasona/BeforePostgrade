CC=gcc

#编译器选项
#?-Isrc可以神奇的忽略头文件的路径问题
CFLAGS=-Wall -Isrc

#链接器选项
LDLIBS=-pthread

TARGETS=test/thrdtest

#使用Makefile中的隐含规则 
test/thrdtest: test/thrdtest.o src/PthreadPool.o

#test/thrdtest.o: test/thrdtest.c 
#src/PthreadPool.o: src/PthreadPool.c 

.PHONY: clean test

#使用通配符*可以清除所有路径下的.o文件
clean:
	rm -f $(TARGETS) */*.o

test:
	./test/thrdtest

