/*
    最短路, 终点集合到s的最远距离最短，求s.    即已知终点集{d}求一s使得Min{ max{ dis(s, di) } }
    好题
    
  
  
    思路：  多次单源最短路，选出最大值
            在对每个x进行分层搜索的过程中, 用max_d[y]记录每个地区x到达地区y的最短距离中的最大值. 最后求得的Star Value就是max_d[]中的最小值.
            由于题目的特殊性`边权都为1`，所以可以借助这一性质变换一下SPFA使其更快。
            说个题外话，在临高时看到有个学弟拓扑排序用到“分层思想”，一直觉得很妙。就是拓扑后我们可以得到floor[i]，如果floor[i] > floor[j]，即说明j是i的前驱节点（层数越小越接近root）; 而floor[i] == floor[j]的话则i，j的相对顺序无所谓，因为他们都在“同一层”。
            这里因为边权都为1，所以SPFA可以用到上述的分层思想，层数越高，离source越远。代码里面floors就表示层数，Q是滚动队列，就是一层一层地relax后继节点。
            注意！！千万不要以为max_d[]是最短路算法里面的dis[]，这里的max_d[i]是到点i到终点集合{di}的最大值！而常规最短路算法里的dis[]已经被省略为“层数”了，不需要记录，所以没开数组。


            最重要的是学到一个tip！！以前我做多次最短路的时候总要每次都初始化visit[] -> false，但其实不用的，我们只要用一个变量when表示“这是第几次做SPFA(或其他)“，然后每次入队前都看”是否当前visit[v] == when就可以直到改点是否已经入过队......
*/
#include <stdio.h>
#include <string.h>
#include <vector>
#include <deque>
using namespace std;
#define     debug   printf("!\n")
#define     INF     999999999
#define     MAXN    10000
int n;
int max_d[MAXN];
int visit[MAXN];
vector<int> v[MAXN];

void SPFA(int s, int when);
void init();
int main()
{
    int cases, query, id, m, y, x;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d%d", &n, &query);
        init();
        for(int i = 0; i < n; i++) {
            scanf("%d%d", &id, &m);
            while(m--) {
                scanf("%d", &y);
                v[id].push_back(y);
            }
        }
        int when = 0;
        while(query--) {
            scanf("%d", &m);
            while(m--) {
                scanf("%d", &x);
                SPFA(x, ++when);
            }
        }
        
        int ans = INF, ans_id = -1;
        for(int i = 1; i < MAXN; i++) if(!v[i].empty() && max_d[i] < ans) ans = max_d[i], ans_id = i;
        printf("%d %d\n", ans, ans_id);
    }
    return 0;
}
void init()
{
    for(int i = 0; i < MAXN; i++) v[i].clear();
    memset(max_d, 0, sizeof(max_d));
    memset(visit, 0, sizeof(visit));
}
void SPFA(int s, int when)
{
    deque<int> Q[2];
    int cur = 0;
    Q[cur].push_back(s);
    max_d[s] = max(max_d[s], 1);
    visit[s] = when;
    int floors = 1;             
    do {
        floors++;
        while(!Q[cur].empty()) {
            int at = Q[cur].front();
            Q[cur].pop_front();
            for(int Size = v[at].size(), i = 0; i < Size; i++) {
                int to = v[at][i];
                if(visit[to] != when) {     //是否已入队
                    //max_d[to] = max(max_d[to], max_d[at]+1);      这句是不对的，因为这个分层跟拓扑排序的分层是不一样的，拓扑排序是要在入度为0时才能加进队Q，所以可以这样写，但是这里只要第一次遇见点to就必须得入队，因为要的是最短路径
                    max_d[to] = max(max_d[to], floors); //不把这句放在if外面，因为这里的max_d[to]是距离s的最短路径，最短路径也就是最小层数，最小层数在to第一次入队的时候已经得到了
                    visit[to] = when;
                    Q[1-cur].push_back(to);
                }
            }
        }
        cur = 1 - cur;
    } while(!Q[cur].empty());
}
