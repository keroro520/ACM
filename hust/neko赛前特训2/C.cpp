/*
  �߶���������  ����  ���븴��  ϸ��
  ���⣺0 a b ��[a, b]�����ڵ�������ȫ���0
        1 a b ��[a, b]�����ڵ�������ȫ���1
        2 a b ��[a,b]�����ڵ�������ȫ��ȡ����Ҳ����˵�����е�0���1�������е�1���0
        3 a b ѯ��[a, b]�������ܹ��ж��ٸ�1
        4 a b ѯ��[a, b]����������ж��ٸ�������1

  ˼·������ܿ��д�����ˣ���������û����debug�ܾã����ְѶ����������һ����߶������
        �˵�ϸ�ĳ̶���=_=
        �Ƽ���һ���������롣�����ģ��һ�����ڴ�������Ŀ����Խ�ܴ��븴�ã�������룬Խ��
        ���׳���
*/
//http://acm.hust.edu.cn/vjudge/contest/view.action?cid=34743#problem/C
#include <stdio.h>
#include <algorithm>
using namespace std;
#define   MAXN            100005
#define   L(x)            (x<<1)
#define   R(x)            ((x<<1) | 1)
#define   MID(l,r)        (((l)+(r))>>1)
#define   forle(b, e)   for(int i = b; i <= e; i++)
struct Node {
  int chg, inv;
  int l, r, lx, rx;
  int s[2], max[2], maxl[2], maxr[2];
} f[MAXN * 4];
void push_down(int u);
void print(int u)
{
  if(f[u].l == f[u].r) {
    printf("(%d: %d) ", f[u].l, f[u].lx);
    return ;
  }
  push_down(u);
  print(L(u)), print(R(u));
}
void Change (int u, int l, int r, int val);
void Inverse(int u, int l, int r);
void push_up(int u)
{
  Node &t = f[u], &lt = f[L(u)], &rt = f[R(u)];
  t.lx = lt.lx, t.rx = rt.rx;        //TODO  �������С�ط�©�ˣ�debug��һ����=_=
  forle(0,1) {
    t.s[i] = lt.s[i] + rt.s[i];
    t.maxl[i] = lt.maxl[i], t.maxr[i] = rt.maxr[i], t.max[i] = max(lt.max[i], rt.max[i]);
  }
  if(lt.rx == rt.lx) {
    int i = lt.rx;
    t.max[i] = max(t.max[i], lt.maxr[i] + rt.maxl[i]);
    if(lt.maxl[i] == lt.r - lt.l + 1)  t.maxl[i] = t.max[i];
    if(rt.maxr[i] == rt.r - rt.l + 1)  t.maxr[i] = t.max[i];
  }
}
void push_down(int u)
{
  Node &t = f[u], &lt = f[L(u)], &rt = f[R(u)];
  if( t.inv ) {
    Inverse(L(u), lt.l, lt.r), Inverse(R(u), rt.l, rt.r);
    t.inv = 0;
  }
  if( t.chg != -1 ) {
    Change(L(u), lt.l, lt.r, t.chg), Change(R(u), rt.l, rt.r, t.chg);
    t.chg = -1;
  }
}

void build(int u, int l, int r)
{
  Node &t = f[u];
  t.chg = -1, t.inv = 0;  t.l = l, t.r = r;
  if(l == r) {
    scanf("%d", &t.rx);
    t.lx = t.rx ;
    t.maxl[1] = t.maxr[1] = t.max[1] = t.s[1] =  t.rx;
    t.maxl[0] = t.maxr[0] = t.max[0] = t.s[0] = !t.rx;
    return ;
  }
  int mid = MID(l, r);
  build(L(u), l, mid), build(R(u), mid+1, r);
  push_up( u );
}
void push_self_change(int u, int val)
{
  Node &t = f[u];  int len = t.r - t.l + 1;
  t.s[val]  = t.max[val]  = t.maxl[val]  = t.maxr[val]  = len;
  t.s[!val] = t.max[!val] = t.maxl[!val] = t.maxr[!val] = 0;
  t.lx = t.rx = val;
}

void Change(int u, int l, int r, int val)
{
  if(l == f[u].l && f[u].r == r) {
    f[u].chg = val, f[u].inv = 0;
    push_self_change(u, val);
    return ;
  }
  push_down( u );
  int mid = MID(f[u].l, f[u].r);
  if(r <= mid) Change(L(u), l, r, val);
  else if(mid < l) Change(R(u), l, r, val);
  else Change(L(u), l, mid, val), Change(R(u), mid+1, r, val);
  push_up( u );
}
void push_self_inverse( int u )
{
  Node &t = f[u];
  t.inv = !t.inv;
  if(t.l != t.r) t.lx = !t.lx, t.rx = !t.rx;
  else t.lx = t.rx = !t.rx;
  swap(t.s[0], t.s[1]);
  swap(t.max[0], t.max[1]), swap(t.maxl[0], t.maxl[1]), swap(t.maxr[0], t.maxr[1]);
}
void Inverse(int u, int l, int r)
{
  if(l == f[u].l && f[u].r == r) {
    if(f[u].chg != -1) {              //����Ĵ������Ҫ������
      Change(u, l, r, !f[u].chg);     //������λ�WA
      return ;                        //��Ϊ��Ҫ��֤chg��inv����lazy��ǲ���ͬʱ��������
    }
    push_self_inverse( u );
    return ;
  }

  push_down( u );
  int mid = MID(f[u].l, f[u].r);
  if(r <= mid)      Inverse(L(u), l, r);
  else if(mid < l)  Inverse(R(u), l, r);
  else              Inverse(L(u), l, mid), Inverse(R(u), mid+1, r);
  push_up( u );
}
int SumOne(int u, int l, int r)
{
  if(l == f[u].l && f[u].r == r)  return f[u].s[1];

  if(f[u].chg != -1 || f[u].inv)  push_down( u );

  int mid = MID(f[u].l, f[u].r);
  if(r <= mid)      return SumOne(L(u), l, r);
  else if(mid < l)  return SumOne(R(u), l, r);
  else              return SumOne(L(u), l, mid) + SumOne(R(u), mid+1, r);
}
int Query(int u, int l, int r)
{
  if(l == f[u].l && f[u].r == r) return f[u].max[1];

  if(f[u].chg != -1 || f[u].inv) push_down( u );

  int mid = MID(f[u].l, f[u].r);
  if(r <= mid)      return Query(L(u), l, r);
  else if(mid < l)  return Query(R(u), l, r);
  else {
    int tmp1 = Query(L(u), l, mid), tmp2 = Query(R(u), mid+1, r);
    if(f[L(u)].rx == 1 && f[R(u)].lx == 1)
      tmp1 = max(tmp1, min(f[L(u)].maxr[1], mid-l+1)+min(f[R(u)].maxl[1], r - mid));
    return max(tmp1, tmp2);
  }
}
int main()
{
  int n, query, a, b, op;
  scanf("%d%d", &n, &query);
  build(1, 0, n-1);
  while( query-- ) {
    scanf("%d%d%d", &op, &a, &b);

    if(op <= 1) Change(1, a, b, op);
    else if(op == 2) Inverse(1, a, b);
    else if(op == 3) printf("%d\n", SumOne(1, a, b));
    else printf("%d\n", Query(1, a, b));
  }
  return 0;
}
