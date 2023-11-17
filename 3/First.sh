#!/bin/bash
if [ $# -ne 2 ]; then
	echo "invalid number of input"
	exit 1
fi

for i in "${@}"; do
	if [[ ! $i =~ ^[0-9]+$ ]]; then
		echo "$i is invalid value"
		exit 1
	fi
done

echo "sum is $(($1 + $2))"

if   [ $1 -gt $2 ]
then 
	echo "Greater number is $1"
elif [ $1 -lt $2 ]
then
	echo "Greater number is $2"
else echo "$1 is euqal with $2"
fi


