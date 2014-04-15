/*
    LCA     Tarjan
*/
#include <stdio.h>
#include <vector>
using namespace std;
#define     MAXN    10001
int n, ans, node1, node2;
vector<int> v[MAXN];
bool is_child[MAXN];
int ancester[MAXN], father[MAXN];

int find(int x) { return x == father[x] ? x : father[x] = find(father[x]);}
void Union(int x, int y) { father[find(y)] = find(x); }
bool Tarjan(int now)
{
    ancester[now] = now;
    for(int Size = v[now].size(), i = 0; i < Size; i++) {
        int tmp = v[now][i];
        if(Tarjan(tmp)) return true;
        Union(now, tmp);
    }

    if(ancester[node1] && ancester[node2]) {
        if(node1 == now) ans = find(node2);  //这里改为ans = find(node2)一下. 结果显示--都可以. ancester只起了判断是否遍历的作用, 可替换成visit
        else if(node2 == now) ans = find(node1);
        if(ans) return true;
    }
    return false;
}
void init()
{
    ans = 0;
    for(int i = 1; i <= n; i++) {
        v[i].clear();
        father[i] = i;
        ancester[i] = 0;
        is_child[i] = false;
    }
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
            v[x].push_back(y);
            is_child[y] = true;
        }
        scanf("%d%d", &node1, &node2);
        for(int i = 1; i <= n; i++) if(is_child[i] == false) {
            Tarjan(i);
            printf("%d\n", ans);
            break;
        }
//        for(int i = 1; i <= n; i++) {
//            printf("%d  %d\n", i, ancester[find(i)]);
//        }
    }
    return 0;
}
