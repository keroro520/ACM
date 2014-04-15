/*
    区间线段树  区间合并
    题意：Hotel有N房间，两种操作：一种checkin(x)，某个团的x个人要住连续的x间房间(k,k+1,..,k+x-1)，若有合适的房间则输出最小房间编号k，否则0，表示谢绝这个团的生意。另一种checkout(x,y)，原住x,x+1,..,x+y-1的人要离开，则这些房间就空了出来，这里面可能有一些原本就是空的。

    思路：经典区间线段树。维护这么几个值:
    Seg_tree_Node {
        int l, r;
        int l_rest, r_rest; 以l为起点的连续空余房间数，以r为终点的连续空余房间数
        int max, max_pos;   区间最多的连续空余房间数，以及对应的最小编号。
        int add;   for lazy.._zZ
    }

    Query的顺序为：<1>有合适的房间？f[1].max >= need ?
                   <1.5> 如果f[u].max == need 则直接返回f[u].max_pos
                   <2>u的左节点l_child, l_child.max >= need ? 是就进左节点
                   <3>u的左右节点交界处？
                   <4>上面都不行的话就进右节点吧
    养成了风格，当有lazy来时如果要保持当前节点的属性为最新，则需要更新当前节点属性，我用put_self()。
    下降lazy用put_down()，有时在Update()时下降，有时在Query()时也要下降。
    Update的最后总会有个put_up()
*/
#include <stdio.h>
#define     debug       printf("!\n")
#define     MAXN        50005 
#define     MID(x, y)   (((x)+(y)) >> 1LL)
#define     L(x)        ((x)<<1LL)
#define     R(x)        (((x)<<1LL)|1LL)

struct Node {
    int l, r, l_rest, r_rest, max, max_pos, add;
} f[MAXN << 2];

void Update(int, int, int, int);
void put_up(int u)
{
    Node & a = f[u];
    Node & ll = f[L(u)];
    Node & rr = f[R(u)];
    if(ll.max >= rr.max) {
        a.max = ll.max;
        a.max_pos = ll.max_pos;
    } else {
        a.max = rr.max;
        a.max_pos = rr.max_pos;
    }
    a.l_rest = ll.l_rest;           //小错误大烦恼...因为一个字母拼错了，debug了好久!
    a.r_rest = rr.r_rest;
    if(ll.r_rest != 0 && rr.l_rest != 0) {
        if(a.max < ll.r_rest + rr.l_rest || (a.max == ll.r_rest + rr.l_rest && a.max_pos > ll.r - ll.r_rest + 1)) {
            a.max = ll.r_rest + rr.l_rest;
            a.max_pos = ll.r - ll.r_rest + 1;
        }

        if(ll.l_rest == ll.r - ll.l + 1) a.l_rest = ll.l_rest + rr.l_rest;
        if(rr.r_rest == rr.r - rr.l + 1) a.r_rest = rr.r_rest + ll.r_rest;
    }
}
void build(int u, int l, int r)
{
    f[u].l = l, f[u].r = r, f[u].add = 0;
    if(l == r) {
        f[u].max = f[u].l_rest = f[u].r_rest = 1;
        f[u].max_pos = l;
        return ;
    }
    int mid = MID(l, r);
    build(L(u), l, mid);
    build(R(u), mid+1, r);
    put_up(u);
}
void put_down(int u)
{
    int mid = MID(f[u].l, f[u].r);
    Update(L(u), f[u].l, mid, f[u].add);
    Update(R(u), mid+1, f[u].r, f[u].add);
    f[u].add = 0;
}
void put_self(int u)
{
    Node & a = f[u];
    a.max_pos = a.l;
    a.max = a.l_rest = a.r_rest = (a.r - a.l + 1) * (int)(a.add == 1);
}
void Update(int u, int l, int r, int add)
{
    if(l == f[u].l && f[u].r == r) {
        f[u].add = add ;
        put_self(u);
        return ;
    }
    if(f[u].add) put_down(u);
    int mid = MID(f[u].l , f[u].r);
    if(r <= mid) Update(L(u), l, r, add);
    else if(mid < l) Update(R(u), l, r, add);
    else Update(L(u), l, mid, add), Update(R(u), mid+1, r, add);
    put_up(u);
}
int  Query(int u, int need)
{
    Node & ll = f[L(u)];
    Node & rr = f[R(u)];
    if(f[u].max == need) return f[u].max_pos;           //MARK  呆会儿看看max的更新     //感觉这句不影响吧..
    if(f[u].add) put_down(u);
    if(ll.max >= need) return Query(L(u), need);
    else if(ll.r_rest + rr.l_rest >= need) return ll.r - ll.r_rest + 1;
    else return Query(R(u), need);
}
int main()
{
    int query, n, op, need, l, r;
    scanf("%d%d", &n, &query);
    build(1, 1, n);
    while(query--) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d", &need);
            if(f[1].max < need) printf("0\n");
            else {
                int result = Query(1, need);
                if(result) Update(1, result, result+need-1, 2);
                printf("%d\n", result);
            }
        } else {
            scanf("%d%d", &l, &r);
            Update(1, l, r+l-1, 1);
        }
    }
    return 0;
}
