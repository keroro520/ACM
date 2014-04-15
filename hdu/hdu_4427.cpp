/*
    DP    好题.     虽然大家都说是水DP, 可是对我来说还是有难度呀...
    状态转移的思路还是挺厉害的, 时间卡得紧, 细节也有, 坑不多.

    题意 : 给出N, M, K, 问有多少种方法构造出长度为K的序列, 使得sum{A} = N, LCM{A} = M

    思路 : 有几点我之前没意识到. 1, 序列中的Ai肯定是M的因子, 不会出现Ak = ai + Aj而M % Ak != 0 的情况, 没想通这一点使得我有点被蒙蔽了双眼, 想复杂了.
    2, 如果想明白了(1), 则该DP其实就是对于每一个位置position进行`0/1背包`的感觉, 而不是`完全背包`

    以位置为阶段, 把v[i]放在该位置为状态(v[i]表M的第i个因子), 
    f[pos][sum][lcm] 表前pos个位置, 总和为sum, 最小公倍数为lcm的最优值, 则
    f[pos+1] [sum+v[i]] [LCM(lcm, v[i])] = sum{ f[pos][sum][lcm]  }, 

    详细解释看代码

    优化 : 
    预处理LCM是必须的
    枚举状态时是以`M的第几个因子`来枚举, 而不是从0-N, 这也是必须的

*/
#include <stdio.h>
#include <vector>
using namespace std;
#define MAXN    1001
#define MOD     1000000007
int N, M, K;
vector<int> v;
int f[2][MAXN+1][MAXN+1];
int LCM[MAXN+1][MAXN+1];

void solve();
int gcd(int a, int b) { if(b == 0) return a; else return gcd(b, a % b); }
int lcm(int a, int b) { return a * b / gcd(a, b); }
void init()
{
    v.clear();
    for(int i = 1; i <= M; i++) if(M % i == 0) v.push_back(i);
}

int main()
{
    for(int i = 1; i <= MAXN; i++)
        for(int j = 1; j <= MAXN; j++)
            LCM[i][j] = lcm(i, j);
            //LCM[j][i] = LCM[i][j] = lcm(j, i);
    while(scanf("%d%d%d", &N, &M, &K) != EOF) {
        init();
        solve();
    }
    return 0;
}
void solve()
{
    int top = v.size();
    int cur = 0;
    for(int i = 0; i <= N; i++)
        for(int j = 0; j < top; j++) f[cur][i][v[j]] = 0; //@优化2 换掉memset
    f[cur][0][1] = 1;
    for(int position = 1; position <= K; position++) {
        cur ^= 1;
        
        for(int sum = 0; sum <= N; sum++)  //用memset会超时
            for(int i = 0; i < top; i++) f[cur][sum][v[i]] = 0;

        for(int sum = position-1; sum <= N; sum++) {//@优化1 : pos-1代替了0, 因为在pos-1个位置的总和肯定 >= pos-1
            for(int i = 0; i < top; i++) { 
                if(f[cur^1][sum][v[i]] == 0) continue;
                for(int j = 0; j < top; j++) {      //前面for i循环是对上一个位置的状态的枚举, 这里的for j是对当前位置要放什么数的枚举
                    int ss = sum + v[j];
                    int ll = LCM[v[i]][v[j]];   //不用判断ll的合法性, 因为ll必定合法
                    if(ss > N) break;   //估计是因为这一点我比kuangbin的快. 因为v[j+1] > v[j], 所以后面的可以不用考虑了
                    f[cur][ss][ll] += f[cur^1][sum][v[i]];
                    f[cur][ss][ll] %= MOD;
                }
            }
        }
    }
    printf("%d\n", f[cur][N][M]);
}
/*
hdu 4427 :  http://acm.hdu.edu.cn/showproblem.php?pid=4427
题解: http://www.cnblogs.com/kuangbin/archive/2012/10/17/2727590.html
*/
