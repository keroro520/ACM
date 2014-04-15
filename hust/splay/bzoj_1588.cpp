/*
    Splay  简单题  经典题

    题意：每插入一个数，就累计这个数与之前出现过的数的最小差值。

    思路：splay维护，每插入一个数，就把这个数旋转到根节点root，则查找其前驱与后继就可以简单地比较Max{root的左子树} 和 Min{root的右子树}

          还是不会Splay呀...代码都看别人的...代码有巧妙之处，具体看注释
          输入有坑，具体看代码。
*/
//bzoj 1588
#include <stdio.h>
#include <algorithm>
#include <limits.h>
using namespace std;
#define     bug(x)      printf("x = %d\n", x)
#define     MAXN        1000010
#define     Key_value   (f[f[root].ch[1]].ch[0])
int root;
int mem[MAXN], head, rear;
class Node {
    public : int value, pre, ch[2];
    Node () { }
    Node (int value, int pre, int l, int r) : value(value), pre(pre) {
        ch[0] = l, ch[1] = r;
    }
} f[MAXN];

void Traval(int x) {
    if(!x) return ;
    Traval(f[x].ch[0]);
    printf("结点%2d:左儿子 %2d 右儿子 %2d 父结点 %2d val = %2d\n", 
             x,     f[x].ch[0],f[x].ch[1],f[x].pre,  f[x].value);
    Traval(f[x].ch[1]);
}
void NewNode(int &x, int father, int value)
{
    if(rear) x = mem[rear--]; else x = ++head;
    f[x] = Node(value, father, 0, 0);
}
void Rotate(int x, int c)
{
    int y = f[x].pre;
    f[y].ch[!c] = f[x].ch[c];
    f[f[x].ch[c]].pre = y;
    if(f[y].pre) {
        int z = f[y].pre;
        f[z].ch[ f[z].ch[1] == y ] = x;
    }
    f[x].pre = f[y].pre;
    f[x].ch[c] = y;
    f[y].pre = x;
}
void Splay(int x, int goal)
{
    while (f[x].pre != goal) {
        int y = f[x].pre;
        if(f[y].pre == goal) {
            Rotate(x, f[y].ch[0] == x);
        } else {
            int z = f[y].pre, c = (f[z].ch[0] == y);
            if(f[y].ch[c] == x) Rotate(x, !c), Rotate(x, c);
            else Rotate(y, c), Rotate(x, c);
        }   
    }
    if(goal == 0) root = x;
}
//int _Find(int x, int value)
//{
//    if(f[x].value == value) return x;
//    else if(f[x].size == 1) return -1;
//    return _Find((f[x].ch[value > f[x].value], value);
//}
//bool _Find(int value)
//{
//    int result = Find(root, value);
//    if(result == -1) return false;
//    else {
//        Splay(result, 0);
//        return true;
//    }
//}
void Insert(int value)      //插入一个为value值的节点，不规定位置
{
    if(root == 0) {
        NewNode(root, 0, value);
        return ;
    }
    int x = root;
    while(f[x].ch[ f[x].value < value ]) {          //好巧妙~
        x = f[x].ch[ f[x].value < value ];
    }
    NewNode(f[x].ch[f[x].value < value], x, value);
    Splay(f[x].ch[f[x].value < value], 0);          //为了统计的时候方便，把新插入节点顶到根节点，好想法！
}
int Get_max(int x) 
{
    while(f[x].ch[1]) x = f[x].ch[1];              
    return f[x].value;
}
int Get_min(int x)
{
    while(f[x].ch[0]) x = f[x].ch[0];
    return f[x].value;
}
void Init()
{
    head = rear = 0;
    root = 0;
}
int Query(int value) 
{
    int tmp = (INT_MAX);
    if(f[root].ch[0]) tmp = min(tmp, value - Get_max(f[root].ch[0]));       //细节。要判断root是否存在左子树才能统计!
    if(f[root].ch[1]) tmp = min(tmp, Get_min(f[root].ch[1]) - value);
    return tmp;
}
int main()
{
    int n, value;
    scanf("%d", &n);
    Init();
    int ans = 0;
    for(int i = 0; i < n; i++) {
        if(scanf("%d", &value) == EOF) value = 0;   //坑=_=
        Insert(value);
        if(i == 0) { ans += value; continue; }
        ans += Query(value);
    }
    printf("%d\n", ans);
    return 0;
}
