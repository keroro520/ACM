/*
    学习资源：http://www.cnblogs.com/UnGeek/archive/2013/04/10/3013333.html
              http://www.cnblogs.com/kuangbin/archive/2012/10/07/2714068.html   kuangbin同学
              http://www.cnblogs.com/kuangbin/archive/2013/04/21/3034081.html
              http://www.link.cs.cmu.edu/cgi-bin/splay/splay-cgi.pl         splay-tree demo，什么策略可以把splay-tree拉成一条链呢？
              杨思雨《伸展树的基本操作与应用》
              Crash《运用伸展树解决数列维护问题》

    把kuangbin的数组形式改成结构题形式怎么比原来快了1s ？！neko说结构体的缓存利用率较高=_=

    **区间操作
    首先要有一个认识，Splay树的中序遍历即为我们要维护的序列。即Splay树的伸展操作并没有改变各个节点的相对位置（从中序的角度）。   这是理解区间操作正确性的前提条件。这没什么好证明的，自己模拟一遍zig/zig-zig/zig-zag就理解了。

    提取区间[a,b] : 们将a前面一个数对应的节点旋转到根节点，将b后面一个数对应的节点转到树根的右孩子，那么根的右孩子的左孩子就对应了[a,b]。这里找第k个节点Get_Kth(root, k)是根据节点的size来找的，不是根据value。
    也正因为Get_Kth()是根据size，也就是区间长度来找节点的位置的，而我们在Splay操作的时候也有好好地维护节点的size值，所以在做完上述的操作后，Key_value就对应了区间[a,b]，这个“区间”跟线段树的“区间”相同点在于，这个节点的属性都代表了该区间的属性，不同点在于，因为线段树是按下标排的，所以区间节点的下标有序，但splay树的区间节点的下标只是相对有序。
    "将a前面一个数对应的节点旋转到根节点"对应代码: Splay(Get_Kth(root, l), 0);     
     解释：father 为0，因为root根节点的father是0，做完这步Splay操作之后新root为下标l对应的节点

    "将b后面一个数对应的节点转到树根的右孩子"对应代码: Splay(Get_Kth(root, r+2), root);
     解释：father 为root，因为r-2 > l，新root是下标l对应的节点，所以Get_Kth(root, r+2)出来的节点一定在新root的右边，所以这一步Splay(Get_Kth(root, r+2), root) 才表示旋转r+2对应节点到root的右孩子，而不是左孩子。
           注意，因为在代码里面插入了两个边界点，所以找a前面一个数的节点是Get_Kth(root, a-1+1)，b后面一个数是Get_Kth(root, b+1+1).  


    ** 代码里面两个地方传的是引用，一个是NewNode()，一个是Build().


    ** 为什么代码在旋转的时候只对节点的父亲维护不对x节点维护，但Splay操作的最后却有维护了x节点？
     解释：直接摘抄Crash的解释：“因为除了一字形旋转,在 Splay 操作里我们进行的旋转都只对 X 结点进行,因此过早地维护是多余的;而在一字形旋转中,好像在旋转中没有对 X 的父亲进行维护,但后面紧接着就是旋转 X 结点,又会对 X 的父亲进行维护,也是没问题的。这样可以节省不少冗余的 Update 操作,能减小程序隐含的常数。”


    ** 内存池模拟：这一题没用到，就是用一个双端队列模拟一下而已。
       rear != 0表示有拉圾内存块，则在新建节点的时候复用这块内存，否则开新内存，if(rear != 0) x = mem[rear--]; else x = mem[head++];


    ** 抱着猜测的态度注释掉了Update和Init下的Push_up(root),Push_up(f[root].ch[1])也AC了，说明这是冗余操作吧...=_=


    核心函数: NewNode(), Build(先建中端再建两端的方法), Rotate(), Splay(将x调整到goal的下方), Get_Kth(), Init().
              #define   Key_value  ( f[f[root].ch[1]].ch[0] )
*/
#define         Key_value       ( f[f[root].ch[1]].ch[0] )
class Node {
    public :
    int value, pre, size, add;
    long long sum;
    int ch[2];
    Node () { }
    Node(int pre, int size, int value, int add, long long sum, int l, int r) : pre(pre), size(size), value(value), add(add), sum(sum) {
        ch[0] = l, ch[1] = r;
    }
} f[MAXN];
int a[MAXN], mem[MAXN], head, rear, root, n;
void Traval(int x) {
    if(!x) return ;
    Traval(f[x].ch[0]);
    printf("结点%2d:左儿子 %2d 右儿子 %2d 父结点 %2d val = %2d\n", 
             x,     f[x].ch[0],f[x].ch[1],f[x].pre,  f[x].value);
    Traval(f[x].ch[1]);
}
void Put_self(int u, int value)
{   
    if(u == 0) return ;
    f[u].add += value, f[u].value += value, f[u].sum += (long long) value * f[u].size;
}
void Push_down(int u)
{
    if(!f[u].add) return ;
    Put_self(f[u].ch[0], f[u].add);
    Put_self(f[u].ch[1], f[u].add);
    f[u].add = 0;
}
void Push_up(int u)
{
    f[u].size = 1 + f[f[u].ch[0]].size + f[f[u].ch[1]].size;
    f[u].sum  = f[u].value + f[f[u].ch[0]].sum + f[f[u].ch[1]].sum;
}

void Rotate(int x, int c)
{
    int y = f[x].pre;
    Push_down(y), Push_down(x);
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
    Push_down(x);
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
void NewNode(int &u, int father, int value)      //u是引用!
{
    if(rear) u = mem[rear--]; else u = ++head;
    f[u] = Node(father, 1, value, 0, 0, 0, 0);   
}
void Build(int &x, int l, int r, int father)         //x是引用！
{
   if(l > r) return ;
   int mid = MID(l, r);
   NewNode(x, father, a[mid]);
   Build(f[x].ch[0], l, mid-1, x), Build(f[x].ch[1], mid+1, r, x);
   Push_up(x);
}
void Init()
{
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    root = 0;
    rear = head = 0;
    f[root] = Node(0, 0, 0, 0, 0, 0, 0);
    NewNode(root, 0, -1);
    NewNode(f[root].ch[1], root, -1);
    Build(Key_value, 1, n, f[root].ch[1]);
}
void Delete(int x)      //把以x为祖先节点删掉放进内存池
{
    int father = f[x].pre;
    int p = 0, q = 0, tmp = x;
    for(Q[p++] = x; q < p; q++) {
        x = Q[q];
        mem[++rear] = x;
        if(f[x].ch[0]) Q[p++] = f[x].ch[0];
        if(f[x].ch[1]) Q[p++] = f[x].ch[1];
    }
    f[father].ch[ f[father].ch[1] == tmp ] = 0;
    Push_up(father);
}
int Get_Kth(int u, int k)
{
    Push_down(u);
    int t = f[f[u].ch[0]].size + 1;
    if(t == k) return u;
    else if(t > k) return Get_Kth(f[u].ch[0], k);
    else return Get_Kth(f[u].ch[1], k - t);
}
void Update(int l, int r, int value)
{
    Splay(Get_Kth(root, l), 0);     //第l个节点到根节点     因为root根节点的father是0       做完这步操作之后新root为下标l对应的节点
                                    //而因为r-2 > l，所以Get_Kth(root, r+2)出来的节点一定在新root的右边，所以下一步Splay(Get_Kth(root, r+2), root) 才表示旋转r+2对应节点到根节点的右孩子，而不是左孩子。提醒：记住这一步之后root节点变了；Get_Kth()是根据size来找的.
    Splay(Get_Kth(root, r+2), root);    //第r+2个点到根节点的右孩子     
    Put_self(Key_value, value);
}
long long Query(int l, int r)
{
    Splay(Get_Kth(root, l), 0);
    Splay(Get_Kth(root, r+2), root);
    return f[Key_value].sum;
}
