#!/bin/bash
#This will make a file that has min through max and each number is on it's own line

#min=`expr 1`
#max=`expr 100`
#for((i=$min;`expr i<=$max`;i++)); 
#do 
#	$i >> numbs
#done
#exit 0

for i in $(seq 1 100);do
	echo $i>>numbs
done

exit 0
