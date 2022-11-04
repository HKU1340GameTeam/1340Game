#!/bin/bash

files="`ls *.cpp`"
sum=0
for file in $files
do
    b="`wc -l $file | cut -d\" \" -f1`"
    let "sum=$sum+$b"
    echo "$file $b"
done
echo "total = $sum"
