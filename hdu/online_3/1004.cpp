#include <stdio.h>
#include <string.h>
#define		MAXN		105
struct Edge { int v, next; } edge[MAXN*MAXN];
int color[MAXN], head[MAXN], Q[MAXN*2];
bool path[MAXN][MAXN];
int n, edge_num;
void init()
{
	edge_num = 0;
	memset(head, -1, sizeof(head));
	memset(path, false, sizeof(path));
	memset(color, 0, sizeof(color));
}
void add_edge(int u, int v)
{
	edge[edge_num].v = v, edge[edge_num].next = head[u];
	head[u] = edge_num++;
}
bool dye()
{
    for(int i = 1; i <= n; i++) if(color[i] == 0) {
        int car = 0, cdr = 0;
        Q[++car] = i;
        color[i] = 1;
        while(car != cdr) {
            int u = Q[++cdr];
            for(int k = head[u]; k != -1; k = edge[k].next) {
                int v = edge[k].v;
                if(color[v] != 0) {
                    if(color[v] == color[u]) return false;
                    else continue;
                }
                color[v] = -color[u];
                Q[++car] = v;
            }
        }
    }
    return true;
}
int main()
{
	while(scanf("%d", &n) != EOF) {
		init();
		for(int i = 1; i <= n; i++) {
			do {
				int x;
				scanf("%d", &x);
				if(x == 0) break;
				path[i][x] = true;
			} while(true);
		}
		for(int i = 1; i <= n; i++)
			for(int j = i+1; j <= n; j++) if(i != j )
				if(!path[i][j] || !path[j][i]) add_edge(i, j), add_edge(j, i);
		if(dye()) puts("YES");
		else puts("NO");
	}
	return 0;
}
