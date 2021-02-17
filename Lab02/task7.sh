#!/bin/bash 
echo “Enter the number you want the factorial of: ” 
read input 
saveInput=$input 
fac=1 
while [ $input -gt 0 ]; do 
    fac=`expr $input \* $fac` 
    echo "input: $input"
    echo "fac: $fac"
    input=`expr $input \- 1` 
done 
echo “The factorial of $saveInput is $fac” 
exit 0 

