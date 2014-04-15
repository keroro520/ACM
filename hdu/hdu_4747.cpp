/*
	线段树  区间乱搞	好题  思路题
	题意：给定一个长度为 n 的非负数列，定义 mex(l, r) 为 l，r 区间里最小的没有出现的数字。求所有 mex(l, r) 的和

	思路：比赛时想了一种分治区间的算法，虽然感觉可行，但是无奈细节巨烦，搞了3个小时都没搞出来！！！简单记录一下：以a[i]=0的i为中间分界线，把区间分成两部分，然后依次对两个区间找1,2,3...不断删区间，不断乱搞...

		  看了xiaodao的题解，巨赞。

		  ***直接合并区间难以进行时。。利用离线先固定一个端点。。沿着另一个端点扫应该是接下来第一个要想的方法了***
		  先搞出mex[i]表示初始的mex(1,i)，已知是单调递增的。
		  next[x]记录右边第一个和a[x]相同的位置，如果没有则等于n+1
		  沿着左端开始删除。。删除前要统计出以这个点为左端点的所有mex
		  考虑删除a[L]，那么将L+1到next[L]-1之间的mex值大于a[i]的全设置成a[i]
		  于是...我们需要维护...区间求和...区间修改...线段树裸题...
		  爆搞的话会TLE。
		  进一步分析发现mex至始至终都是单增的，所以对于上述“i到next[i]-1中mex值大于a[i]的改为a[i]”只要找到(i,next[i]-1)第一个mex值比a[i]大的位置，再区间覆盖即可，那找这个位置也是很简单的，Find()函数.


		  做完后看别人代码发现其实若a[i] > i则可以不用管它...
*/
#include <stdio.h>
#include <string.h>
#include <map>
#include <algorithm>
using namespace std;
#define		debug		printf("!\n")
#define		MAXN		200005
#define		L(x)		((x) << 1)
#define		R(x)		(((x) << 1) | 1)
#define		MID(l,r)	(((l) + (r)) >> 1)
map<int,int> M;
struct Segment_Tree {
	int l, r, lazy, num;
	long long sum;
} f[MAXN << 2];
int head[MAXN], next[MAXN], a[MAXN], b[MAXN], n;

void _Update(int u, int l, int r, int val);
void push_up(int u)
{
	f[u].num = max(f[L(u)].num, f[R(u)].num);
	f[u].sum = f[L(u)].sum + f[R(u)].sum;
}
void push_down(int u)
{
	_Update(L(u), f[u].l, f[L(u)].r, f[u].lazy);
	_Update(R(u), f[R(u)].l, f[u].r, f[u].lazy);
	f[u].lazy = -1;
}
long long _Query(int u, int l, int r)
{
	if(l <= f[u].l && f[u].r <= r) return f[u].sum;
	if(f[u].lazy != -1) push_down(u);
	int mid = MID(f[u].l, f[u].r);
	if(r <= mid) return _Query(L(u), l, r);
	else if(mid < l) return _Query(R(u), l, r);
	else return _Query(L(u), l, mid) + _Query(R(u), mid+1, r);
}
void _Update(int u, int l, int r, int val)
{
	if(l <= f[u].l && f[u].r <= r) {
		f[u].lazy = val;
		f[u].num = val;
		f[u].sum = val * (r - l + 1);
		return ;
	}
	if(f[u].lazy != -1) push_down(u);
	int mid = MID(f[u].l, f[u].r);
	if(r <= mid) _Update(L(u), l, r, val);
	else if(mid < l) _Update(R(u), l, r, val);
	else _Update(L(u), l, mid, val), _Update(R(u), mid+1, r, val);
	push_up(u);
}

int Find(int u, int l, int r, int val)
{
	if(f[u].num <= val) return -1;
	if(f[u].l == f[u].r) return f[u].l;

	int mid = MID(f[u].l, f[u].r);
	if(r <= mid) return Find(L(u), l, r, val);
	else if(mid < l) return Find(R(u), l, r, val);
	else {
		if(f[L(u)].num > val) return Find(L(u), l, mid, val);
		else return Find(R(u), mid+1, r, val);
	}
}
void Update(int pos)
{
	if(next[pos] == n+1) {
		int tmp = Find(1, pos+1, n, a[pos]);
		if(tmp == -1) return ;
		_Update(1, tmp, n, a[pos]);
	} else  {
		int tmp = Find(1, pos+1, next[pos]-1, a[pos]);
		if(tmp == -1) return ;
		_Update(1, tmp, next[pos]-1, a[pos]);
	}
}
long long Query(int pos)
{
	return _Query(1, pos, n);
	//if(next[pos] == n+1) return _Query(1, pos, n);
	//return _Query(1, pos, next[pos]);
}
void build(int u, int l, int r)
{
	f[u].l = l, f[u].r = r, f[u].lazy = -1;
	if(l == r) {
		f[u].sum = f[u].num = b[l];
		return ;
	}
	int mid = MID(l,r);
	build(L(u), l, mid), build(R(u), mid+1, r);
	push_up(u);
}

void init()
{
	int Mex = 0, Index = 0;
	M.clear();
	for(int i = 1; i <= n; i++) {
		if(a[i] == Mex) {
			do {
				Mex++;
			} while(M[ Mex ]);
		}
		b[i] = Mex;
		if(M[ a[i] ] == 0) M[ a[i] ] = ++Index;
	}

	for(int i = 0; i <= Index; i++) head[i] = n+1;
	for(int i = n; i > 0; i--) {
		int x = M[ a[i] ];
		next[i] = head[x];
		head[x] = i;
	}
}
int main()
{
	while(scanf("%d", &n) != EOF && n) {
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		init();	
		build(1, 1, n);
		long long ans = 0;
		for(int i = 1; i < n; i++) {
			ans += Query(i);
			Update(i);
		}
		ans += (a[n] == 0 ? 1 : 0);
		printf("%I64d\n", ans);
	}
	return 0;
}
