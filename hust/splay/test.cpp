/*
    bzoj 宠物店    WA 没过样例
*/
#include <algorithm>
#include <stdio.h>
using namespace std;
#define     bug(x)      printf("x# %d\n", x);
#define     MAXN        80000 
#define     MOD         1000000

class Node {
    public :
    int val, pre, min, max, ch[2];
    Node () { }
    Node (int val, int pre) : val(val), pre(pre), min(val), max(val) { ch[0] = ch[1] = 0; }
} f[MAXN];

int head, root, ans;
void init()
{
    ans  = 0; head = 0; root = 0;
}
void Push_up(int x)
{
    if(f[x].ch[0]) {
        f[x].min = min(f[x].val, f[f[x].ch[0]].min);
        f[x].max = max(f[x].val, f[f[x].ch[0]].max);
    }
    if(f[x].ch[1]) {
        f[x].min = min(f[x].val, f[f[x].ch[1]].min);
        f[x].max = max(f[x].val, f[f[x].ch[1]].max);
    }
}
void Rotate(int x, int c)
{
    int y = f[x].pre;
    f[y].ch[!c] = f[x].ch[c];
    f[f[x].ch[c]].pre = y;
    if(f[y].pre) {
        if(f[f[y].pre].ch[0] == y) f[f[y].pre].ch[0] = x;
        else f[f[y].pre].ch[1] = x;
    }
    f[x].pre = f[y].pre;
    f[y].pre = x;
    f[x].ch[c] = y;
    Push_up(y);         //维护y节点
}
void Splay(int x, int goal)
{
    while(f[x].pre != goal) {
        int y = f[x].pre;
        if(f[y].pre == goal) Rotate(x, f[y].ch[0] == x);
        else {
            int z = f[y].pre, c = (f[z].ch[0] == y);
            if(f[y].ch[c] == x) Rotate(x, !c), Rotate(x, c);    //之字形旋转
            else Rotate(y, c), Rotate(x, c);                    //一字形旋转
        }
    }
    Push_up(x);        //维护x节点
    if(goal == 0) root = x;
}
void NewNode(int &x, int father, int val)
{
    x = ++head;
    f[x] = Node(val, father);
    if(root == 0) root = x;
}
void Delete(int &x)
{
    if(!(f[x].ch[0] || f[x].ch[1])) {
        x = 0;
        return ;
    }
    int c = (f[x].ch[0] == 0);
    f[f[x].ch[!c]].pre   = f[x].ch[c];
    f[f[x].ch[c]].ch[!c] = f[x].ch[!c];
    x = f[x].ch[c];
    Push_up(x);
}
void Insert(int x, int val)
{
    int tmp = x;
    while(x) {
        tmp = x;
        x = f[x].ch[ f[x].val < val ];
    }
    NewNode(x, tmp, val);
    Splay(x, 0);
    printf("$$ %d   left: %d   right: %d\n", f[root].val, f[f[root].ch[0]].val, f[f[root].ch[1]].val);
}
int Find(int x, int val)
{
    if(!x) return 0;
    else if(f[x].val == val) return x;
    else return Find(f[x].ch[ f[x].val < val ], val);
}
void Query(int val)
{
    int x = Find(root, val);
    if(x) {
        Splay(x, 0);
        Delete(root);
        return ;
    }
    Insert(root, val);
    //bug(f[f[root].ch[1]].max);
    int diff = min(val - f[f[root].ch[0]].max, f[f[root].ch[1]].min - val);
    ans = (ans + diff) % MOD;
    bug(ans);
    Delete(root);
}
int main()
{
    int query, op, val, sum = 0, sign;
    init();
    for(scanf("%d", &query) ; query ; query--) {
        scanf("%d%d", &op, &val);
        if(sum == 0) {
            sign = op, sum++;
            Insert(root, val);
        } else {
            if(op == sign) Insert(root, val), sum++;
            else Query(val), sum--;
        }
    }
    return 0;
}
