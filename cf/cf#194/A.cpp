#include <string.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
int a[10], b[10], c[10], d[10], used[2][1000005];
int n = 8;
int main()
{
    for(int i = 0; i < n; i++) {
        scanf("%d%d", &a[i], &b[i]);
        used[0][a[i]]++, used[1][b[i]]++;
    }
    memcpy(c, a, sizeof(a));
    memcpy(d, b, sizeof(b));
    sort(a, a+n);
    sort(b, b+n);
    int mid1 = a[3], mid2 = b[3];
    bool flag = true;
    for(int i = 0; i < n; i++) 
        if(c[i] == mid1 && d[i] == mid2) flag = false;
    if(!flag) {
        puts("ugly");
        return 0;
    }
    used[0][mid1]++, used[1][mid2]++;
    for(int i = 0; i < n; i++) if(!(used[0][c[i]] == 3 && used[1][d[i]] == 3)) flag = false;
    puts(flag? "respectable" : "ugly");
    return 0;
}
