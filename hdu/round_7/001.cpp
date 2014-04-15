/*
    变换式子  优先队列  最远曼哈顿距离  好题

    题意：K(K<=5)维空间里面，不断增点和删点，问每次操作后的最远两个点的曼哈顿距离

    思路：比赛时完全没想法，虽然也知道应该是把点的曼哈顿距离变换成一个可维护变量，但是没想出来。
          其实知道怎么变换的话应该是可以写出来的。
          困了，睡觉，哪天发现这道题再写题解吧...
*/
#include <algorithm>
#include <vector>
#include <functional>
#include <queue>
#include <stdio.h>
#include <string.h>
using namespace std;
#define     N       (32)
#define     MAXN    60010
class Node {
    public :
    int num, id;
    Node () { }
    Node (int num, int id) : num(num), id(id) { }
    friend bool operator > (const Node & a, const Node & b) {
        return a.num < b.num;
    }
    friend bool operator < (const Node & a, const Node & b) {
        return a.num > b.num;
    }
} ;
priority_queue<Node, vector<Node>, greater<Node> > max_Q[MAXN];
priority_queue<Node, vector<Node>, less<Node> >    min_Q[MAXN];
bool boo[MAXN];
int ans;

void init()
{
    ans = 0;
    for(int i = 0; i < N; i++) {
        while(!max_Q[i].empty()) max_Q[i].pop();
        while(!min_Q[i].empty()) min_Q[i].pop();
    }
    memset(boo, false, sizeof(boo));
}
int  Insert(int * x, int query, int K)
{
    int top = (1 << K);
    for(int k = 0; k < top; k++) {
        int sum = 0;
        for(int i = 0; i < K; i++) {
            if(k & (1<<i)) sum += x[i]; else sum -= x[i]; 
        }
        //printf("query = %d  k = %d   sum = %d\n", query, k, sum);
        max_Q[k].push( Node(sum, query) );
        min_Q[k].push( Node(sum, query) );
    }
    int ans = 0;
    for(int k = 0; k < top; k++) 
        if(!max_Q[k].empty()) ans = max(ans, max_Q[k].top().num - min_Q[k].top().num);
    return ans;
}

int Query(int p, int K)
{
    int top = (1 << K);
    boo[p] = true;
    int ans = 0;
    for(int k = 0; k < top; k++) {
        while(!max_Q[k].empty() && boo[max_Q[k].top().id]) max_Q[k].pop();
        while(!min_Q[k].empty() && boo[min_Q[k].top().id]) min_Q[k].pop();
        if(!max_Q[k].empty()) ans = max(ans, max_Q[k].top().num - min_Q[k].top().num);
    }
    return ans;
}
int main()
{
    int query, K, op, p, x[100];
    while(scanf("%d%d", &query, &K) != EOF) {
        init();
        for(int q = 1; q <= query; q++) {
            scanf("%d", &op);
            if(op == 0) {
                for(int i = 0; i < K; i++) scanf("%d", &x[i]);
                printf("%d\n", Insert(x, q, K));
            } else {
                scanf("%d", &p);
                printf("%d\n", Query(p, K));
            }
        }
    }
    return 0;
}
