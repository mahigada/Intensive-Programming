#!/bin/sh
#Mahi Gada - CS288 003
# Number 1
declare -a arr
arr=`ls /usr/bin`
for i in {a..z}
do
count=0
    for x in ${arr[@]}
    do
    firstchar=${x:0:1}
        if [ $firstchar == $i ] 
        then count=$((count+1))
        fi
    done
    echo "$i $count"
done