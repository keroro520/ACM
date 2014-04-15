#include <stdio.h>

int p[100005];
bool visit[100005];
int main()
{
    int s, t, n;
    scanf("%d%d%d", &n, &s, &t);
    for(int i = 1; i <= n; i++) scanf("%d", &p[i]);
    if(s == t) {
        puts("0");
        return 0;
    }
    int ans = 0;
    while(s != t) {
        if(visit[s]) {
            puts("-1");
            return 0;
        }
        visit[s] = true;
        ans++;
        s = p[s];
    }
    printf("%d\n", ans);
    return 0;
}
