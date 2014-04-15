/*
	做hdu_4280的时候超时了...所以我在想我是不是写的sap
    ISAP模板
    邻接表  
*/
int cur[MAXN], head[MAXN], aug[MAXN], pre[MAXN], gap[MAXN], dis[MAXN];

struct Edge {
    int u, v, next, cap;
    Edge () { }
    Edge (int u, int v, int next, int cap) : u(u), v(v), next(next), cap(cap) { }
} edge[MAXM];
int edge_num;

void init()
{
    edge_num = 0;
    memset(head, -1, sizeof(head));
}
void add_edge(int u, int v, int cap)
{
    edge[edge_num] = Edge(u, v, head[u], cap);
    head[u] = edge_num++;
    edge[edge_num] = Edge(v, u, head[v], 0);
    head[v] = edge_num++; 
}
int SAP(int s, int sink, int n)
{
    aug[s] = INF;
    pre[s] = -1;
    memset(dis, 0, sizeof(dis));
    memset(gap, 0, sizeof(gap));
    gap[0] = n;
    memcpy(cur, head, sizeof(head));
    int max_flow = 0, u = s;
    while(dis[s] < n) {
        bool flag = false;
        if(u == sink) {
            max_flow += aug[sink];
            for(int v = pre[sink]; v != -1; v = pre[v]) {
                int k = cur[v];
                edge[k].cap -= aug[sink];
                edge[k ^ 1].cap += aug[sink];
                aug[v] -= aug[sink];
                if(edge[k].cap == 0) u = v;
            }
        }

        for(int k = cur[u]; k != -1; k = edge[k].next) {
            int v = edge[k].v;
            if(edge[k].cap > 0 && dis[u] == dis[v] + 1) {
                flag = true;
                pre[v] = u;
                cur[u] = k;
                aug[v] = min(aug[u], edge[k].cap);
                u = v;
                break;
            }
        }

        if(!flag) {
            if(--gap[dis[u]] == 0) break;       /* gap优化，层次树出现断层则结束算法 */  
            int mindis = n;
            cur[u] = head[u];
            for(int k = head[u]; k != -1; k = edge[k].next) {
                int v = edge[k].v;
                if(edge[k].cap > 0 && dis[v] < mindis) {
                    mindis = dis[v];
                    cur[u] = k;
                }
            }
            dis[u] = mindis + 1;
            gap[dis[u]]++;
            if(u != s) u = pre[u];
        }
    }
    return max_flow;
}

