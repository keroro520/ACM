/*
	千创百孔...
	其中最惨的是被宏定义...定义MAXN = 400 + 405，然后定义数组的时候Q[MAXN * MAXN]果断跪；定义Limit = 400 * 400，使用的时候car % Limit再次跪在宏定义上

	队列形式的SPFA跪在TLE上

	各种滥交~

*/	
#include <math.h>
#include <stdio.h>
#define			MAXN		(400 + 405)				//
#define			Limit		(400*400)				//
#define			inf			999999999
int n, m;
double dis[MAXN], e[MAXN][MAXN];
int    time[MAXN] ;//,Q[MAXN*MAXN];
int    S[MAXN * MAXN];
bool   inq[MAXN];

inline		int		hash(int x) { return  x + n; }
bool SPFA(int s)
{
	//int car = 0, cdr = 0;
	int top = 0;
	for(int i = 1; i <= n+m; i++) dis[i] = inf, inq[i] = true, time[i] = 0, S[top++] = i;
	//dis[s] = 0;
	//Q[ car++ ] = s;
	//for(int i = 1; i <= n+m; i++) Q[car++] = i, inq[i] = true;			//为什么？？？
	//while(cdr < car) {
		//int u = Q[(cdr++) % Limit];
	while(top) {
		int u = S[--top];
		inq[u] = false;
		int v = (u <= n ? n+1 : 1), deadline = (u <= n ? n+m : n);
		for( ; v <= deadline; v++) 
			if(dis[v] > dis[u] + e[u][v]) {
				dis[v] = dis[u] + e[u][v];
				if(!inq[v]) {
					if(++time[v] > n) return false;
					//Q[(car++) % Limit] = v, inq[v] = true;
					S[top++] = v,  inq[v] = true;
				}
			}
	}
	return true;
}
int main()
{
	double U, L, x;
	while( scanf("%d %d %lf %lf", &n, &m, &L, &U) != EOF ) {
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++) {
				scanf("%lf", &x);
				e[i][hash(j)] = log2(x/L),  e[hash(j)][i] = log2(U/x);
			}
		puts(SPFA(1) ? "YES" : "NO");
	}
	return 0;
}
