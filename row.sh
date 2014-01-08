#!/bin/sh

sum=0
for file in `ls *.cpp`
do
    echo -n $file'  '
    lines=`wc -l $file|awk '{print $1;}'`
    sum=`expr $sum + $lines`
done


for file in `ls *.h`
do
    echo -n $file'  '
    lines=`wc -l $file|awk '{print $1;}'`
    sum=`expr $sum + $lines`
done

echo "\ntotal line is $sum"


