#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
int begin[25], end[25];
long long ans;
char s[30];
bool used[25];
int n;

void dfs(int deep)
{
    if(deep == n) {
        ans ++;
        return ;
    }
    for(int i = begin[deep]; i <= end[deep]; i++) if(!used[i]) {
        used[i] = true;
        dfs(deep+1);
        used[i] = false;
    }
}
int main()
{
    s[0] = '*';
    while(scanf("%s", s+1) != EOF) {
        n = strlen(s);
        for(int i = 1; i < n; i++) {
            if(s[i] == '-') begin[i] = 1, end[i] = i-1;
            else begin[i] = i+1, end[i] = n-1;
        }
        ans = 0;
        memset(used, false, sizeof(used));
        dfs(1);
        cout << ans << endl;
    }
    return 0;
}

