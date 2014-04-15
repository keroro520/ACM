/*
    状压DP  全排列与二进制联系起来了   模M计数问题  好题

    题意：以Base进制给出数字x，将x的各个位上的数字(digits)进行全排列，每个排列对应一个数，问有多少个排列对应的数能被K整除。

    思路：看了好久，不会。还是用笔抄了一下雷的程序才有点懂的=_=  neko说“这不是水题吗” -_- + =_=

          二进制n位，第i位对应输入的第i个digit.
          f[x][r] : 设S1为x二进制的位为1的编号集合，size(S1) = l, 则f[x][r]表示S1的所有元素已经排好前l位，且这些排列中余数为r的排列数有多少。用雷的话说就是“使用过的数字集合为x，余数为r的个数”。
          那对于f[x][r]的状态转移就是，如果a[i]没有出现在x中，a[i] ∉ S1，则把a[i]放在x所代表的排列后面，
          y  = x | (1<<i);
          r1 = (r*Base + a[i]) % K;     //因为是把a[i]放在这些排列的后面
          f[y][r1] += f[x][r];
          
          感觉实际上整个程序就是对所有排列对应的数模M的余数都统计一遍


          我觉得计算过程很巧妙，要考虑很多细节如我们的排列要从小到大构造，即使用过的数字集合S1是慢慢增长的，所以雷先预处理出ones[i]表示i的二进制有多少个1，然后v[x]表示二进制有x个1的集合。这样，我们的dp跑的时候就可以从小的S1到大的S1了。

          再总结一点，会过头来，我这才知道为什么之前死活看不懂人家的程序（然后又没题解，蛋疼）。因为我对全排列的认识不深，别人写代码的时候有很清晰的思路把位运算与全排列的性质结合起来，而我压根就没想过把这两者联系起来。想一想全排列，大概就能明白为什么把a[i]放在x对应的排列集合后面是(r*Base + a[i]) % MOD了。
*/
//lightoj 1021
#include <stdio.h>
#include <string.h>
#define     MAXN    ((1 << 16) + 10)
#define     N       (20)
int ones[MAXN];
int cnt[N], v[N][MAXN], a[N];
long long f[MAXN][N]; 

int Base, MOD;

void init()
{
    for(int i = 1; i < (1 << 16); i++) ones[i] = ones[i/2] + (i & 1);
}
void DP(int n)
{
    memset(f, 0, sizeof(f));
    f[0][0] = 1;
    for(int one = 0; one < n; one++)
        for(int i = 0; i < cnt[one]; i++) {
            int x = v[one][i];
            for(int r = 0; r < MOD; r++) if(f[x][r])
                for(int k = 0; k < n; k++) if((x & (1 << k)) == 0) {
                    int y  = x | (1 << k);
                    int _r = (r*Base + a[k]) % MOD;
                    f[y][_r] += f[x][r];
//                    printf("%d  r = %d, _r = %d   %d  [a[k]]=%d\n", y, r, _r, f[y][_r], a[k]);
                }
        }
}
int main()
{
    int cases, Cas = 0;
    char s[100];
    init();
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d\n%s", &Base, &MOD, s);
        int n = strlen(s);
        for(int i = 0; i < n; i++) a[i] = ('0' <= s[i] && s[i] <= '9' ? s[i] - '0' : s[i] - 'A' + 10);
        memset(cnt, 0, sizeof(cnt));
        for(int i = 0; i < (1 << n); i++)
            v[ones[i]][ cnt[ones[i]]++ ] = i;
        DP(n);
        printf("Case %d: %lld\n", ++Cas, f[(1 << n)-1][0] );
    }
    return 0;
}
