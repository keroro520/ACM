#!/bin/sh
for((i=1;i<=20;i++));do
    g++ random.cpp&& ./a.out > in &&  g++ try.cpp && ./a.out < in> 1 && g++ test.cpp&& ./a.out < in > 2 && diff 1 2 && echo "done" + $i
done;

