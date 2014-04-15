/*
    超时
*/
#include <stdio.h>
#include <math.h>
#define     func(i, j) ((int)(ceil(sqrt(i-j))))
#define     MAXN    500005
int n;
int h[MAXN], pre[MAXN], next[MAXN];
int main()
{
    scanf("%d", &n);
    int max_h = 0, max_i = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &h[i]);
    }

    int mm = 0, mi = -1;
    for(int i = 0; i < n; i++) {
        pre[i] = mi;
        if(h[i] > mm) {
            mm = h[i];
            mi = i;
        }
    }
    mm = 0, mi = n;
    for(int i = n-1; i != -1; i--) {
        next[i] = mi;
        if(h[i] > mm) {
            mm = h[i];
            mi = i;
        }
    }

    for(int i = 0; i < n; i++) {
        int j = 0, maxx = 0;
        while(j <= i) {
            int tmp = func(i, j);
            if(maxx < h[j] + tmp)
                maxx = h[j] + tmp;
            j = next[j];
        }
        j = n-1;
        while(j > i) {
            int tmp = func(j, i);
            if(maxx < h[j] + tmp) 
                maxx = h[j] + tmp;
            j = pre[j];
        }
        printf("%d\n", maxx - h[i] < 0 ? 0 : maxx - h[i]);
    }
    return 0;
}
