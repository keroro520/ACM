/*
    区间线段树   lazy  延迟标记的好题

    题意：求区间最长*连续*上升序列。两种操作：一般的询问(l,r)，要求返回该区间的LCIS(longest continuous increasing subsequence)；add操作(l,r, add_value)

    思路：很久很久以前看过解题思路了，不过要开始写的时候又想犯懒直接看题解，最后还是忍住了自己写...

          主要考虑合并，父节点区间的lcis可能是两个子节点的最大lcis，也可能是两个子节点拼接时可产生一个新的lcis，即左孩子的右端比右孩子的左端小的时候。
          所以我们要维护这么几个值：Seg_tree_Node {
              l,r : 区间
              l_value, r_value : 区间边界值
              maxl : 区间最长cis的长度
              l_cis : 以左边界为起点的cis的长度
              r_cis : 以右边界为终点的cis的长度
              最后有一个add，是用来搞lazy的~~
          }


          这里的add跟一般lazy操作的add意义没什么区别。在这里lazy能够成立的条件为，对于整个区间[l,r]，都增加add值不会改变[l,r]里任意区间的LCIS。
          但是[l,r]都增加add会影响非[l,r]子集的其它区间的lcis。而这时候我们的l_value/r_value的作用就体现出来了，合并操作是考虑两个子节点的最大lcis，和左孩子的右端+右孩子的左端的lcis ，也就是说合并只用到了l_value/r_value的比较，那我们就可以维护这两个值，使得它们一直保持更新，一有add过来就更新，那么我们就可以在保持lazy延迟的基础上，又实现了合并的正确性了~
          也就是说，记录区间边界值l_value/r_value是为了方便我们的合并操作.
    
          其实我觉得难点就在于如何维护区间边界l_value/r_value保持最新，因为这点WA了好几次，代码里的注释也都是关于这一点的，也是我做这道题的收获的地方吧。在put_down时更新子节点的l_value/r_value，在put_up时更新自己的l_value/r_value，在lazy延迟标记的时候也要更新自己的l_value/r_value.


          另外顺便记下put_down和put_up的位置，这道题我的put_up只有Update()的最下方出现，因为对于[l,r]，只有在update其部分区间的时候需要put_up；put_down只出现在Query()的开头，因为Query下去需要下降lazy...
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
#define     debug       printf("!\n")
#define     MAXN        100005
#define     MID(x, y)   (((x)+(y)) >> 1)
#define     L(x)        ((x)<<1)
#define     R(x)        (((x)<<1)|1)

struct Node {
    int l, r, maxl, l_cis, r_cis, l_value, r_value, add;
} f[MAXN << 2];
void put_up(int u)
{
    Node & a  = f[u];
    Node & ll = f[L(u)]; 
    Node & rr = f[R(u)];
    a.maxl = max(ll.maxl, rr.maxl);
    a.l_value = ll.l_value + a.add, a.r_value = rr.r_value + a.add;     //因为要保持l_value/r_value为最新，所以...
    a.l_cis = ll.l_cis, a.r_cis = rr.r_cis;
    if(ll.r_value < rr.l_value) {
        a.maxl = max(a.maxl, ll.r_cis + rr.l_cis);
    }
    if(ll.l_cis == ll.r - ll.l + 1 && ll.r_value < rr.l_value) {
        a.l_cis = ll.l_cis + rr.l_cis;
    }
    if(rr.r_cis == rr.r - rr.l + 1 && ll.r_value < rr.l_value) {
        a.r_cis = ll.r_cis + rr.r_cis;
    }
}
void put_down(int u)
{
    Node & a = f[u];
    Node & ll = f[L(u)];
    Node & rr = f[R(u)];
    ll.add += a.add, rr.add += a.add;
    ll.l_value += a.add, ll.r_value += a.add;         //又感觉在push_down里也要改l_value/r_value，这样才是最新的  ---才不是！！
    rr.l_value += a.add, rr.r_value += a.add;         //想起来了，刚才这样感觉是说要改ll/rr的l_value值，但是之前写成改a的l_value了...
                                                      //哈哈，改完这里就AC了~~
                                                      //ATTENTION
    a.add = 0;
}
void build(int u, int l, int r)
{
    Node & a = f[u];
    a.l = l, a.r = r, a.add = 0;
    if(l == r) {
        scanf("%d", &a.r_value);
        a.l_value = a.r_value;
        a.l_cis = a.r_cis = a.maxl = 1;
        return ;
    }
    int mid = MID(l, r);
    build(L(u), l, mid);
    build(R(u), mid+1, r);
    put_up(u);
}
int Query(int u, int l, int r)      //询问的时候不用put_up，因为整个区间都增加add不会影响节点的属性
{
    if(l == f[u].l && f[u].r == r) return f[u].maxl; 
    
    put_down(u);        //应该放前面，因为递归回去的时候会有else{..}那边比较l_value/r_value的值，如果不先push_down的话 //没关系，放哪儿都一样。

    int mid = MID(f[u].l, f[u].r);
    if(r <= mid) return Query(L(u), l, r);
    else if(mid < l) return Query(R(u), l, r);
    else {
        int result = max(Query(L(u), l, mid), Query(R(u), mid+1, r));
        Node & a = f[L(u)];
        Node & b = f[R(u)];
        if(a.r_value < b.l_value) {
            result = max(result, a.r + 1 - max(l, a.r - a.r_cis + 1) + min(r, b.l + b.l_cis - 1) + 1 - b.l);
        }
        return result;
    }
}
void Update(int u, int l, int r, int add)
{
    if(l == f[u].l && f[u].r == r) {
        f[u].add += add;
        f[u].l_value += add, f[u].r_value += add;       //我觉得应该在这里改变l_value/r_value,而不是在push_down()里，因为query的时候要比较l_value/r_value，所以l_value/r_value一定要保持最新
        return ;
    }
    int mid = MID(f[u].l, f[u].r);
    if(r <= mid) Update(L(u), l, r, add);
    else if(mid < l) Update(R(u), l, r, add);
    else Update(L(u), l, mid, add), Update(R(u), mid+1, r, add);
    put_up(u);      //ATTENDTION
}
int main()
{
    int cases, Cas = 0, query, l, r, n, add;
    char op[2];
    scanf("%d", &cases);
    while(cases--) {
        printf("Case #%d:\n", ++Cas);
        scanf("%d%d", &n, &query);
        build(1, 1, n);
        while(query--) {
            scanf("%s %d%d", op, &l, &r);            
            if(op[0] == 'q') printf("%d\n", Query(1, l, r));
            else scanf("%d", &add), Update(1, l, r, add);
        }
    }
    return 0;
}
