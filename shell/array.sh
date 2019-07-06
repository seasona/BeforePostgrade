#!/bin/bash
# while array

while read line
do
    hosts[++i]=$line
done < /etc/hosts

echo "hosts first : ${hosts[1]}"

for i in ${!hosts[@]}
do
    echo "$i: ${hosts[i]}"
done

