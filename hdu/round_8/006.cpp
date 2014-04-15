#include <string.h>
#include <algorithm>
#include <stdio.h>
using namespace std;
#define     MAXN    1005
#define     debug   printf("!\n")
char A[MAXN], B[MAXN], C[MAXN];
int g[MAXN][MAXN], pre_a[MAXN], pre_b[MAXN], last_a[125], last_b[125];
int len_a, len_b, len_c, limit_a, limit_b;
int jump(int * pre, int * last, int i, char ch, int limit)
{
    int j = last[ch];
    //printf("# %d\n", i);
    while(j > i) {
        j = pre[j];
        if(j <= limit) return 0;
    }
    return j;
}
void calc(int & ans, int n, int m)
{
    int i = n-1, j = m-1;
    for(int k = len_c-2; k > 0; k--) {
        i = jump(pre_a, last_a, i, C[k], limit_a), j = jump(pre_b, last_b, j, C[k], limit_b);
        if(!i || !j) return ;
    }
    limit_a = i, limit_b = j;
    ans = max(ans, g[i-1][j-1] + len_c-1 + (g[len_a-1][len_b-1] - g[n][m]));
}
int  work()
{
    int ans = 0;
    limit_a = limit_b = 0;
//    for(int i = 1; i < len_a; i++) {
//        if(A[i] == C[p]) {
//            p++;
//            if(p == len_c) a_v.push_back(i), p = 1;
//        }
//    }
    memset(pre_a, 0, sizeof(pre_a));
    memset(pre_b, 0, sizeof(pre_b));
    memset(last_a, 0, sizeof(last_a));
    for(int i = 1; i < len_a; i ++) {
        if(A[i] == C[len_c - 1]) {
            memset(last_b, 0, sizeof(last_b));
            for(int j = 1; j < len_b; j ++) {
                if(B[j] == C[len_c-1]) {
                   calc(ans, i, j);
               }
               pre_b[j] = last_b[B[j]];
               last_b[B[j]] = j;
           }
        }
        pre_a[i] = last_a[A[i]];
        last_a[A[i]] = i;
    }
    return ans ;       
}
void init()
{
    memset(g, 0, sizeof(g));
    for(int i = 1; i < len_a; i ++)
        for(int j = 1; j < len_b; j ++) {
            if(A[i] == B[j]) g[i][j] = g[i-1][j-1] + 1;
            else g[i][j] = max(g[i-1][j], g[i][j-1]);
        }
}

int main()
{
    int cases, Cas = 0;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%s%s%s", A+1, B+1, C+1);
        A[0] = '-';
        B[0] = '-';
        C[0] = '-';
        len_a = strlen(A);
        len_b = strlen(B);
        len_c = strlen(C);
        init();
        printf("Case #%d: ", ++Cas);
        if(len_c == 2) printf("%d\n", g[len_a - 1][len_b - 1]);
        else printf("%d\n", work());
    }
}
