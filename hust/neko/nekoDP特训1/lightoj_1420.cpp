/*
    DP  记忆化搜索  好题

    题意：给出三个字符串A、B、C。拿出A和B的一些subsequences组成C。问有多少种方式？


    思路：显然，我们可以用f[i][j][k]表示用A的前i个和B的前j个拼出C的前k个的方案数。对于C的每个位置k，我们要在A或B中找到一个与C[k]相同的，若A[i]=C[k]则DFS(i+1,j,k+1)，若B[j]=C[k]则DFS(i,j+1,k+1)。但是我们发现，比如A[i]=C[k]，其实i位置之后还是有与C[k]相等的，那些位置也是需要计算的，比如A的下一个位置i1,那么应该DFS(i1+1,j,k+1)。但是下一次计算DFS(i1+1,j,k+1)的时候我们又不能用B[j]来更新。因为，若下次使用B[j]这次也是用B[j]，虽然两次的i是不同的，但是还是有可能出现重复计算的情况。为了解决这个问题，我们再在状态的记录上增加一维，f[i][j][k][3]，0表示只能用A来得到 C[k]，1表示只能用B来得到C[k]，2表示都可以。这样当前若A[i]=C[k]，那么下一步就可以使DFS(i+1,j,k+1,2)或者(DFS,i+1,j,k,0)。


    上面全都摘抄自雷的blog =_=

    赞。  ***  想到开第4维来防止重复，实在太赞了！ 我只想到第3维，而且还不知道怎么转移。 ***
    另外，代码里有注释的那个"break"语句很重要，隐形大剪枝啊！！

    雷总是能用记忆化搜索秒掉麻烦的DP，太崇拜了。。再搞几天DP就加强一下记忆化吧，这几天做lightoj的DP，膜拜记忆化搜索之强大。
*/
//lightoj 1420
#include <stdio.h>
#include <string.h>
#define     MAXN    102
#define     MOD     1000000007
int vis[MAXN][MAXN][MAXN][3], f[MAXN][MAXN][MAXN][3];
int len_a, len_b, len_c, when = 1;
char A[MAXN], B[MAXN], C[MAXN];

inline void update(int &x, int y)
{
    x = (x + y) % MOD;
}
int  DP(int a, int b, int c, int flag)
{
    if(c == len_c) {
        return 1;
    }
    int &x = f[a][b][c][flag];
    if(vis[a][b][c][flag] == when) {
        return x;
    }
    vis[a][b][c][flag] = when;
    x = 0;
    if(flag != 2) {
        for(int i = a; i < len_a; i++) if(A[i] == C[c]) {
            update(x, DP(i+1, b, c+1, 0));
            update(x, DP(i+1, b, c,   1)); 
            break;              ////////    ??????TODO        不用break的会会超时。。。好厉害的搜索o.o
        }
    }
    if(flag != 1) {
        for(int i = b; i < len_b; i++) if(B[i] == C[c]) {
            update(x, DP(a, i+1, c+1, 0));
            update(x, DP(a, i+1, c,   2));
            break;            ////////   ??????TODO        不用break的会会超时。。。好厉害的搜索o.o
        }
    }
    return x;
}

int main()
{
    int cases, Cas = 0;
    scanf("%d", &cases);
    A[0] = B[0] = C[0] = '-';
    while(cases--) {
        scanf("%s%s%s", A+1, B+1, C+1);
        len_a = strlen(A);
        len_b = strlen(B);
        len_c = strlen(C);
        when ++;
        printf("Case %d: %d\n", ++Cas, DP(1,1,1,0));
    }
    return 0;
}
