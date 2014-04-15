/*
    N久N久才理解了题意。。。。1A
*/
#include <stdio.h>
#define     debug   printf("!\n")
#define     MAXN    1005
int n, X;
int f[MAXN], father[MAXN], count[MAXN];

int find(int x)
{
    return x == father[x] ? x : father[x] = find(father[x]);
}   
void Union(int x, int y)
{
    int fx = find(x), fy = find(y);
    father[fx] = fy;
}
int main()
{
    scanf("%d%d", &n, &X);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &father[i]);
        if(father[i] == 0) father[i] = i;
    }
    int pre = 1;
    while(father[X] != X) {
        pre++;
        X = father[X];
    }
    f[0] = true;
    for(int i = 1; i <= n; i++) Union(i, father[i]);
    for(int i = 1; i <= n; i++) count[find(i)]++;
    for(int i = 1; i <= n; i++) if(i == find(i) && i != X) {
        for(int j = n; j >= 0; j--) if(f[j])
            f[j+count[i]] = true;
    }
    for(int i = 0; i <= n; i++) 
        if(f[i]) printf("%d\n", i + pre);
    return 0;
}
