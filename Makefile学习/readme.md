### 学习Makefile机制进行工程管理
-	了解Makefile的基本规则
-	了解变量定义VPATH和vpath的用法
-	了解%、$@、$<、$%等各类符号的意义
-	了解autoconf & automake的基本知识
具体要求：能看懂较为复杂的Makefile文件，可以按照需要修改已有的Makefile文件，通过Makefile对3个以上的子目录、10个以上的源代码文件进行管理。
<br>
$@  表示目标文件;
$^  表示所有的依赖文件;
$<  表示第一个依赖文件;
$?  表示比目标还要新的依赖文件列表

下面这个网址讲述的非常详细：
<https://seisman.github.io/how-to-write-makefile/index.html>
