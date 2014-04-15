/*
    归并排序求逆序数  

    题意：有两排城市，这两排之间有一些城市之间有连接的道路，给出所有道路，问有多少道路是相交的。

    思路：求逆序数，看了disccus后知道重边不算相交。
          按x排序，然后对y求逆序数。
          本来是切树状数组专题的...应该是用树状数组做这道题的...

*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define     MAXN        1005
#define     MID(x, y)   (((x)+(y))>>1)

class Subway {
    public : int x, y;
    Subway () { }
} a[MAXN * MAXN];
int b[MAXN*MAXN], tmp[MAXN*MAXN], n, m, K;
long long ans;
bool cmp(const Subway & a, const Subway & b) { 
    if(a.x != b.x) return a.x < b.x;
    else return a.y < b.y;
}
void merge_sort(int l, int r)
{
    if(l >= r) return ;
    int mid = MID(l, r);
    merge_sort(l, mid), merge_sort(mid+1, r);
    int i = l, j = mid+1;
    int index = l;
    while(i <= mid && j <= r) {
        if(b[i] <= b[j]) tmp[index++] = b[i], i++;
        else {
            tmp[index++] = b[j];
            ans += (mid - i + 1);
            j++;
        }
    }
    if(i <= mid) for(i ; i <= mid; i++) tmp[index++] = b[i];
    if(j <= r)   for(j ; j <= r;   j++) tmp[index++] = b[j];
    memcpy(b+l, tmp+l, sizeof(int) * (r - l + 1));
}

int main()
{
    int cases, Cas = 0;
    scanf("%d", &cases);
    while(cases--) {
        n = m = K = 0;
        scanf("%d%d%d", &n, &m, &K);
        for(int i = 0; i < K; i++) scanf("%d%d", &a[i].x, &a[i].y);
        sort(a, a+K, cmp);
        for(int i = 0; i < K; i++) b[i] = a[i].y;
        ans = 0;
        merge_sort(0, K-1);
        printf("Test case %d: %I64d\n", ++Cas, ans);
    }
    return 0;
}
