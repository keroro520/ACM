/*
    组合数学  容斥定理

    题意: 给出可能包含数字或'?'的长度为n的字符串a,b, 问: a,b字符串里面的'?'可以随意以数字(1-9)替换, 有多少种方法数使得a,b为incomparable. 所谓的incomparable是指满足条件: 存在i, j(1 <= i,j <= n), 使得ai > bi 且 aj < bj
    结果mod 1000000007


    思路: 第一次写容斥的题目.
          sum_ab不可比 = 总情况数 + ab相等情况数 - a大于等于b情况数 - b大于等于a情况数

          ***注意点*** 最后的结果模MOD的时候一定要记得先加上MOD!! 详情看main函数最后的代码注注释 
*/
#include <iostream>
#include <string>
using namespace std;

#define MOD 1000000007

int n;

long long square(long long x) { return x * x; }
long long powMod(int x, int e, int mod)
{
    if(e == 0) return 1 % mod;
    long long res = square( powMod(x, e>>1, mod) ) % mod;   //别忘了. 不加%mod可能溢出.
    res *= (e & 1) ? x : 1;
    return res % mod;
}
long long equal_(string a, string b)
{
    long long sum = 1;
    for(int i = 0; i < n; i++)
        if(a[i] != '?' && b[i] != '?') {
            if(a[i] != b[i]) return 0;
        } else if(a[i] == '?' && b[i] == '?') {
            sum = sum * 10 % MOD;
        }
    return sum;
}
long long greater_equal_(string a, string b)
{
    long long sum = 1;
    for(int i = 0; i < n; i++) {
        if(a[i] != '?' && b[i] != '?') {
            if(a[i] < b[i]) return 0;
        } else if(a[i] == '?' && b[i] == '?') {
            sum *= 55;
        } else if(a[i] == '?') {
            sum = sum * (10 - (b[i] - '0'));
        } else {
            sum = sum * (a[i] - '0' + 1);
        }
        sum %= MOD;
    }
    return sum;
}
int calc(string str)
{
    int sum = 0;
    for(int i = 0; i < n; i++) sum += (str[i] == '?');
    return sum;
	//return count(str, '?');
}
int main()
{
    string a, b;
    cin >> n >> a >> b;
    int tot = calc(a) + calc(b);
    long long ans = (powMod(10, tot, MOD) + equal_(a, b) - greater_equal_(a, b) - greater_equal_(b, a) + MOD) % MOD;    //TODO !!! 要先加上MOD再最后模, 因为C++里的负数模结果是负数
    cout << ans << endl;
    return 0;
}
