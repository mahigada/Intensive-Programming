#!/bin/sh
#Mahi Gada - CS288 003

function main(){
    echo "$4"
    if [[ "$4" == "breadth" ]];
    then
        breadthFirst $1 $2 $3
        tree $3
    fi
    if [[ "$4" == "depth" ]];
    then
        depthFirst $1 $2 $3
        tree $3
    fi
}
function depthFirst(){
    local depth=$1
	local breadth=$2
	local dir=$3
	
	if [ $depth -le 0 ]; then 
		return
	fi

	depth=$((depth-1))
    
	local breadthCount=$breadth

	while [[ $breadthCount > 0 ]]; do
	    mkdir -p $dir/$breadthCount
		depthFirst $depth $breadth $dir/$breadthCount
		let breadthCount--
	done 
}
function breadthFirst(){
    depth=$1
    breadth=$2
    open=($3)
    for ((i = 0; i<$depth; i++));
    do
        new=()
        for file in ${open[@]}
        do
            temp=()
            for ((j=0; j<$breadth; j++));
            do
                mkdir -p $file/$j
                new=(  "${new[@]}" "$file/$j" )
            done
            temp=(  "${temp[@]}" "${new[@]}" )
        done
        open=${temp[@]}
    done
}
main $1 $2 $3 $4
