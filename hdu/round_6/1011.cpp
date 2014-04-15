#include <stdio.h>
#include <string.h>
#define     MAXN    2005
int a[MAXN], pos[MAXN], used[MAXN], num[2][MAXN];
bool boo[MAXN];
int n;

int main()
{
    int cases;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        if(n==0)
        {
            printf("\n");
            continue;
        }
        memset(used, 0, sizeof(used));
        memset(boo, false, sizeof(boo));
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            used[a[i]]++;
        }
        for(int i = 0; i < n; i++) if(used[a[i]] == 4) boo[a[i]] = true;
        int p = 0, q = 0;
        for(int i = 0; i < n; i++) {
            if(boo[a[i]] == false) {
                if(used[a[i]] == 2) pos[i] = 0, num[0][p] = a[i], p++;
                else pos[i] = 1, num[1][q] = a[i], q++;
                used[a[i]]--;
                continue;
            }
            if(used[a[i]] == 4) pos[i] = 0, num[0][p] = a[i], p++;
            else if(used[a[i]] == 1) pos[i] = 1, num[1][q] = a[i], q++;
            else if(used[a[i]] == 3) {
                if(num[0][q] != a[i]) pos[i] = 0, num[0][p] = a[i], p++;
                else pos[i] = 1, num[1][q] = a[i], q++;
            }
            else if(used[a[i]] == 2) {
                if(num[0][q] != a[i]) pos[i] = 0, num[0][p] = a[i], p++;
                else pos[i] = 1, num[1][q] = a[i], q++;
            }
            used[a[i]]--;
        }
        for(int i = 0; i < n; i++) printf("%d", pos[i]);
//        printf("\n");
//        for(int i = 0; i < n/2; i++) printf("%d ", num[0][i]);
//        printf("\n");
//        for(int i = 0; i < n/2; i++) printf("%d ", num[1][i]);

        printf("\n");
    }
    return 0;
}
