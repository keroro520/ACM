(1) 最大流  经典题  神构造
/*

    题意：有 M 个猪圈（M ≤ 1000），每个猪圈里初始时有若干头猪。
        一开始所有猪圈都是关闭的。
        依次来了 N 个顾客（N ≤ 100），每个顾客分别会打开指定的几个>猪圈，从中买若干头猪。
        每个顾客分别都有他能够买的数量的上限。
        每个顾客走后，他打开的那些猪圈中的猪，都可以被任意地调换到>其它开着的猪圈里，然后所有猪圈重新关上。
        问总共最多能卖出多少头猪。

    题解：http://imlazy.ycool.com/post.2059102.html

    构造很经典




    "
    在面对网络流问题时，如果一时想不出很好的构图方法，不如先构造一>个最直观，或者说最“硬来”的模型，
    然后再用合并节点和边的方法来简直化这个模型。经过简化以后，好的>构图思路自然就会涌现出来了。
    这是解决网络流问题的一个好方法。
    "
*/


/********************* EK 模板 ************************************/
bool EK(int src, int sink)
{
    memset(visit, false, sizeof(visit));
    deque<int> Q;
    Q.push_back(src);
    visit[src] = true;
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop_front();
        for(int v = 0; v <= sink; v++)
            if(!visit[v] && path[u][v] > f[u][v]) {
                visit[v] = true;
                pre[v] = u;
                if(v == sink) return true;
                Q.push_back(v);
            }
    }
    return false;
}
int max_flow(int src, int sink)
{
    int ans = 0;
    while(EK(src, sink)) {
        int Min = INF, v = sink;
        do {
            Min = min(Min, path[pre[v]][v] - f[pre[v]][v]);
            v = pre[v];
        } while (v != src);
        ans += Min;
        v = sink;
        do {
            f[pre[v]][v] += Min;
            f[v][pre[v]] -= Min;
            v = pre[v];
        } while(v != src);
    }
    return ans;
}
