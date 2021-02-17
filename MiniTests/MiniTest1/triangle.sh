#!/bin/bash
echo "Entr a number that is odd and greater than 3: "
read input
if [ `expr $input % 2` -eq 0 ] || [ $input -lt 3 ];then
	echo "Invalid number"
	exit 1
fi

numSpace=`expr $input / 2`
numStar=1

for i in $(seq 0 $numSpace);do
	for j in $(seq 1 $numSpace);do
		echo -n " "
	done
	for k in $(seq 1 $numStar);do
		echo -n "*"
	done
	numStar=`expr $numStar + 2`
	numSpace=`expr $numSpace - 1`
	echo
done
exit 0
