/*
    并查集 简单题
    
    ATTENTION ! long long 的移位要(1LL << x)  不要用(1L << x)，在CF上WA了几次是因为这个原因。
*/
#include <stdio.h>
#define     MAXN    105

long long lan[MAXN][2];
int father[MAXN];
bool boo[MAXN];
int n, m;

int find(int x) { x == father[x] ? x : father[x] = find(father[x]); }
void Union(int x, int y) {
    int fx = find(x), fy = find(y);
    father[fx] = fy;
}
int main()
{
    bool flag = false;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) father[i] = i;
    for(int i = 0; i < n; i++) {
        int k, x;
        scanf("%d", &k);
        if(k) flag = true;
        while(k--) {
            scanf("%d", &x);
            x--;
            if(x > 60) lan[i][0] |= (1LL<<x);           //TODO  !!  不能用 1L  ，要用1LL  !!!
            else lan[i][1] |= (1LL<<(x-60));
        }
    }
    if(!flag) {         //  特例：全部员工都不会说任何office language
        printf("%d\n", n);
        return 0;
    }
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++) 
            if( (lan[i][0] & lan[j][0]) || (lan[i][1] & lan[j][1]) ) {
                Union(i, j);
            }
    int ans = 0;
    for(int i = 0; i < n; i++) if(!boo[find(i)]) {
        ans++;
        boo[find(i)] = true;
    }
    printf("%d\n", ans-1);
    return 0;
}
