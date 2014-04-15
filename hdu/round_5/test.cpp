#include <stdio.h>
#include <string.h>
#define         MAXN        202
double f[2][(1 << 20)], p[MAXN];
bool boo[(1 << 20)+5];
char op[MAXN];
int S[(1 << 20)+5], a[MAXN];
int n, top;
void init()
{
    top = 0;
    memset(boo, false, sizeof(boo));
    memset(f, 0, sizeof(f));
}
int calc(int x, int y, char op)
{
    if(op == '&') return x & y;
    else if(op == '|') return x | y;
    else return x ^ y;
}
int main()
{
    int Cas = 0;
    char ch;
    while(scanf("%d", &n) != EOF) {
        init();
        for(int i = 0; i <= n; i++) scanf("%d", &a[i]);
        while(getchar() != '\n');
        for(int i = 1; i <= n; i++) {
            while((ch = getchar()) == ' ' || ch == '\t');
            op[i] = ch;
        }
        for(int i = 1; i <= n; i++) scanf("%lf", &p[i]);
        S[top++] = a[0];
        boo[a[0]] = true;
        int cur = 0;
        f[cur][a[0]]  = 1;
        for(int i = 1; i <= n; i++) {
            int top2 = top;
            memcpy(f[1-cur], f[cur], sizeof(int)*(1 << 20));
            for(int j = 0; j < top; j++) {
                int x = S[j];
                int y = calc(x, a[i], op[i]);
                if(!boo[y]) {
                    boo[y] = true;
                    S[top2++] = y;
                }
                if(x == y) continue;
                f[1-cur][y] += f[cur][x] * (1- p[i]);
                f[1-cur][x] =  f[cur][x] * p[i];
            }
            top = top2;
            cur = 1- cur;
        }
        double ans = 0;
        for(int i = 0; i < top; i++) {
            ans += f[cur][S[i]] * S[i];
        }
        printf("Case %d:\n%.6f\n", ++Cas, ans);
    }
    return 0;
}
