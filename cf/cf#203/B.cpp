/*
	被坑了......数据竟然有自环.....且自环还也算一条路径....
*/
#include <stdio.h>
#include <string.h>
#define     MAXN        100005
struct Edge {
    int v, next;
} edge[MAXN];
int head[MAXN], path[MAXN], ans_path[MAXN], type[MAXN];
bool vis[MAXN];
int n, edge_num, ans;

void add_edge(int u, int v)
{
    edge[edge_num].v = v, edge[edge_num].next = head[u];
    head[u] = edge_num++;
}
void dfs(int u, int sum)
{
    vis[u] = true;
    path[sum] = u;
    if(type[u]) {
        if(sum > ans) {
            ans = sum;
            for(int i = 1; i <= sum; i++) ans_path[i] = path[i];
        }
        return ;
    }
	if(edge[head[u]].next != -1) return ;
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v =edge[k].v;
		if(v == u) continue;
        dfs(v, sum+1);
    }
}
bool rd[MAXN];
int main()
{
    int x;
    scanf("%d", &n);
    edge_num = 0;
    memset(vis, false, sizeof(vis));
    memset(head, -1, sizeof(head));
    for(int i = 1; i <= n; i++) scanf("%d", &type[i]);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &x);
        if(x != 0) add_edge(x, i); 
    }
    ans = 0;
    for(int i = 1; i <= n; i++) if(type[i] == 0 && !vis[i]) {
        dfs(i, 1);
    }
	if(ans == 0) {
		for(int i = 1; i <= n; i++) if(type[i] == 1) {
			ans_path[ans = 1] = i;
			break;
		}
	}
    printf("%d\n", ans);
    for(int i = 1; i <= ans; i++) printf("%d ", ans_path[i]);
    puts("");
    return 0;
}
