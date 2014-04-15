#include <algorithm>
#include <stdio.h>
using namespace std;

int a[100];
int main()
{
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", a+i);
    sort(a, a+n);

    int tot = 1, ans = 0;
    for(int i = 1; i < n; i++) 
        if(a[i] == a[i-1]) tot++;
        else if(tot > ans) ans = tot, tot = 1;
    if(tot > ans) ans = tot, tot = 1;
    
    printf((ans < (n+1)/2 + 1) ? "YES\n" : "NO\n");
    return 0;
}
