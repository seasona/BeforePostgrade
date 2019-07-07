#!/bin/bash
# how to return a value a string by function
# 使用$?来获取函数的返回值不能超过shell的上限255，可以使用echo来返回字符串或者数值
# 但这样会返回所有echo打印到屏幕上的数据

func2(){
    #echo "use echo to return a value"
    read -p "enter the num: " num
    echo $[2*$num]
}

result=`func2`
echo "function2 return value $result"
