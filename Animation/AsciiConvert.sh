#!/bin/bash

framePath="frames/"
touch video.txt
i=1
len=$1
Sep=""
while [ $i -le $len ]
do
    Sep+="*"
    i=$(($i+1))
done
echo "$Sep"
echo "$Sep" > video.txt
imgs=`ls $framePath`
for img in $imgs:
do
    echo "${framePath}${img}"
    ascii-image-converter ${framePath}${img} -d $1,$2 >> video.txt
    echo "$Sep" >> video.txt
done

