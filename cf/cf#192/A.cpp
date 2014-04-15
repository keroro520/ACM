#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
#define     MAXN    100
bool used[MAXN][MAXN];
string s[MAXN];

int main()
{
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++) cin >> s[i];
    int sum = 0;
    for(int i = 0; i < n; i++) {
        bool flag = true;
        for(int j = 0; j < m && flag; j++) if(s[i][j] == 'S') flag = false;
        if(!flag) continue;
        for(int j = 0; j < m; j++) {
            sum += (!used[i][j]);
            used[i][j] = true;
        }

    }
    for(int j = 0; j < m; j++) {
        bool flag = true;
        for(int i = 0; i < n && flag; i++) if(s[i][j] == 'S') flag = false;
        if(!flag) continue;
        for(int i = 0; i < n; i++) sum += (!used[i][j]);
    }
    printf("%d\n", sum);
    return 0;
}
