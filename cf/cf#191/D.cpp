
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
using namespace std;
#define     MAXN    505
#define     debug       printf("!\n")
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
class Pair { 
    public : int op, x, y; 
    Pair(int _op, int _x, int _y) {
        op = _op; x = _x; y = _y;
    }
};
int a[MAXN][MAXN];
int n, m;
vector<Pair> Ans;

bool check(int x, int  y) { return !(x < 0 || x > n || y < 0 || y > m); }
void dfs(int row, int col)
{
    a[row][col] = 2;
    for(int dr = 0; dr < 4; dr++) {
        int x = row + dx[dr], y = col + dy[dr];
        if(!check(x, y) || a[x][y] != 1) continue;
        Ans.push_back(Pair(0, x, y));
        dfs(x, y);
        Ans.push_back(Pair(1, x, y));
        Ans.push_back(Pair(2, x, y));
    }
}

int main()
{
    string s;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) {
        cin >> s;
        for(int len = s.length(), j = 0; j < len; j++)
            a[i][j] = (s[j] == '.');
    }

    for(int i = 0; i < n; i++) 
        for(int j = 0; j < m; j++) if(a[i][j] == 1) {
            Ans.push_back(Pair(0, i, j));
            dfs(i, j);
        }

    printf("%d\n", Ans.size());
    for(int Size = Ans.size(), i = 0; i < Size; i++) {
        if(Ans[i].op == 0) printf("B");
        else if(Ans[i].op == 1) printf("D");
        else printf("R");
        printf(" %d %d\n", Ans[i].x+1, Ans[i].y+1);
    }
    return 0;
}
