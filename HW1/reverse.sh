#!/bin/sh
#Mahi Gada - CS288 003
# Number 2
function main(){
    reverse $1
    

}
function reverse(){
    declare -a arr2
    declare -a arr3
    arr2=`ls $1`
    for x in ${arr2[@]}
    do
        arr3=(  "$x" "${arr3[@]}" )
    done
    echo "${arr3[@]}"
}
main $1
