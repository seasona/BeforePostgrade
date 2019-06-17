#!/usr/bin/bash
## this is a script to add usr
## 注意不要在win下写shell脚本，因为win下的换行是回车符+换行符，也就是\r\n,而unix下是换行符\n。linux下不识别\r为回车符，所以导致每行的配置都多了个\r
## 只有[[]]中可以使用正则，[]中是不行的

read -p "Please input number: " num
if [[ ! "$num" =~ ^[0-9]+$ ]];then
	echo "error number!"
	exit
fi

read -p "Please input prefix: " prefix

for i in `seq $num`
do
	user=$prefix$i
	useradd $user
	echo "123"| passwd -stdin $user &>/dev/null
done
