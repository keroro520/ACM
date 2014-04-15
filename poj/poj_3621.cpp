/*
  ���ű��ʻ�
  http://www.cnblogs.com/wally/p/3228171.html
*/
#include <algorithm>
#include <queue>
#include <string.h>
#include <stdio.h>
using namespace std;
#define   INF     (1.0*(1<<30))
#define   MAXN    1111
#define   EPS     1e-4
struct Edge {
  int v, next; double w;
} edge[MAXN*10];
int head[MAXN], cnt[MAXN], vis[MAXN];
double dis[MAXN], node[MAXN];
int n, m, edge_num, when;
void add_edge(int u, int v, double w) {
  edge[edge_num].v = v, edge[edge_num].w = w, edge[edge_num].next = head[u];
  head[u] = edge_num++;
}
bool SPFA(double r, int s)
{
  for(int i = 1; i <= n; i++) cnt[i] = 0, dis[i] = INF;
  dis[s] = 0;
  queue<int> Q;
  Q.push( s );
  while(!Q.empty()) {
    int u = Q.front(); Q.pop();
    vis[u] = 0;
    if(++cnt[u] > n) return true; //�и���

    for(int k = head[u]; k != -1; k = edge[k].next) {
      int v = edge[k].v; double tmp = edge[k].w * r - node[u];
      if(dis[u] + tmp < dis[v]) {
        dis[v] = dis[u] + tmp;
        if(vis[v] != when) vis[v] = when, Q.push(v);
      }
    }
  }
  return false;
}
int main()
{
  freopen("in.txt","r",stdin);
  int u, v; double w;
  while( scanf("%d%d", &n, &m) != EOF ) {
    edge_num = 0, memset(head, -1, sizeof(head));
    for(int i = 1; i <= n; i++) scanf("%lf", &node[i]);
    for(int i = 0; i < m;  i++) {
      scanf("%d%d%lf", &u, &v, &w);
      add_edge(u, v, w);
    }
    double l = 0, r = 10000, mid, ans = 0;
    while(r - l > EPS) {
      mid = (l + r) / 2;
      when++;
      if(SPFA(mid, 1)) ans = l = mid; else r = mid;
    }
    printf("%.2f\n", ans);
  }
  return 0;
}

/*
˼·��֮ǰ������С������������Ҳ������0/1�����������⣬�������������ű��ʻ���������Ϥ����ϧ����û���ƺã�Ҫ������wa,Ҫ������tle�����ư���ʵ�����������֣�ֱ��copy�ɣ�

��Ŀ����˼�ǣ���һ������{��Ȩ��}����{��Ȩ��}��ʹ���Ǹ��������л���{��Ȩ��}����{��Ȩ��}���
����һ�������ȨΪv[i]����Ӧ�ı�ȨΪe[i]�� 
��Ҫ�󣺡ƣ�i=1��n��v[i]/�ƣ�i=1��n)e[i]���Ļ���nΪ���ĵ������� 
����Ŀ��Ϊans�� 
���������еĻ����� �ƣ�i=1��n����v[i]��/�ƣ�i=1��n)��e[i]��<=ans 
���ε�ans* �ƣ�i=1��n����e[i]��>=�ƣ�i=1��n����v[i]�� 
�ٵ� �ƣ�i=1��n����ans*e[i]-v[i]�� >=0 
�Է���һ�£����У� 
��k<ansʱ���ʹ�������һ�����ƣ�i=1��n����k*e[i]-v[i]��<0�����и�Ȩ��·(��ȨΪk*e[i]-v[i])�� 
��k>=ansʱ���Ͷ������еĻ��ƣ�i=1��n����k*e[i]-v[i]��>=0����û�и�Ȩ��·�� 
Ȼ�����ǾͿ���ʹ�µı�ȨΪk*e[i]-v[i]����spfa���жϸ�Ȩ��·,����ans��
*/
