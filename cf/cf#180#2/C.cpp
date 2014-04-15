/*
    题意: 给出0/1串a,b, 问a串能否通过下面两个操作变成串b, 其中每个操作可以无限次使用
    -操作1 : 添加a的`奇偶性`到a的末尾. 若a的'1'有奇数个, 则添加'1', 反之'0'
    -操作2 : 把a的第一个字母删掉


    数学规律 : 原始a的'1'数cnt若是偶数个, 则a的'1'最多也只有cnt个; 否则, 最多可以有cnt+1个. 这个不难推出.
               若a的'1'最多(偶则cnt, 奇cnt+1) >= b的'1'数, 则a一定可以变换到b. 证明看官方题解.
                
*/
#include <string>
#include <iostream>
using namespace std;

int calc(string str)
{
    int sum = 0;
    for(string :: iterator it = str.begin(); it != str.end(); it++)
        sum += *it == '1';
    return sum;
}

int main()
{
    string a, b;
    cin >> a >> b;

    bool ans = (calc(a) + (calc(a) & 1)) >= calc(b);
    cout << (ans ? "YES" : "NO") << endl;
    return 0;
}
/*
官方题解 : http://www.codeforces.com/blog/entry/7437

Fact 0: If a has odd parity, we can apply operation 1 to increase its number of 1 by 1.

Fact 1: If a has a even parity, its number of 1 cannot increase anymore

If a has parity 0, unless we pop a 1, otherwise we cannot write a new 1 into a.

Fact 2: If the number of 1 in a is not less than the one in b, we can always turn a to b

The idea is to make a copy of b at the right of a. Lets assume a has even parity now. If we need a 0, simply apply operation 1. If we need a 1, keep remove from head until we remove a 1. Notice that we never remove digits from 'new part' of a. Now the parity of a will be odd and we can apply operation 1. After that, the parity of a becomes even again, the number of 1 in the 'old part' of a decrease by 1 and we handle a 1 in b.

Finally, remove the remain 'old part' of a. Now we get b.

Combine all those fact, we can conclude that we can turn a into b if and only if

        countOnes(a) + parity(countOnes(a)) ≥ countOnes(b)
*/
