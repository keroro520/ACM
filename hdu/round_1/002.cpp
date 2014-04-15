#include <stdio.h>
#include <string.h>

void init()
{
    edge_num = 0;
    memset(head, -1, sizeof(head));
    memset(is_father, false, sizeof(is_father));
}
void add_edge(int u, int v, char ch)
{
    edge[edge_num].v = v;
    edge[edge_num].next = head[u];
    head[u] = edge_num++;
}
bool compare(int a, int b)
{
    while(letter[a] == letter[b]) {
        if(child[a] == a) return true;
        else if(child[b] == b) return false;
        a = chld[a]; b = child[b];
    }
    return letter[b] > letter[a];
}
long long 
void get_max_deep(int root)
{
    if(!is_father[root]) {
        max_deep[root] = 1;
        return ;
    }
    int tmp = 0;
    for(int k = head[root]; k != -1; k = edge[k].next) {
        int v = edge[k].v;
        get_max_deep(v);
        tmp = max(tmp, max_deep[v]);
    }
    max_deep[root] = tmp;
}
int main()
{
    int query, cases, x, y;
    char ch;
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        init();
        for(int i = 1; i < n; i++) {
            char ch;
            int x, y;
            scanf("%d%d%c", &x, &y, &ch);
            letter[y] = ch;
            is_father[x] = true;
            add_edge(x, y, ch);
        }
        get_max_deep(1);
        scanf("%d", &query);
        while(query--) {
            scanf("%d%d", &x, &len);
            int result = Query(x, len);
            if(result == -1) printf("IMPOSSIBLE\n");
            else printf("%d\n", result);
        }
    }
    return 0;
}
