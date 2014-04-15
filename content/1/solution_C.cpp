/*
    简单并查集。
    注意，因为有“背叛”，而且是带小弟背叛这么一说，所以在“并操作”的时候不能压缩路径！  到最后输出序列的时候才压缩路径。
    压缩路径的正确性的成立是建立在这么一个条件上的：两个元素并在一个集合之后，那后面它们都会在同一个集合里。
    但是这里的“背叛”因素不符合上述条件，两个社团可能原来属同一大boss社，但是有可能某一个会被其它社团挖墙角，背叛出去。

    判断标签是否有某一个相同，若是直接遍历法比较的话可能会超时。需要用到位运算，因为 m < 60，我们可以用一个long long来模拟一个社团的标签label[i]，若i社具有标签k，则label[i]的二进制的第k-1个位置是1.
*/
#include <stdio.h>
#define     MAXN    100005
#define     MAXM    60

int n, m, C;
long long label[MAXN];
int power[MAXN], father[MAXN];

void check_and_move(int x, int y) {
    if(!(label[x] & label[y])) return ;
    if(power[x] > power[y]) father[y] = x;
    else if(power[x] < power[y]) father[x] = y;
}
int find(int x) {
    return x == father[x] ? x : father[x] = find(father[x]);
}

int main()
{
    int l, x, y;
    scanf("%d%d%d", &n, &m, &C);
    for(int i = 1; i <= n; i++) {
        scanf("%d%d", &power[i], &l);
        while(l--) {
            scanf("%d", &x);
            label[i] |= (1LL << x);
        }
    }
    for(int i = 1; i <= n; i++) father[i] = i;
    while(C--) {
        scanf("%d%d", &x, &y);
        check_and_move(x, y);
    }
    for(int i = 1; i <= n; i++) printf("%d%c", find(i), i == n ? '\n' : ' ');
    return 0;
}
