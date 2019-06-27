
### 各种引号的区别
shell支持以下三种定义变量的方式

```shell
variable=value
variable='value'
variable="value"
```

variable 是变量名，value 是赋给变量的值。如果 value 不包含任何空白符（例如空格、Tab缩进等），那么可以不使用引号；如果 value 包含了空白符，那么就必须使用引号包围起来。注意，赋值号的周围不能有空格

```shell
#!/bin/bash

name=test;
variable1='单引号:${name}'
variable2="双引号:${name}"

echo ${variable1}
echo ${variable2}

#output:
#单引号:${name}
#双引号:test
```
以单引号' '包围变量的值时，单引号里面是什么就输出什么，即使内容中有变量和命令（命令需要反引起来）也会把它们原样输出。这种方式比较适合定义显示纯字符串的情况，即不希望解析变量、命令等的场景。
以双引号" "包围变量的值时，输出时会先解析里面的变量和命令，而不是把双引号中的变量名和命令原样输出。这种方式比较适合字符串中附带有变量和命令并且想将其解析后再输出的变量定义。

### 麻烦的空格

shell中的空格不像其他编程语言那样，要求很高，并不能够被省略

```shell
#!/bin/bash

var=$(expr 2 + 2)
echo "var=${var}"
```
等号两边必须要有空格， 2+2 是不对的，必须写成 2 + 2
