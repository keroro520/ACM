#include <cstdio>
#define max(a,b) ((a)>(b)?(a):(b))
int main ()
{
    int n, m, t, i;
    int arr[1500], Time[1500], dis[1500];
    scanf("%d %d %d", &n, &t, &m);
    for (i = 1; i <= m; i++)
        scanf("%d", &arr[i]);
    Time[0] = dis[0] = 0;
    for (i = 1; i <= m; i++)
    {
        Time[i] = max(Time[max(i-n,0)],arr[i]) + 2 * t;
        dis[i] = dis[max(i - n, 0)] + 1;
    }
    printf("%d %d\n", Time[m] - t, dis[m]);
    return 0;
}
