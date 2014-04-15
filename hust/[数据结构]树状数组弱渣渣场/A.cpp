/*
    树状数组模板题

    专题第一题，看树状数组资料自己写出来的..1A.
*/
// hdu 1166
#include <stdio.h>
#include <string.h>
#define     MAXN        50005
int c[MAXN], n;

void init()
{
    memset(c, 0, sizeof(c));
}
int low(int x)
{
    return x & (x ^ (x - 1));
}
void Update(int pos, int x)
{
    do {
        c[pos] += x;
        pos += low(pos);
    } while(pos <= n);
}
int Query(int pos)
{
    int sum = 0;
    while(pos) {
        sum += c[pos];
        pos -= low(pos);
    }
    return sum;
}
int main()
{
    int cases, Cas = 0, l, r, x;
    char op[10];
    scanf("%d", &cases);
    while(cases--) {
        init();
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &x);
            Update(i, x);
        }
        printf("Case %d:\n", ++Cas);
        while(scanf("%s", op)) {
            if(op[0] == 'E') break;
            scanf("%d%d", &l, &r);
            if(op[0] == 'Q') printf("%d\n", Query(r) - Query(l-1));        //i = 0时候会怎样？
            else Update(l, r * (op[0] == 'A' ? 1 : -1));
        }
    }
    return 0;
}
