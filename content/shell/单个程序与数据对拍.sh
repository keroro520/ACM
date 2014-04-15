#!/bin/sh

WA=1
g++ test.cpp -o a.out

for i in *.in ; do 
	./ac.out < $i > out_ac
	j=${i%\.*}
	j="$j.out"

	if [ ! -d $j ] ; then 
		echo "$j 不存在"
		exit 2
	fi
	diff out_ac $j > /dev/null
	if [ ! $? -eq 0 ] ; then
		echo "WA at $i"
		exit $WA
	fi
done

echo "AC"
