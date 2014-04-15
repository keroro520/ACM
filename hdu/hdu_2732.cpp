/*
    最大流  拆点   简单图论  SAP

    题意：有一些蜥蜴在一个迷宫里面，求这些蜥蜴还有多少是无论如何都逃不出来的。蜥蜴最远能够跳跃距离D，若某一时刻蜥蜴能跳到迷宫外围，则算蜥蜴逃出来了。每只蜥蜴有一个初始的位置，题目保证这些位置都有一些柱子，每次蜥蜴从一个位置跳到另外一个位置的时候，就会由于反作用力使得一根柱子倒下。每根柱子都有最大jump数，若有超过jump个蜥蜴从该跟柱子跳过(也就是leap次)，则柱子会倒塌。距离是算曼哈顿距离。


    建图：初始有蜥蜴的柱子和source连边，容量为1
          每个柱子拆成两个点，u -> u'，容量为jump数
          能跳到外围的柱子和sink连边，容量infinite
          相距不超过D的柱子u,v，连边u' -> v 和 v' -> u，容量infinite

          有sap模板就是爽...建完图就算完工了~~
*/
#include <stdio.h>
#include <algorithm>
#include <string>
#include <iostream>
#include <string.h>
using namespace std;
#define     debug   printf("!\n")
#define     MAXN    550+550+100
#define     MAXM    505000
#define     INF     999999999
#define     ABS(x)  ((x) > 0 ? (x) : (-(x)))

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
    gap[0] = n;memcpy(cur, head, sizeof(head));
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


string map[25], lizards[25];
int main()
{
    int cases, Cas = 0, row, D;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &row, &D);
        init();
        for(int i = 0; i < row; i++) cin >> map[i];
        int n = row, m = map[0].length();
        int source = n*m*2, sink = source + 1;
        for(int i = 0; i < n; i++) 
            for(int j = 0; j < m; j++) if(map[i][j] != '0')
                add_edge(i*m+j, i*m+j + n*m, map[i][j] - '0');      //拆点
        for(int i = 0; i < row; i++) cin >> lizards[i];
        int sum = 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) if(lizards[i][j] == 'L') {
                add_edge(source, i*m+j, 1);     //有蜥蜴的柱子
                sum++;
            }
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) if(i < D || j < D || i > n - D - 1 || j > m - D - 1) {
                add_edge(i*m+j + m*n, sink, INF);
            }
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                for(int x = 0; x < n; x++)
                    for(int y = 0; y < m; y++) if(!(x == i && y == j) && D >= ABS(x-i) + ABS(y-j)) {
                        add_edge(i*m+j + n*m, x*m+y, INF);
                    }
        int result = SAP(source, sink, n*m*2+2);
        printf("Case #%d: ", ++Cas);
        if(sum == result) printf("no lizard was left behind.\n");
        else if(sum == result + 1) printf("1 lizard was left behind.\n");
        else printf("%d lizards were left behind.\n", sum - result);
    }
    return 0;
}
