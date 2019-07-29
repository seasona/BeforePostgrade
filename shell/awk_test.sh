#!/bin/bash

# awk是按行处理的
# awk内置函数length，计算每行的字符个数，空格也计算在内
awk '{print length($0)}' sex.txt

# awk内置函数substr，对于每一行获取子字符串
awk '{print substr($0,2,2)}' sex.txt

# awk内置函数match，可以使用正则匹配，返回第一个匹配位置（从1开始），RSTART和RLENGTH是内置变量
awk 'BEGIN{start=match(" href=\"#waitpid\" this is hapi ",/href=\".*"/); print start, RSTART, RLENGTH }'