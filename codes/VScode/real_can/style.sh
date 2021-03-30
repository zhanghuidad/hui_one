#!/usr/bin/env bash

dir=`pwd`

filelist=`find $dir -type f -name "*.c" -or -name "*.cpp" -or -name "*.cc" -or -name "*.h" -or -name "*.hpp"`  

for file in $filelist
do
    astyle --style=linux --indent=spaces=4 --indent-switches $file
done    

filelist=`find $dir -type f -name "*.orig"`

for file in $filelist
do
    rm $file
done
