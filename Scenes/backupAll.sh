#!/bin/bash

rm *.bak
files="`ls`"
for file in $files:
do
    echo "creating backup for $file"
    cp $file $file.bak
done
