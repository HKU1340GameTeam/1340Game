#!/bin/bash

i=1
len=$1
Sep=""
while [ $i -le $len ]
do
    Sep+="*"
    i=$(($i+1))
done
echo "$Sep"
