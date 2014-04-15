/*
	B: 用类似于并查集的方法把数分成k个组, 
	某个组大小size > 3, 则 -1
	size = 3  自成一组
	接下来就是size == 1和size == 2的组来随意组合了...
	
	算法简单. 但是被输出搞了好久...其实输出也不难, 就是别扭
*/

#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;;

vector<int>  ans[50], v[50], ok;
bool boo[50];
int start, n;

void dfs(int node)
{
    int tmp;
    for(int i = 0; i < v[node].size(); i++) {
        tmp = v[node][i];
        if(boo[tmp]) continue;
        boo[tmp] = true;
        ans[start].push_back(tmp);
        dfs(tmp);
    }
}
void sendout(int node)
{
    for(int i = 0; i < ans[node].size(); i++) ok.push_back(ans[node][i]);
}
bool cmp(vector<int> a, vector<int> b)
{
    return a.size() < b.size();
}
int main()
{
    int m, x, y;
    scanf("%d%d", &n, &m);
    while(m--) {
        scanf("%d%d", &x, &y);
        v[x].push_back(y);
        v[y].push_back(x);
    }

    memset(boo, false, sizeof(boo));
    for(int i = 1; i <= n; i++) if(!boo[i]) {
            boo[i] = true;

            start = i;
            ans[i].push_back(i);

            dfs(i);
            
            if(ans[start].size() > 3) {
                printf("-1\n");
                return 0;
            }
    }

    for(int i = 1; i <= n; i++) if(ans[i].size() == 3) sendout(i);
       
    
    for(int i = 1; i <= n; i++) if(ans[i].size() == 2) {
            sendout(i);
            ans[i].clear();
            int j ;
            for(j = 1; j <= n; j++) if(ans[j].size() == 1) {
                sendout(j);
                ans[j].clear();
                break;
            }
            if(j > n) {
                printf("-1\n");
                return 0;
            }
    }
    for(int i = 1; i <= n; i++) 
        if(ans[i].size() == 1) sendout(i);

    for(int i = 0, tmp = 1; i < ok.size(); i++, tmp++) {
        printf("%d ", ok[i]);
        if(tmp % 3 == 0) printf("\n");
    }
    return 0;
}
