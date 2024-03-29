<!-- TOC -->

- [从Hello World引出的问题](#%e4%bb%8ehello-world%e5%bc%95%e5%87%ba%e7%9a%84%e9%97%ae%e9%a2%98)
- [过度优化会导致线程非安全](#%e8%bf%87%e5%ba%a6%e4%bc%98%e5%8c%96%e4%bc%9a%e5%af%bc%e8%87%b4%e7%ba%bf%e7%a8%8b%e9%9d%9e%e5%ae%89%e5%85%a8)

<!-- /TOC -->

## 从Hello World引出的问题

- 程序为什么要被编译器编译了之后才可以开始运行？<p>
因为需要通过编译将高级语言变成计算机可以识别的2进制语言，因为只有0和1的二进制语言可读性较差，所以一般转化为十六进制的机器码，机器码和汇编是一一对应的，通过反汇编就可以把机器码转为汇编代码
- 编译器在把c语言程序转换成可以执行的机器码的过程中做了什么，怎么做的？<p>
经过了预处理、编译、汇编和链接四个过程

## 过度优化会导致线程非安全

- 不同线程中的寄存器是相互独立的，所以如果编译器在进行优化时将不同线程的中的同一个变量放入不同的寄存器，就会导致线程非安全
- 编译器调整语句的执行顺序导致过度优化，典型例子就是单例中的double-check模式

通过volatile可以完美解决第一个问题，但是对第二个问题无能为力。因为就算volatile能阻止编译器调整顺序，也无法阻止cpu动态调度换序。

因此需要使用memory-fence对指令的执行顺序进行规定。通常情况下是调用cpu提供的一条指令，这条指令会阻止cpu将该指令之前的指令交换到它之后，x86中的指令为:

```c
#define fence() __asm__ volatile("" ::: "memory")
```

C11中通过使用Acquire and Release Fences等原子操作解决这个问题，比如利用atomic_thread_fence等


