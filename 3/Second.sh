#!/bin/bash

read -p "Enter First number : " num1
read -p "Enter Second number :" num2
read -p "which operator? (* / + -): " operator


echo -n "Result is "
case $operator in
	
	\*)
	echo "$(($num1 * $num2))"
	;;
	
	/)
	echo "$(($num1 / $num2))"
	;;
		
	
	+)
	echo "$(($num1 + $num2))"
	;;
	
	-)
	echo "$(($num1 - $num2))"	
	;;
esac
