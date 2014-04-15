#!/bin/sh

AC=0
WA=1

g++ $1 -o a.out

for i in $2*.in ; do 
	./a.out < $i > out_test
	j=${i%\.*}
	j="$j.out"

	diff out_test $j > /dev/null
	if [ ! $? -eq 0 ] ; then
		exit $WA
	fi
done

exit $AC
