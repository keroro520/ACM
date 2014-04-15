#include <string.h>
#include <stdio.h>
#include <deque>
#include <vector>
using namespace std;

deque<int> q;
vector<int> v[1001];
bool visit[1001];
bool bfs(int x, int y)
{
    int tmp;
    q.clear();
    q.push_back(x);
    visit[x] = true;
    while(!q.empty()) {
        x = q.front();
        q.pop_front();
        for(int i = 0, Size = v[x].size(); i < Size; i++) {
            tmp = v[x][i];
            if(visit[tmp]) continue;
            visit[tmp] = true;
            if(tmp == y) return true;
            q.push_back(tmp);
        }
    }
    return false;
}
int main()
{
    int n, c, x, y;
    scanf("%d%d", &n, &c);
    while(c--) {
        scanf("%d%d", &x, &y);
        v[x].push_back(y);
    }
    
    scanf("%d%d", &x, &y);
    memset(visit, false, sizeof(visit));
    if(bfs(x, y)) {
        printf("%d\n", x);
        return 0;
    } 
    memset(visit, false, sizeof(visit));
    if(bfs(y, x))  {
        printf("%d\n", y);
        return 0;
    } 

    printf("N/A\n");
    return 0;
}   

