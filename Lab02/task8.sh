#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Need an integer to add"
	exit 1
fi
input=$1
sum=0
while [ $input -gt 0 ]; 
do
	next=`expr $input \% 10`
	sum=`expr $sum + $next`
	input=`expr $input / 10`
	
done
echo "Sum of Arguments is "$sum"."
exit 0	
