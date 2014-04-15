/*
    线段树   单点更新最值   简单题
*/
#include <stdio.h>
#include <algorithm>
using namespace std;
#define     debug       printf("!\n")
#define     MAXN        200005
#define     MID(x, y)   (((x)+(y)) >> 1)
#define     L(x)        ((x)<<1)
#define     R(x)        (((x)<<1)|1)

struct Node {
    int left, right, max;
} f[MAXN * 5];
int pos[MAXN], a[MAXN], n;

void Update(int root)
{
   if(root == 0) return ;
   int tmp = f[root].max;
   f[root].max = max(f[L(root)].max, f[R(root)].max);
   if(tmp != f[root].max) Update(root >> 1);
}
int Query(int root, int left, int right)
{
    if(left == f[root].left && f[root].right == right) {
        return f[root].max;
    }
    int mid = MID(f[root].left, f[root].right);
    if(right <= mid) return Query(L(root), left, right);
    else if(mid < left) return Query(R(root), left, right);
    else return max(Query(L(root), left, mid), Query(R(root), mid+1, right));
}
void build(int root, int left, int right)
{
    f[root].left = left, f[root].right = right;
    if(left == right) {
        f[root].max = a[left];
        pos[left] = root;
        return ;
    }
    int mid = MID(left, right);
    build(L(root), left, mid);
    build(R(root), mid+1, right);
    f[root].max = max(f[L(root)].max, f[R(root)].max);
}
int main()
{
    int A, B, m;
    char op[10];
    while(scanf("%d%d", &n, &m) != EOF) {
        for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
        build(1, 1, n);
        while(m--) {
            scanf("%s%d%d", op, &A, &B);            //原本输入用的是char，WA了N次后用char*
            if(op[0] == 'Q') {
                if(A > B) swap(A, B);
                printf("%d\n", Query(1, A, B));
            } else {
                f[pos[A]].max = B;
                Update(pos[A] >> 1);
            }
        }
    }
    return 0;
}
