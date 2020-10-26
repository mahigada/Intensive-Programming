#!/bin/sh
#Mahi Gada - CS288 003
#Number 4
declare -a arr
arr=("$@")
len=${#arr[@]}
for ((i = 0; i<$len; i++)) 
do
    for((j = 0; j<$len-$i-1; j++)) 
    do
      if [ ${arr[j]} -gt ${arr[$((j+1))]} ] #if left is greater than right
        then
            # switch two elements
            temp=${arr[j]} 
            arr[$j]=${arr[$((j+1))]}   
            arr[$((j+1))]=$temp 
        fi
    done
done
echo "${arr[@]}"