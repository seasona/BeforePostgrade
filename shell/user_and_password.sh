#!/bin/bash
# this script create user with name and password by the file given

if [ $# -eq 0 ];then
    echo "usage: `basename $0` file"
    exit 1
fi

if [ ! -f $1 ];then
    echo "error file"
    exit 2
fi

#for是按照空格分隔，因此需要重新定义分隔符
#IFS内部字段分隔符
IFS=$'\n'

for line in $(cat $1)
do
    if [ ${#line} -eq 0 ];then
        continue
    fi
    user=$(echo "$line"|awk '{print $1}')
    pass=$(echo "$line"|awk '{print $2}')
    id $user &>/dev/null
    if [ $? -eq 0 ];then
        echo "user $user already exists"
    else
        echo "user $user added"
        echo "password $pass"
        #echo "$pass"|passwd --stdin $user &>/dev/null
        #if [ $? -eq 0 ];then
        #    echo "$user is create."
        #fi
    fi
done

