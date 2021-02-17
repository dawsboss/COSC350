#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Need atleast one number to add"
	exit 1
fi

sum=0
for i in $*;do
	sum=`expr $sum + $i`
done
echo "Sum of Arguments is "$sum"."
exit 0	
