/*
    线段树  简单题   单点更新
*/
#include <stdio.h>
#define     debug       printf("!\n")
#define     MAXN        50005
#define     MID(x, y)   (((x)+(y)) >> 1)
#define     L(x)        ((x)<<1)
#define     R(x)        (((x)<<1)|1)
int a[MAXN], pos[MAXN], n;

struct Node {
    int left, right, sum;
} f[MAXN * 3];

void Update(int root, int add)
{
    f[root].sum += add;
    if(root == 1) return ;
    Update(root >> 1, add);
}
int Query(int root, int left, int right)
{
    if(left == f[root].left && f[root].right == right) {
        return f[root].sum;
    }
    int mid = MID(f[root].left, f[root].right);
    if(right <= mid) return Query(L(root), left, right);
    else if(mid < left) return Query(R(root), left, right);
    else return Query(L(root), left, mid) + Query(R(root), mid+1, right);
}
void build(int root, int left, int right)
{
    f[root].left = left, f[root].right = right;
    if(left == right) {
        f[root].sum = a[left];
        pos[left] = root;
        return ;
    }
    int mid = MID(left, right);
    build(L(root), left, mid);
    build(R(root), mid+1, right);
    f[root].sum = f[L(root)].sum + f[R(root)].sum;
}
int main()
{
    int Cas = 0, cases, x, l, r;
    char op[100];
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        printf("Case %d:\n", ++Cas);
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        build(1, 1, n);
        while(scanf("%s", op)) {
            if(op[0] == 'E') break;
            else if(op[0] == 'Q') {
                scanf("%d%d", &l, &r);
                printf("%d\n", Query(1, l, r));
            } else {
                scanf("%d%d", &l, &x);
                if(op[0] == 'S') x = -x;
                Update(pos[l], x);
            }
        }
    }
    return 0;
}
