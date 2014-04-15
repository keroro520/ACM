#include <algorithm>
#include <deque>
#include <math.h>
#include <stdio.h>
using namespace std;
typedef pair<int, int> Pii;
int cur = 0, n;
deque<Pii> Q[2];
int a[200][200];
void check(int x, int y) 
{
    if(a[x][y] > 3)Q[1-cur].push_back(Pii (x, y));
}
int main()
{
    int query, x,y;
    scanf("%d%d", &n, &query);
    a[0][0] = n;
    if(n > 3) {
        Q[cur].push_back(Pii (0, 0));
    }
    while(!Q[cur].empty()) {
        while(!Q[cur].empty()) {
            x = Q[cur].front().first;
            y = Q[cur].front().second;
            Q[cur].pop_front();
            int tmp = a[x][y] / 4;
            if(tmp == 0) continue;
            a[x][y] %= 4;
            a[x+1][y] += tmp,   check(x+1, y);
            a[x][y+1] += tmp,check(x, y+1);
            if(x > 0) a[x-1][y] += tmp,check(x-1, y);
            if(y > 0) a[x][y-1] += tmp,check(x, y-1);
        }
        cur = 1 - cur;
    }
    while(query--) {
        scanf("%d%d", &x, &y);
        if(x > 180 || y > 180) printf("0\n");
        else printf("%d\n", a[(int)abs(x)][(int)abs(y)]);
    }
    return 0;
}
