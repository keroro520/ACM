/*
    �����·���߿������ظ��ߣ�   ����
    ���⣺����ͼ��������·���߿��ظ���

    ժ��https://www.byvoid.com/blog/pku-3255/
    ����ⲻͬ��һ��Ĵζ�·�����⣬��Ϊ��������ߡ����Ƹ�Ϊ�����ˣ���ʵ�Ǹ�����һЩ����
    ��Ϊ����Heap+Dijkstra���1��N�ĵ�Դ���·����������߿�����������ߣ�Ȼ��ö��ÿ��������
    (u,v)������Dist=dis(1,u) + dis(N,v) + w��������ʱDist��ֵ�Ƿ����dis(1,N)������ǵĻ���
    �����´ζ�·��������һ����С��ֵ��

    �һ���һ��ͼ�������e(u,v,w)�ڴ����·����ô����޷�3�֣�
    (1) e�������·�ϣ���u,vҲ�������·�ϣ���Dist=dis(1,u) + dis(N,v) + w����Ȼʹ�ã�����
        ���������ζ̾��������в�ڵ�·��
    (2) e�������·�ϣ�u,v��һ�������·�ϣ���Dist=dis(1,u) + dis(N,v) + w�͵������·����
        shortest + 2*w
    (3) e�����·�ϣ���Dist=dis(1,u) + dis(N,v) + w����shortest�Ļ�����ʵ����s->u->v->u->v->t

    ����AC�����Լ���dijstra���Ƕ��Ż���=_=Ū���ˣ�Ӧ����pair<dis, node>�ģ�д��pair<node,pair>
    ��=_=�����Ըɴ�ɾ����
*/
int solve()
{
    dijstra(1, n, sp[0]), dijstra(n, 1, sp[1]);
    int short_path = sp[0][n], ans = INF;
    for(int i = 0; i < edge_num; i++) {
      u = edge[i].u, v = edge[i].v, w = edge[i].w;
      int tmp = sp[0][u] + sp[1][v] + w;
      if(tmp > short_path && ans > tmp) ans = tmp;
    }
    return ans;
}




#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <queue>
using namespace std;
#define MAXN 5005
#define INF  999999999
#define MAXM 100005
typedef pair<int,int> Pii;
priority_queue< Pii > Q;
struct Edge {
  int u, v, w, next;
} edge[MAXM * 2];
int head[MAXN], sp[2][MAXN];

int main()
{
  int m, u, w, v;
  while(scanf("%d%d", &n, &m) != EOF) {
    init();
    for(int i = 0; i < m; i++) {
      scanf("%d%d%d", &u, &v, &w);
      add_edge(u, v, w), add_edge(v, u, w);
    }

    printf("%d\n", solve());
  }
  return 0;
}
int n, edge_num;
void init()
{
  memset(head, -1, sizeof(head));
  edge_num = 0;
}
void add_edge(int u, int v, int w)
{
  edge[edge_num].u = u, edge[edge_num].v = v, edge[edge_num].w = w;
  edge[edge_num].next = head[u]; head[u] = edge_num++;
}
