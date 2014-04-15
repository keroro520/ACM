/*
    二维树状数组   区间求和

    修改单点，询问区间
*/
#include <stdio.h>
#define     MAXN    (1030)
#define     low(x)  (x & (-(x)))
int c[MAXN][MAXN], n;
void Update(int x, int y, int add)
{
    for(int i = x; i <= n; i += low(i))
        for(int j = y; j <= n; j += low(j)) c[i][j] += add;
}
int Query(int x, int y)
{
    int sum = 0;
    for(int i = x; i > 0; i -= low(i))
        for(int j = y; j > 0; j -= low(j))
            sum += c[i][j];
    return sum;
}
int main()
{
    int op,x,y,x1,x2,y2,y1,add;
    scanf("%*d%d", &n);
    while(scanf("%d", &op), op != 3) {
        if(op == 1) {
            scanf("%d%d%d", &x, &y, &add);
            x++, y++;
            Update(x, y, add);
        } else {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            x1++, y1++, x2++, y2++;
            printf("%d\n", Query(x2,y2) + Query(x1-1,y1-1) - Query(x1-1, y2) - Query(x2, y1-1));
        }
    }
    return 0;
}
