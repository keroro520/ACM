/*
    树的构造题   好题

    题意：给一棵树的没个几点赋于Rank'A'-'Z'，使得任意两个有相同Rank的节点x和y之间至少有一个节点z有Rank[z] > Rank[x] = Rank[y]

    思路：<1>递归分治
          <2>对于一棵树，找到其中心点root，给root赋予当前最高Rank
          <3>把root删掉，则这棵树就被拆成若干棵子树
          <4>递归到每颗子树，做同样的事情，即回到<1>


        一开始我是想找一遍树的中心，然后用分层思想，一层一个Rank从高到低下来。易证这不是最优的，比方说遇到1-2-3-...-100这个链就还会挂。

        后来看题解，想了很久都没想出来......

        刚才在活动室的时候跟Tim讨论了一会儿，想了一种方法：还是找到树的中心root，递归到子节点sub，如果sub是有多棵子树的分支节点，则Rank[sub] = Rank[root] + 1，递归下去；如果sub是只有一棵子树的节点，也就是接下来是一条链，则'Z' .. Rank[root]+1依次赋予这条链上的节点，直到遇到分叉口或者‘Z'用完.
        这个方法被Tim的数据否决掉了：偏二叉树情况...
*/
//cf#190#2#E
#include <vector>
#include <stdio.h>
#include <deque>
using namespace std;
#define     MAXN    200005
int n;
vector<int> adj[MAXN];
int ans , ansi;
char color[MAXN];
int pre[MAXN];
void dfs(int u, int sum, int father)        //找u所在的那棵树的中心点，ans表最远直径，ansi表最远点
{
    if(sum > ans) {
        ans = sum;
        ansi =  u;
    }
    for(int Size = adj[u].size(), i = 0; i < Size; i++) {
        int v = adj[u][i];
        if(color[v] || father == v) continue;
        pre[v] = u;
        dfs(v, sum+1, u);
    }
}
int find_center(int u)
{
    ans = -1;
    dfs(u, 1, u);
    ans = -1;
    dfs(ansi, 1, ansi);
    ans /= 2;               //直径除2为半径
    while(ans--) ansi = pre[ansi];
    return ansi;
}
void dye(int u, char rank)
{
    int root = find_center(u);              //<2>
    color[root] = rank;                     //<3>
    for(int Size = adj[root].size(), i = 0; i < Size; i++) {
        int v = adj[root][i];
        if(color[v]) continue;
        dye(v, rank+1);                     //<4>
    }
}
int main()
{
    int x, y;
    scanf("%d", &n);
    for(int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dye(1, 'A');
    for(int i = 1; i <= n; i++) printf("%c ", color[i]);
    printf("\n");
    return 0;
}
