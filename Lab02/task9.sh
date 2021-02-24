#!/bin/bash

echo "Give absolute path to the file's directory (Don't forget the '/' at the end): "
read dir
if [ ${dir:0:1} == '~' ];then
	dir="${HOME}/${dir:2}"
fi

if ! [ -d "$dir" ];then
	echo "Invalid file path"
	exit 1 # Failed exit - Not valid path
fi

echo "Name of file you are searching for:"
read fileI
file=$dir # Make the ablslute path for search
file+=$fileI
i=0
while ! [ -f "$file" ];do # Ask user 3 times for a file in the given dir
	#echo "file: $file"
	if [ $i -ge 2 ];then
		echo "Invalid file entered 3 times"
		exit 2 # Failed exit - INvalid file 3 times
	fi
	echo "Invalid file, try again: "
	read fileI
	file=$dir
	file+=$fileI
	i=`expr $i + 1`
done

echo "What word would you like to search for: "
read word # User input for searched word

if ! [ -r $"$file" ];then
	echo "File not readable!"
	exit 3 # Failed exit - File not readable
fi

if ! [ -z "$(grep $word "$file")" ];then
	echo "FOUND $word in $file"
else
	echo "NOT FOUND $word in $file"
	exit 4 # Failed exit - word not found
fi
exit 0 # Succesful exit
