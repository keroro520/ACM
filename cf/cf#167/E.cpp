/*
    图论构造题      启发题  好题
    n匹马，每匹马有不超过3个敌人。现要把这些马分成两部分，使得对于每条马，和它在同一部分的敌人数量不超过 1个.
    给出敌对关系，要求一个划分方案，或impossible = -1.

    思路：思路是看题解的，题解讲得很清晰 ... http://www.cnblogs.com/zhj5chengfeng/archive/2013/05/30/3108783.html
          实现也是用他的思路，不过代码比他简洁. enemy[i]是记录跟i在同一部分的敌人数量


          反思：题解作者在看到“敌人不超过3个”这一条件的时候就觉得这可能是突破点，而我虽然也在意了一下，但没有深入地去思考，也就没有从这个条件里发掘出什么有用的东西。***最不好的一点是，我甚至都没有怎么在纸上划划！！！*** 作者是一步一步思考出AC来的（看题解就知道），但我就没有他那种“一步一步”的耐心！改！
*/
#include <stdio.h>
#include <vector>
#include <deque>
using namespace std;
#define     MAXN        300005
vector<int> adj[MAXN];
deque<int> Q;
int enemy[MAXN], color[MAXN];
int n;

void bfs()
{
    for(int i = 1; i <= n; i++) {
        if(enemy[i] > 1) Q.push_back(i);
        color[i] = 0;
    }
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop_front();
        if(enemy[u] <= 1) continue;         //有可能他的敌人已经被扔到另一边了，enemy[u]就变得<=1了，这里就不能扔u
        color[u] = !color[u];               //把u扔到另一边    
        enemy[u] = 0;
        for(int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i];
            if(color[v] == color[u]) enemy[u]++, enemy[v]++;
            else enemy[v]--;
            if(enemy[v] > 1) Q.push_back(v);
        }
    }
}
int main()
{
    int m, x, y;
    scanf("%d%d", &n, &m);
    while(m--) {
        scanf("%d%d", &x, &y);
        adj[x].push_back(y);
        adj[y].push_back(x);
        enemy[x]++, enemy[y]++;
    }
    bfs();
    for(int i = 1; i <= n; i++) printf("%d", color[i]);
    printf("\n");
    return 0;
}
/*
做法分析
 

首先，观察下为什么题目给的数据范围这么奇葩：

每条马的敌人的数量不超过 3 个

这有什么用呢？想了很久，画了好几个图，最终确定，这样的条件下，一定是存在一个划分方案，使得每部分中，每条马的敌人数量不超过 1 个。

可以考虑 4 个点的完全图，每个点的度是 3，对应了 3 个敌人，我们完全可以找出一种分配的方案使得这个图的点分成两个点集，那么，对于其余的情况，肯定也是能够找出一种解的，因为他们的关系比 4 个点的完全图的关系更加的简单

也就是说，输出 -1 的情况是不存在的

接下来就考虑怎么构造出一种分配的方案了

 

实在是想不出有什么其他的做法了，干脆贪心的找找，类似于 SPFA 的 BFS：

        ①. 先假设所有的马都在同一个部分中，把所有不合格的马（有超过 1 个敌人的）入队

        ②. BFS 的过程中，先把当前马移动到另一个部分中，然后再统计它的敌人中，哪些马变得不合法了，把不合法的加入到队列中

这样不断的 BFS，肯定能够找到一种分配方案，但是具体的时间复杂度不知道怎么计算的，迷迷糊糊的就过了......
*/
