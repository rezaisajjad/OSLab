#!/bin/bash

function first(){
        for i in 1 2 3 4 5
        do
                for ((j=1;j<=$i;j++))
                do
                        echo -n "$i "
                done
                echo
        done
}

function second(){
        for i in 1 2 3 4 5 6
        do
                for ((j=5;j>=$i;j--))
                do
                        echo -n " "
                done
                for ((j=1;j<=$i;j++))
                do
                        echo -n "* "
                done
                echo
        done
        for i in 1 2 3 4 5 6
        do
                for ((j=1;j<$i;j++))
                do
                        echo -n " "
                done
                for ((j=6;j>=$i;j--))
                do
                        echo -n "* "
                done
                echo
        done

}

function third(){
        for ((i=1;i<=5;i++))
        do

                for ((j=1;j<$i;j++))
                do
                        echo -n "| "
                done
                echo "|_"
        done
}
read -p "Enter 1 or 2 or 3 :" num
case $num in
        "1")
                first
                ;;
        "2")
                second
                ;;
        "3")
                third
                ;;
esac
