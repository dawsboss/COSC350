#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Need an integer to add"
	exit 1
fi
input=$1
sum=0

for i in $@
do
	if [ `expr $i % 2` -eq 1 ]; then
		sum=`expr $sum + $i`
	fi

done

echo "Sum of ODD Arguments is "$sum"."
exit 0	
