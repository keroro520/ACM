#include <vector>
#include <stdio.h>
#define		MID(l,r)		(((l) + (r)) >> 1)
#define		L(x)			((x)  << 1)
#define		R(x)			(((x) << 1) + 1)
using namespace std;
#define     MAXN        (1 << 18)
struct Node {
	int l, r, num, ch;
} f[MAXN * 4];
int a[MAXN], pos[MAXN];

int calc(int a, int b, int ch)
{
    if(ch == 0) return (a|b);
    else return (a^b);
}
void Update(int u)
{
	while(u != 0) {
		f[u].num = calc(f[L(u)].num, f[R(u)].num, f[u].ch);
		u >>= 1;
	}
}
void build(int u, int l, int r)
{
	if(l == r) {
		f[u].ch = 1;
		f[u].num = a[l];
		pos[l] = u;
		return ;
	}
	int mid = MID(l, r);
	build(L(u), l, mid);
	build(R(u), mid+1, r);
	f[u].ch = !f[L(u)].ch;
	f[u].num = calc(f[L(u)].num, f[R(u)].num, f[u].ch);
}

void solve(int n, int query);
int main()
{
	int n, query;
	while(scanf("%d%d", &n, &query) != EOF) {
		solve(n, query);
	}
	return 0;
}
void solve(int n, int query)
{
    int p, b;
    for(int i = 0; i < (1 << n) ; i++) {
        scanf("%d", &a[i]);
    }
	build(1, 0, (1 << n)-1);
	while(query--) {
		scanf("%d%d", &p, &b);
		p--;
		f[ pos[p] ].num = b;
		Update((pos[p] / 2));
		printf("%d\n", f[1].num);
	}
}
