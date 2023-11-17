#!/bin/bash
read -p "How many numbers do you want to enter?" many
declare -a numbers

for ((i=0;i<many;i++))
do
	read -p "" tmp
	numbers[$i]=$tmp
done

read -p "which operator ? (* / + -): " operator


case $operator in

	\*)
	tmp=${numbers[0]}
	for ((i=1;i<many;i++))
	do
		tmp=$((tmp * numbers[i]))
		
	done
	echo "$tmp"
	;;
	
	/)
	tmp=${numbers[0]}
	for ((i=1;i<many;i++))
	do
		tmp=$((tmp / numbers[i]))
		
	done
	echo "$tmp"
	;;

	+)
	tmp=${numbers[0]}
	for ((i=1;i<many;i++))
	do
		tmp=$((tmp + numbers[i]))
		
	done
	echo "$tmp"
	;;
	
	-)
	tmp=${numbers[0]}
	for ((i=1;i<many;i++))
	do
		tmp=$((tmp - numbers[i]))
		
	done
	echo "$tmp"
	;;
	
esac
