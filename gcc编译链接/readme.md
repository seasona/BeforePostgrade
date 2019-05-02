[TOC]
### 学习gcc编译连接
- CFLAGS
- LDFLAGS
- -L, -l,-I
- LD_LIBRARY_PATH & LIBRARY_PATH

#### CFLAGS和LDFLAGS

CFLAGS和LDFLAGS其实都只是自定义的变量，CFLAGS用于编译，LDFLAGS用于链接，从变量名也能看出来C(compile)_FLAGS、LD(链接器ld)\_FLAGS：

##### GCC编译选项CFLAGS参数:

|选项| 	说明|
|-------|-------|
|-c| 	用于把源码文件编译成 .o 对象文件,不进行链接过程|
|-o| 	用于连接生成可执行文件，在其后可以指定输出文件的名称|
|-g| 	用于在生成的目标可执行文件中，添加调试信息，可以使用GDB进行调试|
|-Idir| 	用于把新目录添加到include路径上，可以使用相对和绝对路径，<br>“-I.”、“-I./include”、“-I/opt/include”|
|-Wall| 	生成常见的所有告警信息，且停止编译|
|-w| 	关闭所有告警信息|
|-O| 	表示编译优化选项，其后可跟优化等级0\1\2\3，默认是0，不优化|
|-fPIC| 	用于生成位置无关的代码|
|-v| 	(在标准错误)显示执行编译阶段的命令，同时显示编译器驱动程序,预处理器,编译器的版本号|

##### GCC链接选项LDFLAGS参数:

|选项| 	说明|
|-|-|
|-llibrary| 	链接时在标准搜索目录中寻找库文件，搜索名为liblibrary.a 或 liblibrary.so|
|-Ldir| 	用于把新目录添加到库搜索路径上，可以使用相对和绝对路径，“-L.”、“-L./include”、“-L/opt/include”|
|-Wl,option |	把选项 option 传递给连接器，如果 option 中含有逗号,就在逗号处分割成多个选项|
|-static| 	使用静态库链接生成目标文件，避免使用共享库，生成目标文件会比使用动态链接库大|
