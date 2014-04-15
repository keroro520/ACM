/*
    排列题

    题意：给出n，问符合ci = (ai - 1 + bi - 1) mod n + 1 的情况有多少？

    思路：易知对于某一排列{A}，若有K种{B}满足条件，则答案一共有K*P(n,n)种情况。
          
          我是用dfs暴力算K，但还是会超时，题解无耻地给出了打表的方法...说是有DP解法，但没公布，看起来好难的样子。

          写下一个证明：n为偶数时，无解。
                    证：假设存在满足条件{A},{B},{C}，对于{A},{B}序列的每个元素都减1先，则
                        sum{A} mod n = sum{B} mod n = (n-1)*n/2 mod n                                   <1>
                        sum{C} mod n = sum{ai+bi} mod n = (sum{A} + sum{B}) mod n = n*(n-1) mod n = 0   <2>

                        当n为偶数时，<1>式 = n/2  ...... (证明：(n-1)*n/2 = n^2/2 - n/2 mod n = n/2)
                        而<2> = 0，此时<1> != <2>，所以无解，假设不成立.
*/
#include <iostream>
using namespace std;
#define     MOD     1000000007
long long ans = 0;
int n;
bool used[17], exist[17];
void dfs(int floors)
{
    if(floors == n+1) {
        ans++;
        return ;
    }
    for(int i = 1; i <= n; i++) if(!used[i]) {
        int tmp = (i + floors - 2) % n + 1;
        if(!exist[tmp]) {
            exist[tmp] = used[i] = true;
            dfs(floors+1);
            exist[tmp] = used[i] = false;
        }
    }
}
long long P(int n, int m)
{
    long long sum  = 1;
    for(long long i = n-m+1; i <= n; i++)
        sum = sum * i % MOD;
    return sum;
}
int main()
{
    cin >> n;
    if(n % 2 == 0) {
        cout << 0 << endl;
        return 0;
    }
    ans = 0;
    dfs(1);
    cout << P(n,n)-ans << endl;
    cout << ans << endl;
    ans = (ans % MOD) * P(n, n) % MOD;
    return 0;
}
