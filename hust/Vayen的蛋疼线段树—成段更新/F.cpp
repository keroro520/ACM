/*
    区间线段树  区间覆盖   括号序列  lazy

    题意：给一串括号序列，问[l,r]的括号序列是否合法。合法的定义：1,Empty 2,S合法，则(S)合法 3,A和B合法，则AB合法。有两种操作，一种一般区间修改(reverse, set)，还有Query.


    思路：之前一遇到括号序列就跪，因为我到现在都搞不清楚what is regular brackets sequence...
          所以在大牛blog上看到下面这句话的时候心情很激动~~from : http://hi.baidu.com/zyz913614263/item/ed68843a6839ecd2392ffa2b
           *** "把左括号当做-1，右括号当做1，对于一个区间，只要从左到右的和的最大值为0，并且区间的和为0，则这个区间就是完全匹配的" ***


          知道上面这个定理后，接下来都是自己写的。这道题细节还是挺多的。


          (1)在Update和Query下子节点时，都要先put_down。
          (2)我的lazy标记只有一个，后来看别人的代码时发现他们用了两个，一个is_reverse, 一个is_set。其实可以合成一个的。
          (3)细节多WA在有lazy来时和put_down的时候的处理：保存lazy时要更新节点属性put_self。刚开始时我把更新lazy值和更新节点属性分开了，后来发现不对，前后的lazy值会影响节点属性的更新，所以干脆都扔到change()里，方便多了。



           *** "把左括号当做-1，右括号当做1，对于一个区间，只要从左到右的和的最大值为0，并且区间的和为0，则这个区间就是完全匹配的" ***
*/
//Bracket Sequence UESTC 1546
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define     debug       printf("!\n")
#define     MAXN        100005
#define     MID(x, y)   (((x)+(y)) >> 1)
#define     L(x)        ((x)<<1)
#define     R(x)        (((x)<<1)|1)

typedef pair<int,int> Pair;
struct Node {
    int l,r,min,max,end;
    char lazy;
} f[MAXN << 2];
char str[100005];
int n;

void Update(int , int , int , char);
void put_self(int u, char op)           //更新节点u
{
    if(op == '(' || op == ')') {
        int tmp = (op == '(' ? -1 : 1);
        f[u].end = tmp * (f[u].r - f[u].l + 1);
        f[u].min = min(tmp, f[u].end);
        f[u].max = max(tmp, f[u].end);
    } else {
        f[u].end = - f[u].end;
        int tmp = f[u].max;
        f[u].max = -f[u].min;
        f[u].min = -tmp;
    }
}
void change(int u, char arrive)     //遇到修改[l,r]操作时边lazy，边更新自己的属性(max,min,end)
{
    if(arrive == '(' || arrive == ')') {
        put_self(u, arrive);
        f[u].lazy = arrive;
    } else if(arrive == 'r') {
        put_self(u, 'r');
        if(f[u].lazy == 'r') f[u].lazy = '\0';
        else if(f[u].lazy == '\0') f[u].lazy = 'r';
        else f[u].lazy = (f[u].lazy == ')' ?  '(' : ')');
    }
}
void put_up(int u)
{
    Node & ll = f[L(u)];
    Node & rr = f[R(u)];
    f[u].end = ll.end + rr.end;
    f[u].max = max(ll.max, ll.end+rr.max);
    f[u].min = min(ll.min, ll.end+rr.min);
}

void put_down(int u)
{
    int mid = MID(f[u].l, f[u].r);
    Update(L(u), f[u].l, mid, f[u].lazy);
    Update(R(u), mid+1, f[u].r, f[u].lazy);
    f[u].lazy = '\0';
}
void build(int u, int l, int r)
{
    f[u].l = l, f[u].r = r, f[u].lazy = '\0';    
    if(l == r) {
        f[u].min = f[u].max = f[u].end = (str[l] == '(' ? -1 : 1);      //小错误大烦恼，忘了初始化min...debug了好久
        return ;
    }
    int mid = MID(l, r);
    build(L(u), l, mid);
    build(R(u), mid+1, r);
    put_up(u);
}
Pair Query(int u, int l, int r)
{
    if(l == f[u].l && f[u].r == r) {
        return Pair (f[u].end, f[u].max);
    }
    if(f[u].lazy != '\0') put_down(u);          //所以说，小错误有大关系...漏了判断就得debug很久
    int mid = MID(f[u].l, f[u].r);
    if(r <= mid) return Query(L(u), l, r);
    else if(mid < l) return Query(R(u), l, r);
    else {
        Pair p1 = Query(L(u), l, mid) , p2 = Query(R(u), mid+1, r);
        return Pair(p1.first + p2.first, max(p1.second, p1.first + p2.second));
    }
}
void Update(int u, int l, int r, char op)
{
    if(l == f[u].l && f[u].r == r) {
        change(u, op);          //把lazy的更新，max/end的更新放到change里了
        return ;
    }
    if(f[u].lazy != '\0')put_down(u);
    int mid = MID(f[u].l, f[u].r);
    if(r <= mid) Update(L(u), l, r, op);
    else if(mid < l) Update(R(u), l, r, op);
    else Update(L(u), l, mid, op), Update(R(u), mid+1, r, op);
    put_up(u);
}
int main()
{
    int cases, Cas = 0, query, l, r;
    char op[10];
    scanf("%d", &cases);
    while(cases--) {
        printf("Case %d:\n", ++Cas);
        scanf("%d%s%d", &n, str, &query);
        build(1, 0, n-1);
        while(query--) {
            scanf("%s%d%d\n", op, &l, &r);
            if(op[0] == 'q') {
                Pair p = Query(1, l,r);
                puts(p.first == 0 && p.second < 1 ? "YES" : "NO");
//                printf("!! %d  %d\n", p.first, p.second);
            } else if(op[0] == 's') {
                scanf("%s", str);
                Update(1, l, r, str[0]);
            } else Update(1, l, r, 'r');
        }
        puts("");
    }
    return 0;
}
