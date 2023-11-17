#!/bin/bash

read -p "Enter x: " x
read -p "Enter y: " y
read -p "Enter name of file: " file
head -n $y $file | tail -n $(($y - $x + 1))
