
/***********最小费用最大流的一些记录 ******************************
    最小费用最大流MCMF的思想就是Ford-Forkson，跟EK求最大流相似，不>断寻找增广路.
    要说和EK的不同点，就是费用流用的是最短路算法来增流，而EK因为不>用考虑费用，所以只要BFS就可以增流。EK出来的增广路是“无序”的，MCMF出
来的增广路是按费用排序了的.
    有个细节，EK的BFS里只要到达了sink就可以return，因为到达了sink就
算找到了一条增广路；但是MCMF得结束了SPFA才可以.



    pre[]数组用来记录增广路径，指向的是边。那能不能像之前那样，用pre指向点来记录呢？
    Answer: 不能，因为这里不是用邻接矩阵来记录流的，是用邻接表，即>直接在边上面记录，所以用pre[]无法逆向回src. 这跟是不是费用流无关，>是看你用什么数据结构来存而已。
    struct Edge { int u, v, value, f, next };

    对于每条边<u, v, c, f>我们都要建立其逆向边<v, u, -c, 0>
******************************************************************/

(1) 最小费用最大流  基础题  poj_2135
    题意：无向带权图G(V, E)，要从点1走到点n再走回来1，期间不能重复>走过同一个点，求最短路径。

    思路：建图：只能经过一次，所以边的容量为1
                边的长度为费用
                因为其实是求两条最小增广路，为了控制要“两条”，可以>设一个超级源点和1相连，容量为2，或者超级汇点和n相连
                估计题目保证了至少有两条不相交路径；无负权回路(因为
我的SPFA都没有写回路的判断就AC了)



    启发：求一条最短路用最短路算法
          求两条可相交的最短路有次短路
          求多条不可相交的路径就用最大流了...因为最大流中，容量可以
控制能经过多少次.


/**********************MCMF模板********************************/
int solve()
{
    int ans = 0;
    while(SPFA(src, sink)) {
        int min_f = INF;
        for(int k = pre[sink]; k != -1; k = pre[edge[k].u])         //寻找颈项边
            min_f = min(min_f, edge[k].f);
        for(int k = pre[sink]; k != -1; k = pre[edge[k].u]) {
            edge[k].f   -= min_f;
            edge[k^1].f += min_f;                                   //因为互为相反边是两两相近的。  因此在建图的时候要注意一下
        }
        ans += min_f * dis[sink];
    }
    return ans;
}

bool SPFA(int src, int sink)
{
    memset(in_queue, false, sizeof(in_queue));
    //memset(pre, -1, sizeof(pre));             //不用初始化pre
    memset(dis, 127, sizeof(dis));
    pre[src] = -1;                      
    in_queue[src] = true;
    dis[src] = 0;
    deque<int> Q;
    Q.push_back(src);
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop_front();
        in_queue[u] = false;
        for(int k = head[u]; k != -1; k = edge[k].next) {
            int v = edge[k].v;
            if(edge[k].f > 0 && dis[v] > dis[u] + edge[k].value) {
                dis[v] = dis[u] + edge[k].value;
                pre[v] = k;                     //记录其前驱边k
                if(!in_queue[v]) {
                    Q.push_back(v);
                    in_queue[v] = true;
                }
            }
        }
    }
    return dis[sink] != INF;
}

