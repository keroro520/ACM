/*
    最大流   ISAP   简单题

    题意：有n个任务和m台机器，每个任务i必须在si天之后才能开始 （包括），在ei之前完成（包括），任务需要pi天完成。一直每台机器一次只能做一个任务。一个任务一天内只能在一个机器上做，但是不同的天可以用不同的机器，求是否能按时完成任务。

    建图：把每个任务和每一天都看做一个点，添加源点和汇点。源点与每个任务之间连一条边，容量为完成该任务所需处理次数。若第i个任务可以在Si至Ei天处理，则由该任务向这些天分别连一条边，容量为1，表示此任务每天只能被处理一次。最后，从每一天连一条到汇点的边，容量为机器数M，表示每天可以处理M个任务。若求出的最大流等于所有任务需要处理的次数之和，说明能完成任务；否则，不能完成任务。



    建图是自己想的，不过上面的描述是直接copy别人的。
    第一道sap，抄别人的模板，基本没理解，而且抄还抄错，debug了好久好久好久...还是没理解。
    先当模板存着:http://blog.csdn.net/ahfywff/article/details/7240087
*/
#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define     debug   printf("!\n")
#define     MAXN    550+550+100
#define     MAXM    505000
#define     INF     999999999
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
            for(int v = pre[sink]; v != -1; v = pre[v]) {       // 路径回溯更新残留网络  
                int k = cur[v];
                edge[k].cap -= aug[sink];
                edge[k ^ 1].cap += aug[sink];
                aug[v] -= aug[sink];                // 修改可增广量，以后会用到  
                if(edge[k].cap == 0) u = v;         // 不回退到源点，仅回退到容量为0的弧的弧尾  
            }
        }

        for(int k = cur[u]; k != -1; k = edge[k].next) {    // 从当前弧开始查找允许弧  
            int v = edge[k].v;
            if(edge[k].cap > 0 && dis[u] == dis[v] + 1) {   // 找到允许弧  
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
                    cur[u] = k;                 // 修改标号的同时修改当前弧  
                }
            }
            dis[u] = mindis + 1;
            gap[dis[u]]++;
            if(u != s) u = pre[u];      // 回溯继续寻找允许弧  
        }
    }
    return max_flow;
}
int main()
{
    int cases, Cas = 0, s = 0, sink, n, m, si, pi, ei;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &m);
        init();
        int sum = 0, Max_day = 0;
        for(int i = 1; i <= n; i++) {
            scanf("%d%d%d", &pi, &si, &ei);
            sum += pi;
            Max_day = max(Max_day, ei);
            add_edge(s, i, pi);
            for(int j = si; j <= ei; j++) add_edge(i, n + j, 1);
        }
        sink = n + Max_day + 1;
        int N = sink + 1;
        for(int i = 1; i <= Max_day; i++) add_edge(n+i, sink, m);

        int tmp = SAP(s, sink, N);
        if(tmp == sum) printf("Case %d: Yes\n\n", ++Cas);
        else printf("Case %d: No\n\n", ++Cas);  
    }
}
