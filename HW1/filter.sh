#!/bin/sh
#Mahi Gada - CS288 003
#Number 3
declare -a arr2
arr2=(`ls -l $1 | tr -s ' ' | cut -d ' ' -f 5`)
function main(){
    average $1
    filter $1
}
function average(){
    
    count=0
    totalSize=0
    for x in ${arr2[@]}
    do
        let totalSize+=$x
        count=$((count+1))
    done 
    average=$(( totalSize / count ))
    #echo "$average"
}
function filter(){
    declare -a arr
    declare -a arr3
    arr=(`ls $1`)
    arr3=()
    count=0
    for x in ${arr[@]}
    do 
        if [ "${arr2[$count]}" -gt $average ]
        then 
            arr3+=("${arr[$count]}")
        fi
        count=$((count+1))
    done
    echo "${arr3[@]}"
}
main $1