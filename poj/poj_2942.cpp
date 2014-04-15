/*
    双连通  点双连通  边双连通  奇圈    经典题  好题
    TLE + WA 了 N次，终于AC了...

    题意：
    亚瑟王要在圆桌上召开骑士会议，为了不引发骑士之间的冲突，并且能够让会议的议题有令人满意的结果，每次开会前都必须对出席会议的骑士有如下要求：
    1、  相互憎恨的两个骑士不能坐在直接相邻的2个位置；
    2、  出席会议的骑士数必须是奇数，这是为了让投票表决议题时都能有结果。
     
    如果出现有某些骑士无法出席所有会议（例如这个骑士憎恨所有的其他骑士），则亚瑟王为了世界和平会强制把他剔除出骑士团。
    现在给定准备去开会的骑士数n，再给出m对憎恨对（表示某2个骑士之间使互相憎恨的），问有几个骑士永远无法开会。
             
    注意：1、所给出的憎恨关系一定是双向的，不存在单向憎恨关系。
    2、由于是圆桌会议，则每个出席的骑士身边必定刚好有2个骑士。即每个骑士的座位两边都必定各有一个骑士。
    3、一个骑士无法开会，就是说至少有3个骑士才可能开会。


    解题：
    1.读清楚题目要求，是“有几个骑士不能和任何人形成任何的圆圈”！！这里先称他们为“悲剧骑士”，其他能开会的人称“欢乐骑士”
    2.能相邻坐即意味着两者没有仇恨，那很容易联想到建仇恨关系的补图~G
    3.在~G里，悲剧骑士要么不能与别人形成环，要么只能和别人形成偶数环。换个角度，欢乐骑士是不仅能和别人形成环，且这些环里至少有一个(n >= 3 && n % 2 != 0)，就是说欢乐英雄至少存在在一个奇圈里。
    4.双连通分量和奇圈有如下关系：
        （1）       如果一个双连通分量内的某些顶点在一个奇圈中（即双连通分量含有奇圈），那么这个双连通分量的其他顶点也在某个奇圈中；
        （2）       如果一个双连通分量含有奇圈，则他必定不是一个二分图。反过来也成立，这是一个充要条件。

      第一个定理在这里特别重要，借助该定理我们可以把“骑士i是否至少存在于一个奇圈里”转换成“骑士i所在的双连通分量是否存在奇圈”
    5.Tarjan可以求出双连通分量，每符合dfn[u] <= low[v]就出来一个双连通分量，所以我们要在每出来一个双连通分量的时候都判断该双连通分量是否存在奇圈，若存在，则该双连通分量里的所有骑士都有资格开会。
    6.判断奇圈用染色法，网上很多人直接用二分图染色法，我觉得那是错的，但是该题的数据弱，可以过=_=  得好好理解定理1才能比较好地理解奇圈染色法.
    7.该题用点双或边双的思维来做都可以，我是用点双，网上较多的是边双，差别不大，点双要处理一点小细节.
        例如从栈里取出当前双连通块的点时不能把割点也取出栈，因为割点可以属于多个双连通块。
        刚TLE的时候黄叔说“边双的题你用点来做当然不行啦”，嘻嘻~~
    8.到后面感觉，染色是关键。。。很多细节，如要理解定理1才能写好，理解不好就会写出个二分图染色；如要初始化color, yes, 




    小优写的题解很棒，除了几点要注意的，在评论里有点出来。
    http://blog.csdn.net/lyy289065406/article/details/6756821
    这个人的做法和我的一样：http://blog.csdn.net/tsaid/article/details/6895808


*/
#include <algorithm>
#include <stdio.h>
#include <stack>
#include <string.h>
using namespace std;
#define     MAXN    1005
#define     MAXM    1000005
struct Edge { int v, next; } edge[MAXM * 2];
int low[MAXN], dfn[MAXN], head[MAXN],  result[MAXM], color[MAXN];
bool path[MAXN][MAXN], label[MAXN],visit[MAXM * 2], yes[MAXN], in_stack[MAXN];
int n, m, edge_num, Index;
stack<int> S;
//result[]记录当前双连通块的骑士     color[]染色用
//label[i]记录i是否有资格开会     yes[i]表示当前双连通块是否包含骑士i     visit[k]由于是无向图，用来判断边是否重用 

void init()
{
    edge_num = 0;
    Index = 1;
    memset(head, -1, sizeof(head));
    memset(visit, false, sizeof(visit));
    memset(path, false, sizeof(path));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(label, false, sizeof(label));
    memset(color, 0, sizeof(color));
    memset(yes, false, sizeof(yes));
    memset(in_stack, false, sizeof(in_stack));
    while(!S.empty()) S.pop();
}
void add_edge(int u, int v)
{
    edge[edge_num].v = v;
    edge[edge_num].next = head[u];
    head[u] = edge_num++;
}
bool dye(int u, int c, int f)       //这里忘记判断父节点了
{
    bool flag = true;
    if(color[u]) return color[u] != c;
    color[u] = c;
    for(int k = head[u]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        if(!yes[v] || v == f) continue;
        if(dye(v, 3-c, u)) return true;     //一开始是直接返回true，没有后面的else，函数结尾直接return false，但是当是叶子节点的时候会出错
        else flag = false;
    }
    //color[u] = 0;     //如果都不成功就抹掉标记，因为是dfs /// ??? //好像不用耶。。得好好理解定理1
    return flag;
}
void judge(int u, int v)
{
    int sum = 0, x;
    memset(yes, false, sizeof(yes));
    do {
        x = S.top();
        S.pop();
        result[sum++] = x;
        yes[x] = true;
        in_stack[x] = false;
    } while(x != v);            //最后的u不要出栈，因为割点可能属于多个双连通块
    result[sum++] = u;
    yes[u] = true;          //这是最后改的点。。。。终于AC了。。。
    //printf(" $$$  ");
    //for(int i = 0 ; i < sum; i++) printf("%d  ", result[i]);
    //printf("\n");

    for(int i = 0; i < sum; i++) color[result[i]] = 0;        //抹掉标记      //之前放在后面，当然会WA啦！！
    if(sum < 3 || !dye(result[0], 1, -1)) return ;
    //printf(" $$$  ");
    //for(int i = 0 ; i < sum; i++) printf("%d(%d)   ", result[i], color[result[i]]);
    //printf("\n");
    for(int i = 0; i < sum; i++) label[result[i]] = true;       //标记这些人有开会资格
}
void Tarjan(int u)
{
    dfn[u] = low[u] = Index++;
    S.push(u);
    in_stack[u] = true;
    for(int k = head[u]; k != -1; k = edge[k].next) if(!visit[k]) {
        visit[k] = visit[k ^ 1] = true;
        int v = edge[k].v;
        if(!dfn[v]) {
            Tarjan(v);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]) {
                judge(u, v);                //遇到割点，判断当前双连通分量有没有奇圈。
            }
        } else if(in_stack[v]) low[u] = min(low[u], dfn[v]);        //为什么要判断是否in_stack?
    }
}
int  work()
{
    int x, y;
    init();
    while(m--) {
        scanf("%d%d", &x, &y);
        if(path[x][y]) continue;
        path[x][y] = path[y][x] = true;
    }
    for(int i = 1; i <= n; i++)
        for(int j = i+1; j <= n; j++) 
            if(path[i][j] == false) {       //这里没处理好，TLE了好多次。一定要(i,j),(j,i)连着加到存边数组里面，不然Tarjan里面
                                            //visit[k] = visit[k^1] = true 就错了，之前没注意到
                add_edge(i, j);
                add_edge(j, i);
            }
    for(int i = 1; i <= n; i++) if(!dfn[i]) Tarjan(i);
    int sum = 0;
    for(int i = 1; i <= n; i++) sum += (label[i] == false);
    //for(int i = 1; i <= n; i++) if(label[i] == false) printf("# %d\n", i);
    //printf("\n\n");
    //printf("=================\n");
    //for(int i = 1; i <= n; i++) {
    //    for(int k = head[i]; k != -1; k = edge[k].next) {
    //        printf("--  %d   %d\n", i, edge[k].v);
    //    }
    //    printf("\n");
    //}
    return sum;
}
int main()
{
    while( scanf("%d%d", &n, &m) , n+m ) printf("%d\n", work());
    return 0;
}
