#!/bin/bash
# function use array to pass parameter

num=(1 2 3)

array(){
    local factorial=1
    for i in $@
    do
        let factorial*=i
    done
    echo "$factorial"
}

array ${num[@]}
