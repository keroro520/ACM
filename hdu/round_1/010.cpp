#include <stdio.h>
#include <algorithm>
using namespace std;
#define     MAXN    100005
#define     MID(l, r)   (((l)+(r)) >> 1)
int a[MAXN];
int n;
int calc(int left, int x)
{
    int right = n-1, mid, ans = left - 1;
    while(left <= right) {
        mid = MID(left, right);
        if(a[mid] < x) ans = mid, left = mid+1;
        else right = mid - 1;
    }
    if(ans == left - 1) return -1;
    else return ans;
}
int main()
{
    int cases;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        long long tmp = (n-2)*(n-1)*n/(2*3);
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        sort(a, a+n);

        long long sum = 0;
        for(int i = 0; i < n; i++)
            for(int j = i+1; j < n; j++) {
                if(a[j] == a[j-1] && j != i+1) {
                    if(k != -1) sum += k - j - 1;
                } else {
                    k = calc(j+1, a[i]+a[j]) 
                    if(k != -1) {
                        sum += k - j;
                    }
                }
            }
        printf("%.7f\n", sum*1.0/tmp);
    }
    return 0;
}
