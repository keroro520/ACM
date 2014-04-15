/*

    TE 了。。。没改呢

*/
#include <string.h>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;
class Node { 
    public :
    int u, d;
    Node(int u, int d) : u(u), d(d) {  }
    friend bool operator < (const Node & a, const Node & b) {
        return a.d < b.d;
    }
};
int n, m;
int dis[30001];
vector<int> vert[30001], edge[30001];
void dijkstra(int s);
int main()
{
    int u,v,w;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        vert[u].push_back(v);
        edge[u].push_back(w);
    }
    dijkstra(1);    //最长路
    printf("%d\n", dis[n]);
}
void dijkstra(int s)
{
    memset(dis, 127, sizeof(dis));
    dis[s] = 0;
    priority_queue<Node> Q;
    Q.push(Node(s, 0));
    while(!Q.empty()) {
        int u = Q.top().u;
        int d = Q.top().d;
        Q.pop();
        if(d > dis[u]) continue;        //@删掉visit，加上这一句
        for(int Size = vert[u].size(), i = 0; i < Size; i++) {
            int v = vert[u][i];
            if(dis[v] > d + edge[u][i]) {
                dis[v] = d + edge[u][i];
                Q.push(Node(v, dis[v]));
            }
       }
   }
}
