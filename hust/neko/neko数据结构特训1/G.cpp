//Cas 没有初始化 WA了N次！！！太晚了脑子会晕...
#include <stdio.h>
#include <string.h>
#define     low(x)  ((x) & (-(x)))
#define     N       1024
int c[N][N];
bool boo[N][N];

void Update(int x, int y)
{
    for(int i = x; i < N; i += low(i))
        for(int j = y; j < N; j += low(j)) c[i][j] ++;
}
int Query(int x, int y)
{
    int sum = 0;
    for(int i = x; i ; i -= low(i)) 
        for(int j = y; j ; j -= low(j)) sum += c[i][j];
    return sum;
}
int main()
{
    int cases, Cas = 0, x,y,x1,x2,y2,y1,query,op;
    scanf("%d", &cases);
    while(cases--) {
        printf("Case %d:\n", ++Cas);
        memset(boo, false, sizeof(boo));
        memset(c, 0, sizeof(c));
        scanf("%d", &query);
        while(query--) {
            scanf("%d", &op);
            if(op == 0) {
                scanf("%d%d", &x, &y), x++, y++, x++, y++;;
                if(Query(x,y) + Query(x-1,y-1) - Query(x-1,y) - Query(x,y-1) == 1) continue;
                else Update(x, y);
//                if(boo[x][y]) continue; else boo[x][y] = 1;
  //              Update(x, y);
            } else {
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2), x1++,y1++,x2++,y2++, x1++,y1++,x2++,y2++;;
                printf("%d\n", Query(x1-1,y1-1) + Query(x2,y2) - Query(x2, y1-1) - Query(x1-1, y2));
            }
        }
    }
    return 0;
}
