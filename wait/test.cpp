
//===============  第一步部分：splay的伸展操作
//Node 为节点类型，其中ch[0]表示左节点类型，ch[1]表示右节点指针
//pre是父亲指针 
void Rotate(Node * x, int c)
{
    Node * y = x->pre;
    push_down(y), push_down(x);
    y->ch[!c] = x->ch[c];
    if(x->[c] != NULL) x->[c]->pre = y;
    x->pre = y->pre;
    if(y->pre != NULL) {
        if(y->pre->ch[0] == y) y->pre->ch[0] = x; else y->pre->ch[1] = x;
    }
    x->ch[c] = y, y->pre = x;
    if(y == root) root = x;
    Update(y);
}
void Splay(Node * x, Node f)        //Splay操作，表示把节点x转到f的上面
{
    push_down(x);
    for( ; x->pre != f ; ) {
        Node * y = x->pre;
        if(y->pre == f) {
            if(y->ch[0] == x) Rotate(x, 1) else Rotate(x, 0);
        } else {
            Node * z = y->pre;
            if(z->ch[0] == y) {
                if(y->ch[0] == x) Rotate(y, 1), Rotate(x, 1);
                else Rotate(x, 0), Rotate(x, 1);
            } else {
                if(y->ch[1] == x) Rotate(y, 0), Rotate(x, 0);
                else Rotate(x, 1), Rotate(x, 0);
            }
        }
    }
    Update(x);
}
void Select(int K, Node * f)        //找到中序遍历第k个点，并将其旋转到节点f的下面
{
    int tmp ;
    Node * t;
    for(t = root; ; ) {
        put_down(t);
        tmp = t->ch[0]->size;
        if(K == tmp+1) break;       //得出t即为查找节点
        if(K <= tmp) t = t->ch[0]; 
        else K -= tmp + 1, t = t->ch[1];
    }
    Splay(t, f);
}
