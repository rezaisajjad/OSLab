#!/bin/bash

while true;
do

tmp=0
reverse=0
sum=0

read -p "Enter a number or type 'end' to finish: " num 
if test "$num" = "end"
then
    exit 0
fi

while [ ! $num -eq 0 ]
do

let tmp=num%10;
let sum=sum+tmp;
let reverse=( reverse*10 )+tmp;
let num=num/10;
done

echo "Reverse is : $reverse";
echo "Sum of digits is : $sum";
done
