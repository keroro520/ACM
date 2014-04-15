# 对拍程序  与标称对拍，AC.cpp 与 test.cpp

#!/bin/sh

WA=1
g++ AC.cpp -o ac.out				#标程
g++ test.cpp -o a.out				#测试程序

for i in *.in ; do 
	./ac.out < $i > out_ac
	./a.out  < $i > out_test
	diff out_ac out_test > /dev/null
	if [ ! $? -eq 0 ] ; then
		echo "WA at $i"
		exit $WA
	fi
done

echo "AC"
