#!/bin/bash
echo "Entr a number that is odd and greater than 3: "
read input # Head length/size
read tailL #Tail's length
if [ `expr $input % 2` -eq 0 ] || [ $input -lt 3 ];then
	echo "Invalid number"
	exit 1
fi

numSpace=`expr $input - 1`
numStar=1

for i in $(seq 0 `expr $numSpace / 2`);do
	if [ $numStar -eq $input ];then
		for k in $(seq 1 $tailL);do
			echo -n "*"
		done
	else
		for j in $(seq 1 $tailL);do
			echo -n " "
		done
	fi

	for k in $(seq 1 $numStar);do
		echo -n "*"
	done
	numStar=`expr $numStar + 2`
	numSpace=`expr $numSpace - 2`
	echo
done


numStar=`expr $input \- 2`
numSpace=2
for i in $(seq $numStar -1 1);do
	for j in $(seq $tailL -1 1);do
		echo -n " "
	done
	for k in $(seq $numStar -1 1);do
		echo -n "*"
	done
	numStar=`expr $numStar \- 2`
	numSpace=`expr $numSpace + 2`
	echo
done

exit 0
