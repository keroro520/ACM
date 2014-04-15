/*
    求逆序数

    归并排序求逆序数  
    归并不熟，算结果的时候弄了好久.
*/
#include <stdio.h>
#include <vector>
using namespace std;
#define     MAXN    1005
#define     MID(x,y)    (((x)+(y))>>1)
int n, a[MAXN];

int merge_sort(int l, int r)
{
    if(l == r) return 0;
    int mid = MID(l, r);
    int sum = merge_sort(l, mid) + merge_sort(mid+1, r);
    int i = l, j = mid+1;
    vector<int> result;
    while(i <= mid) {
        if(a[i] <= a[j]) result.push_back(a[i]), i++;
        else {
            result.push_back(a[j]);
            sum += (mid - i + 1);
            j++;
            if(j > r) break;
        }
    }
    for(i ; i <= mid; i++) result.push_back(a[i]);
    for(j ; j <= r;   j++) result.push_back(a[j]);
    for(i = l; i <= r; i++) a[i] = result[i - l];
    return sum;
}
int main()
{
    int cases, Cas = 0;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        printf("Scenario #%d:\n", ++Cas);
        printf("%d\n", merge_sort(0, n-1));
        printf("\n");
    }
    return 0;
}
