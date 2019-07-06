#!/bin/bash
# learn function in shell

factorial(){
    num=1;
    for((i=1;i<=$1;i++))
    do
        num=$[$num * $i]
    done
    echo "5的阶乘是: $num"
}

factorial $1
