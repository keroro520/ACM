/*
bzoj 1503: [NOI2004]郁闷的出纳员
还没写完
*/

class Node {
    int value, pre, num, add, min, size;
    Node () { }
    Node (int value, int pre, int num) : value(value), pre(pre), num(num), add(0), min(value-Limit), size(1) { }
} f[MAXN];
void NewNode(int &x, int father, int value)
{
    if(rear) x = mem[read--]; else s = ++head;
    f[x] = Node(value, father, 1);      //1表num
}
void Insert(int value)
{
    int x = root;
    while(f[x].ch[ f[x].value < value ]) x = f[x].ch[ f[x].value < value ];
    NewNode(f[x].ch[ f[x].value < value ], x, value);
}
bool Find(int x, int value)
{
    if(!x) return false;
    if(f[x].value == value) {
        do {
            f[x].size++;
            x = f[x].pre;
        } while(x != root);
        return true;
    }
    return Find(f[x].ch[f[x].value > value], value);
}
void Push_self(int x, int add)
{
    f[x].add += add;
    f[x].value += add;
    f[x].min += add;
}
void Push_up(int x)
{
    f[x].min = min(f[x].value - Limit, min(f[f[x].ch[0]].min, f[f[x].ch[1]].min));
}
void Update(int x, int add)
{
    if(add >= 0 || add + f[u].add + f[u].min >= Limit) {
        Push_self(x, add);
        return ;
    }
    if(f[x].ch[0]) Update(f[x].ch[0], add+f[x].add);
    if(f[x].ch[1]) Update(f[x].ch[1], add+f[x].add);
    f[x].add = 0;
    Push_up(x);
}
int Query(int x, int k)
{
    int t = f[f[x].ch[1]].num;
    if(t + 1 == k) return f[x].value;
    Push_down(x);
    if(t >= k) return Query(f[x].ch[1], k);
    else return Query(f[x].ch[0], k - t - 1);
}
int main()
{
    int query;
    scanf("%d%d", &query, &Limit);
    init();
    while(query--) {
        char op = rdc();
        int  k  = rdi();
        if(op == 'I') {
            if(k < Limit) continue;
            int res = Find(root, k);
            if(res != -1) f[res].num++, n++;
            else Insert(k);
        } else if(op != 'F') {
            if(k > n) { printf("-1\n"); continue; }
            Update(root, k * (op == 'A' ? 1 : -1));
        } else printf("%d\n", Query(root, k));
    }
    return 0;
}
void init()
{
    rear = head = 0;
    root = 0;
    n = 0;
}
