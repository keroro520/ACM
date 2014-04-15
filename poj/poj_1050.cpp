/*
    最大矩阵和  经典DP

    题意：最大子序列和的扩展。

    思路：枚举每一行为起始行，枚举终点行，把这个区域压成一维，运用最大子段和求该区域的最大矩阵和。
*/
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
int n;
int a[105][105], tmp[105];

int calc(int * tmp)
{
    int sum = 0, ans;
    memset(&ans, 128, sizeof(int));
    for(int i = 1; i <= n; i++) {
        sum += tmp[i];
        ans = max(ans, sum);
        if(sum < 0) sum = 0;
        else sum = max(sum, tmp[i]);
    }
    return ans;
}
int main()
{
    int ans;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) 
        for(int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
    memset(&ans, 128, sizeof(int));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) tmp[j] = 0;
        for(int j = i; j <= n; j++) {
            for(int k = 1; k <= n; k++) tmp[k] += a[j][k];
            int sum = calc(tmp);
            ans = max(ans, sum);
        }
    }
    printf("%d\n", ans);
    return 0;
}
