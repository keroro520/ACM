#!/bin/sh

n=50
echo  $n
for i in $(seq 50) ; do 
	echo $(($RANDOM % 48 + 1))
done
