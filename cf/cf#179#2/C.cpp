/*
    二次线段树(简单)

    题意 : 给出序列{a}, 
           操作序列{op}, 一个操作opi以(li, ri, di)表示, 表示a[li], a[li+1],..., a[ri]都加上di
           询问序列{q}(其实这名字取得不好), 一个query以(xi, yi)表示, 表示序号为xi ~ yi的操作operation都执行一次.

           要求输出执行完所有query后的{a}


    思路 : 两次线段树
           建两颗树, 一棵存序列{a}, 一棵存操作序列.
           每次query都update一次operation_tree.
           结束后, 再update a_tree

           被long long坑了2个wa... 今天long long跟我有仇吗...


           看别人代码, 发现operation_tree是可以不用的, 这个方法是线段树的特例, 就是当每次加相同数目的情况, **详情看C_2.cpp** 如下:
            for(int i=0;i<k;i++) {
                cin >> li >> ri;
                C[li] += 1; C[ri+1] -= 1;
            }
            for(int i=2;i<=m;i++) C[i] += C[i-1];
*/
#include <stdio.h>
#include <iostream>
using namespace std;

#define L(x)    (x<<1)
#define R(x)    (1+(x<<1))
#define TIMES   13
#define N       100003
#define debug   cout << "!" << endl



struct Operation { int start, end ; long long value; };
struct Tree { 
    int left, right;
    long long value; 
};
Operation op[N];
Tree f[N * TIMES], action[N * TIMES];
long long a[N], b[N];


void down(int node, long long add)
{
    f[node].value += add;
    if(f[node].left == f[node].right) return ;
    down(L(node), f[node].value);
    down(R(node), f[node].value);
}
void update(int node, int left, int right, long long value)
{
    if(f[node].left == left && right == f[node].right) {
        f[node].value += value;
        return ;
    }
    
    int mid = (f[node].left+f[node].right) >> 1;
    if(right <= mid) update(L(node), left, right, value);
    else if(left > mid) update(R(node), left, right, value);
    else {
        update(L(node), left, mid, value);
        update(R(node), mid+1, right, value);
    }
}
void build(int node, int left, int right)
{
    f[node].left  = left;
    f[node].right = right;
    f[node].value = 0;
    if(left >= right) {
        f[node].value = a[left];
        a[left] = node;
        return ;
    }

    int mid = (left + right) >> 1;
    build(L(node), left, mid);
    build(R(node), mid+1, right);
}
void down_op(int node, long long add)
{
    action[node].value += add;
    if(action[node].left == action[node].right) return ;
    down_op(L(node), action[node].value);
    down_op(R(node), action[node].value);
}
void update_op(int node, int left, int right, long long value)
{
    if(action[node].left == left && right == action[node].right) {
        action[node].value += value;
        return ;
    }
    
    int mid = (action[node].left+action[node].right) >> 1;
    if(right <= mid) update_op(L(node), left, right, value);
    else if(left > mid) update_op(R(node), left, right, value);
    else {
        update_op(L(node), left, mid, value);
        update_op(R(node), mid+1, right, value);
    }
}
void build_op(int node, int left, int right)
{
    action[node].left  = left;
    action[node].right = right;
    action[node].value = 0;
    if(left == right) {
        b[left] = node;
        return ;
    }

    int mid = (left + right) >> 1;
    build_op(L(node), left, mid);
    build_op(R(node), mid+1, right);
}
int main()
{
    int n, m, k, x, y;
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];
    build(1, 1, n);

    for(int i = 1; i <= m; i++) 
        cin >> op[i].start >> op[i].end >> op[i].value;
    build_op(1, 1, m);

    while(k--) {
        scanf("%d%d", &x, &y);
        update_op(1, x, y, 1);
    }
    down_op(1, 0);
    //for(int i = 1; i <= m; i++) {
      //  cout << i << "\t" << action[b[i]].value << endl;
//    }
    for(int i = 1; i <= m; i++)
        update(1, op[i].start, op[i].end, action[b[i]].value * op[i].value);
    down(1, 0);
    for(int i = 1; i <= n; i++) cout << f[a[i]].value << "\t";
    cout << endl;
    return 0;
}
