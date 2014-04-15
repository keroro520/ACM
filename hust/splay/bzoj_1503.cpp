/*
    Splay 伸展树  好题
    题意：[NOI2004]郁闷的出纳员
          4个操作：I(k)，插入一个值为k的点，如果已经有了，则累加数量
                   A(k)，略
                   S(k)，所有数的值减去k。如果有些数减去k之后小于low_limit(常数)，则把该数删掉
                   F(k)，输出第k大数


    思路：Splay经典题，郁闷了好久。
    做这道题的体会就是自己还是没理解伸展树的本质...好多情况我还是用一般二叉树的思维来做，结果当然是没用上神奇的Splay()操作，自然低效很多，超时超到爆。看人家的代码很久后才发现他们的代码多次用到了Splay()，而我就极少用。这才好好地去理解Splay()操作的神奇功能，赞！再赞！
    TLE是因为没理解伸展树及其Splay()操作。
    WA是细节问题，最重要的细节是传参是否传引用。
    752ms 过，不错了~

    细节1: if(root == 0) root = x;                     
    细节2: int  Find_LE_than(int std)      //以后这类函数都非递归吧，比较快
    细节3: void Insert(int &x, int father, int val)     //这个引用找了好久      最后是在加上这个引用符才AC的
*/
#include <stdio.h>
#define     MAXN    100005
#define     debug   printf("!\n")
#define     bug(x)  printf("X = %d\n", x)
int mem[MAXN];
int Limit, delta, head, rear, root, count;
class Node {
    public :
    int val, pre, size, num;
    int ch[2];
    Node () { }
    Node (int val, int pre, int size, int num) : val(val), pre(pre), size(size), num(num) { ch[0] = ch[1] = 0;}
} f[MAXN];

void Push_up(int x)
{
    f[x].size = f[x].num + f[ f[x].ch[0] ].size + f[ f[x].ch[1] ].size;
}
void Rotate(int x, int c)
{
    int y = f[x].pre;
    f[y].ch[!c] = f[x].ch[c];
    f[f[x].ch[c]].pre = y;
    if(f[y].pre) f[ f[y].pre ].ch[y == f[f[y].pre].ch[1]] = x;
    f[x].pre = f[y].pre;
    f[x].ch[c] = y;
    f[y].pre = x;
    Push_up(y);
}
void Splay(int x, int goal)
{
    while(f[x].pre != goal) {
        int y = f[x].pre;
        if(f[y].pre == goal) Rotate(x, x == f[y].ch[0]);
        else {
            int z = f[y].pre, c = (f[z].ch[0] == y);
            if(f[y].ch[c] == x) Rotate(x, !c), Rotate(x, c);
            else Rotate(y, c), Rotate(x, c);
        }
    }
    if(goal == 0) root = x;
    Push_up(x);
}
void init()
{
    head = rear = root = 0;
    count = delta = 0;
}
void NewNode(int &x, int father, int val)
{
//    if(rear) x = mem[rear--] ; else x = ++head;
    x = ++head;
    f[x] = Node(val, father, 1, 1);
    if(root == 0) root = x;                     //细节1
}
int  Find_LE_than(int std)                      //这样非递归比较快
{
    int x = root, t = 0;
    while(x) {
        if(f[x].val == std) {
            t = x;
            break;
        } else if(f[x].val < std) {
            t = x ;
            x = f[x].ch[1];
        } else {
            x = f[x].ch[0];
        }
    }
    return t;
}
void Insert(int &x, int father, int val)        //细节2: 这个引用找了好久      最后是在加上这个引用符才AC的
{
    if(!x) {
        NewNode(x, father, val);
        Splay(x, 0);                //神奇的Splay操作呀~~  之前没这样写TLE 
    } else if(f[x].val == val) {
        f[x].num++;
        f[x].size++;
        Splay(x, 0);
    } else {
        Insert(f[x].ch[ f[x].val < val ], x, val);
    //    Push_up(x);         //这里要不要Push_up？ 不要，子节点都Splay到根节点了，不用在这里push_up
    }
}
int Get_Kth(int x, int k)
{
    while(true) {
        if(f[f[x].ch[1]].size >= k) x = f[x].ch[1];
        else if(f[x].num + f[f[x].ch[1]].size >= k) return x;
        else k -= f[x].num + f[f[x].ch[1]].size, x = f[x].ch[0];
    }
}
void A (int k) {
   delta += k; 
}
void I(int k) {
    if(k >= Limit) Insert(root, 0, k - delta);     //低于下界的话算不算离开公司的人员 ?     不算
}
void S(int k) {
    delta -= k;
    int x = Find_LE_than(Limit - delta - 1);       //低于等于Limit-delta-1的就离开公司，这里是找离开的这一群人的祖先节点
    if(x) {
        Splay(x, 0);        //把x旋上来，神奇~~
        count += f[root].num;
        if(f[root].ch[0]) count += f[f[root].ch[0]].size;
        root = f[root].ch[1];       //直接删掉
        f[root].pre = 0;
        Push_up(root);
    }
}
void F(int k) {
    if(f[root].size < k) printf("-1\n");
    else {
        int x = Get_Kth(root, k);
        printf("%d\n", f[x].val + delta);
    }
}
int main()
{
    int query, x; char op[2];
    scanf("%d%d", &query, &Limit);
    init();
    while(query--) {
        scanf("%s%d", op, &x);
        switch (op[0]) {
            case 'I' : I(x); break;
            case 'A' : A(x); break; 
            case 'S' : S(x); break;
            case 'F' : F(x); break;
        }
    }
    printf("%d\n", count);
    return 0;
}
