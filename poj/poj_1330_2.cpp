/*
    倍增法求LCA
*/
#include <string.h>
#include <stdio.h>
#include <vector>
using namespace std;
#define     MAXN        10005
#define     ANC_SIZE    15
int depth[MAXN];
int ancester[MAXN][ANC_SIZE];
int n, node[2];
vector<int> child[MAXN];

void Get_Depth(int root, int deep)
{
    depth[root] = deep;
    for(int Size = child[root].size(), i = 0; i < Size; i++) {
        Get_Depth(child[root][i], deep+1);
    }
}
int LCA(int u, int v)
{
    if(depth[u] < depth[v]) swap(u, v);         //使得v比较接近根
    int K = depth[u] - depth[v];
    for(int i = 0; i < ANC_SIZE; i++)           //使得depth[u] == depth[v]
        if(K & (1<<i)) u = ancester[u][i];
    if(u == v) return v;            //重要，别忘记了，因为下面的循环只能处理u != v的情况
    for(int i = ANC_SIZE-1; i >= 0; i--)
        if(ancester[u][i] != ancester[v][i]) {
            u = ancester[u][i];
            v = ancester[v][i];
        }
    return ancester[u][0];
}
void work(int root)
{
    Get_Depth(root, 1);                 //确定depth关系
    for(int j = 1; j < ANC_SIZE; j++)   //确定ancester的关系
        for(int i = 1; i <= n; i++) 
            ancester[i][j] = ancester[ancester[i][j-1]][j-1];
    printf("%d\n", LCA(node[0], node[1]));
}
void init()
{
    for(int i = 1; i <= n; i++) child[i].clear();
    for(int i = 1; i <= n; i++) ancester[i][0] = -1;
}

int main()
{
    int cases, x, y;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        init();
        for(int i = 1; i < n; i++) {
            scanf("%d%d", &x, &y);
            child[x].push_back(y);
            ancester[y][0] = x;
        }
        for(int i = 0; i < 2; i++) scanf("%d", &node[i]);
        for(int i = 1; i <= n; i++) if(ancester[i][0] == -1) {
            work(i);
            break;
        }
    }
    return 0;
}

