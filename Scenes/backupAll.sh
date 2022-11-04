#!/bin/bash
files=`ls`
for file in $files:
do
    echo "$file"
    cp $file "$file.bak"
done
