#include <stdio.h>
#include <algorithm>
using namespace std;
#define     debug       printf("!\n")
#define     MAXN         50005
#define     L(x)        ((x)<<1)
#define     R(x)        (1+((x)<<1))
#define     MID(l, r)   (((l)+(r)) >> 1)
struct Node {int left, right, num;} f[MAXN * 3];
int a[MAXN];
int n;
void build(int root, int left, int right)
{
    f[root].left = left;
    f[root].right = right;
    if(left == right) {
        f[root].num = a[left];
        return ;
    }
    int mid = MID(left, right);
    build(L(root), left, mid);
    build(R(root), mid+1, right);
    f[root].num = max(f[L(root)].num, f[R(root)].num);
}
int Query(int root, int left, int right)
{
    if(left == f[root].left && f[root].right == right) {
        return f[root].num;
    }
    int mid = MID(f[root].left, f[root].right);
    if(right <= mid) return Query(L(root), left, right);
    else if(mid < left) return Query(R(root), left, right);
    else return max(Query(L(root), left, mid), Query(R(root), mid+1, right));
}
int main()
{
    int m, left, right;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    build(1, 0, n-1);
    scanf("%d", &m);
    while(m--) {
        scanf("%d%d", &left, &right);
        left--, right--;
        printf("%d\n", Query(1, left, right));
    }
    return 0;
}
