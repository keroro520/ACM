# 程序放在当前目录下。数据放在datapath下
# 数据以xxx.in 和 xxx.out格式
#!/bin/sh

datapath="./data/"
for file in *.c* ; do 
	sh check.sh $file $datapath 
	if [ $? -eq 0 ] ; then 
		echo  "$file AC"
	else echo "$file WA"
	fi
done
