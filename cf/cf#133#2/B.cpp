#include <string.h>
#include <stdio.h>
#include <vector>
#include <deque>
using namespace std;
#define     N   101
bool visit[N];
vector<int> v[N];
deque<int> q;

int  bfs(int node)
{
    int x, sum = 0;
    visit[node] = true;
    q.push_back(node);
    while(!q.empty()) {
        sum++;
        x = q.front();
        q.pop_front();
        for(int i = 0; i < v[x].size(); i++) 
            if(visit[ v[x][i] ] == false) {
                visit[ v[x][i] ] = true;
                q.push_back(v[x][i]);
            }
    }
    return (sum & 1);
}

int main()
{
    int n, m, x, y;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        v[x].push_back(y);
        v[y].push_back(x);
    }
    memset(visit, false, sizeof(visit));
    for(int i = 0; i < n; i++) 
        if(visit[i] == false && v[i].size() == 1) bfs(i);
    int ans = 0;
    for(int i = 0; i < n; i++) 
        if(visit[i] == false && v[i].size() == 2) ans += bfs(i);
    printf("%d\n", ans + ((n & 1) ^ (ans & 1)) );
    return 0;
}
