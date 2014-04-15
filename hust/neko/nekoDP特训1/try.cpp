#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
using namespace std;

#define sqr(a,b) sqrt((double)(a)*(a)+(double)(b)*(b))
template <class T> inline double DIS ( T a , T b ) { return sqr ( a.x - b.x , a.y - b.y ); }

#define INF 0x3f3f3f3f
#define CY 1005
#define E 1000005
#define TT 10005
struct re{
	int v, nxt;
}e[E];

int g[CY], dfn[CY], low[CY], stk[CY], r[CY], Mx[CY], My[CY], dx[CY], dy[CY], fro[TT], to[TT], q[CY];
bool head[CY][CY], instk[CY], vst[CY], vis[CY];
int idx, N, M, top, ind, n_scc, dis, Nx;

void init() {
	idx = top = ind = n_scc = 0;
	memset(g, -1, sizeof(g));
	memset(head, false, sizeof(head));
	memset(dfn, 0, sizeof(dfn));
}

void addedge(int u, int v) {
	e[idx].v = v;
	e[idx].nxt = g[u]; g[u] = idx++;
}

void tarjan(int u) {
	dfn[u] = low[u] = ++ind;
	stk[++top] = u;
	instk[u] = true;
	int v;
	for (int i = g[u]; ~i; i = e[i].nxt) {
		v = e[i].v;
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (instk[v]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	if (dfn[u] == low[u]) {
		do{
			v = stk[top--];
			instk[v] = false;
			r[v] = n_scc;
		}while (u != v);
		n_scc++;
	}
}

bool searchP() {
	queue<int> Q;
	dis = INF;
	memset(dx, -1, sizeof(dx));
	memset(dy, -1, sizeof(dy));
	for (int i = 0; i < Nx; ++i) {
		if (-1 == Mx[i]) {
			Q.push(i); dx[i] = 0;
		}
	}
	while (!Q.empty()) {
		int u = Q.front(); Q.pop();
		if (dx[u] > dis) break;
		for (int i = g[u]; ~i; i = e[i].nxt) {
			int v = e[i].v;
			if (-1 == dy[v]) {
				dy[v] = dx[u] + 1;
				if (-1 == My[v]) dis = dy[v];
				else {
					dx[My[v]] = dy[v] + 1;
					Q.push(My[v]);
				}
			}
		}
	}
	return dis != INF;
}

bool DFS(int u) {
	for (int i = g[u]; ~i; i = e[i].nxt) {
		int v = e[i].v;
		if (!vst[v] && dy[v] == dx[u] + 1) {
			vst[v] = true;
			if (-1 != My[v] && dy[v] == dis) continue;
			if (-1 == My[v] || DFS(My[v])) {
				My[v] = u; Mx[u] = v;
				return true;
			}
		}
	}
	return false;
}
bool Find(int u)
{
	for(int k = g[u]; ~k; k = e[i].nxt) {
		int v = e[i].v;
		if(!vis[v] 
}
int MaxMatch(int n) {
	int ans = 0;
	for(int i = 0; i < n; i++) {
		memset(vis, false, sizeof(vis));
		if(Find(i)) ans ++;
	}
	return ans;
//	Nx = n;
//	int res = 0;
//	memset(Mx, -1, sizeof(Mx));
//	memset(My, -1, sizeof(My));
//	while (searchP()) {
//		memset(vst, 0, sizeof(vst));
//		for (int i = 0; i < Nx; ++i) {
//			if (-1 == Mx[i] && DFS(i)) res++;
//		}
//	}
//	return res;
}

void input(int n, int m) {
	int u, v;
	for (int i = 0; i < m; ++i) {
		scanf("%d%d", &u, &v);
		addedge(u, v);
		fro[i] = u; to[i] = v;
	}
}

void bfs(int s, int n, int MX) {
	memset(vis, false, sizeof(vis));
	vis[s] = true;
	int front = 0, rear = 1, u, v;
	q[front] = s;
	while (front != rear) {
		u = q[front++];
		if (front == MX) front = 0;
		for (int i = g[u]; ~i; i = e[i].nxt) {
			v = e[i].v;
			if (!vis[v]) {
				vis[v] = true;
				q[rear++] = v;
				if (rear == MX) rear = 0;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		head[s][i] = vis[i];
	}
	head[s][s] = false;
}

void solve(int n, int m) {
	for (int i = 1; i <= n; ++i) {
		if (!dfn[i]) {
			tarjan(i);
		}
	}
	idx = 0;
	memset(g, -1, sizeof(g));
	for (int i = 0; i < m; ++i) {
		int u = r[fro[i]];
		int v = r[to[i]];
		if (u != v) {
			addedge(u, v);
		}
	}
	for (int i = 0; i < n_scc; ++i) {
		bfs(i, n_scc, CY - 1);
	}
	idx = 0;
	memset(g, -1, sizeof(g));
	for (int i = 0; i < n_scc; ++i) {
		for (int j = 0; j < n_scc; ++j) {
			if (i == j) continue;
			if (head[i][j]) addedge(i, j);
		}
	}
	int ans = MaxMatch(n_scc);
	//test
//	cout << n_scc << " " << ans << endl;
	//end
	printf("%d\n", n_scc - ans);
}

int main(void) {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; ++i) {
		scanf("%d%d", &N, &M);
		init();
		input(N, M);
		printf("Case %d: ", i);
		solve(N, M);
	}
	return 0;
}
