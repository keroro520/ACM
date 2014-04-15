/*
	树状数组 离线查询   好题  启发题  经典题 

	题意：序列{A}, ai<=200000，若干询问[l,r]，回答区间[l,r]内有多少个ai与区间内其它数都互质

	我是觉得这道题跟bzoj那道“求区间内不同的数字个数”很类似，如过我们把“不互质的数Not co-prime”对应着“不同数字”，那就很像了。
	但不同点，也是这道题的难点在于，a与b不互质，b与c不互质，但a与c不一定不互质，也就是说，bzoj那道题的“相同关系”是有传递性的，但这里的“不互质关系”是没有传递性的！

	那怎么解决这一问题呢？
	我先预处理出对于每一个ai，右端第一个不互质的数aj，我用个vector<int> R来存，R[j].push_back( i )；还预处理出L[i]表示ai的左端第一个与ai不互质的数的位置
	然后离线扫描的时候，对于当前i，我把R[i]里面的下标全都减1（思考一下就会发现，减1之后肯定为0），L[i]再减1，i加1（就对应与bzoj那道题“对于之前所有和ai相等的数都为0，然后当前i加1，L[i]减1”）。
	说一下为什么这么操作：
	R[i]里面的全都减1：易知每个下标x只会存在于一个R[i]里面。这个操作就相当于，把i左端的“右端first Not co-prime的数为ai”的x消为0，因为我们之前遇到每一个x都加了1，这里遇到ai是第一个与ax不互质的数，我们要把x消掉为0
	L[i]减1：i的哨兵，不解释
	i加1：不解释
	
	还有很重要的一个操作：在我们R[i]里的所有x都减1的时候判断一下 if(L[x] != -1) Update(L[x], +1);		//Attention!
						  这个操作的目的就是把x的哨兵消掉



	
	再联 系一下bzoj 1878，来写一下两题的对应联系
	同：
	hdu 4777 的Not co-prime关系对应着bzoj 1878的equal相等关系
	hdu 4777 的R[i]里面的数其实就是对应着bzoj 1878的L[i]
	hdu 4777 的L[i]也是对应着bzoj 1878的L[i]
	所以我们的操作都用L[i]作为哨兵, Update(L[i], -1)

	异：
	<一对一 与 一对多>
	bzoj 1878离线扫描时保证前面aj = ai,j < i都已经把j位置上的树状数组搞为0了，当然哨兵为-1除外，所以查询的时候时候可以Query(l,r)
	hdu  4777离线扫描时对应着要保证对于gcd(aj, ai) != 1的位置j，j在树状数组里面为0，哨兵为-1除外，所以查询的时候可以Query(l,r).
	那对于搞为0的操作，bzoj 1878只要消L[i]即可，因为是“一对一”的关系；hdu 4777需要对于R[i]里的每个x都手动消为0，因为这里是一对多的关系---ai左端有多个不互质的关系

	bzoj 1878的一对一关系，使得我们每次只要Update(L[L[i]], +1)就可以消掉之前的影响；hdu 4777的一对多关系，就要求我们得对每个x ∈ R[i]，都得Update(L[x], +1)

	<传递性 与 非传递性>
	其实传递性就是一对一，非传递性就是一对多
*/
#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;
#define		INF			999999999
#define		low(x)		((x) & (-(x)))
#define		Pii			pair<int,int>
#define		MAXN		200005

int L[MAXN], a[MAXN], p[MAXN], ans[MAXN], c[MAXN];
compositel composite[MAXN];
vector<int> factor[MAXN], R[MAXN];
vector<Pii> Q[MAXN];
int n;

void Update(int pos, int val)
{
	while(pos <= n) {
		c[pos] += val;
		pos += low(pos);
	}
}
int Query(int pos)
{
	int sum = 0;
	while(pos) {
		sum += c[pos];
		pos -= low(pos);
	}
	return sum;
}
void init_factor()
{
	for(int i = 2; i <= 200000; i++) if(!composite[i]) 
		for(int j = i+i; j <= 200000; j += i) composite[j] = true;
	
	for(int i = 2; i <= 200000; i++) if(!composite[i])
		for(int j = i; j <= 200000; j += i)
			factor[j].push_back( i );
}
void init()
{
	memset(c,   0, sizeof(c));
	memset(p,  -1, sizeof(p));
	for(int i = 1; i <= n; i++) Q[i].clear(), R[i].clear();
	for(int i = 1; i <= n; i++) {
		int tmp = -1;
		for(vector<int> :: iterator it = factor[ a[i] ].begin(); it != factor[ a[i] ].end(); it++) {
			tmp = max(tmp, p[*it]);
			p[ *it ] = i;
		}
		L[i] = tmp;
	}

	for(int i = 1; i <= 200000; i++) p[i] = INF;
	for(int i = n; i >= 1; i--) {
		int tmp = INF;
		for(vector<int> :: iterator it = factor[ a[i] ].begin(); it != factor[ a[i] ].end(); it++) {
			tmp = min(tmp, p[*it]);
			p[*it] = i;
		}
		if(tmp != INF) R[tmp].push_back( i );
	}
}
void solve()
{
	for(int i = 1; i <= n; i++) {
		for(vector<int> :: iterator it = R[i].begin(); it != R[i].end(); it++) {
			Update(*it, -1);
			if(L[*it] != -1) Update(L[*it], +1);		//Attention!
		}
		if(L[i] != -1) Update(L[i], -1); 
		Update(i, 1);

		for(vector<Pii> :: iterator it = Q[i].begin(); it != Q[i].end(); it++) {
			ans[ it->second ] = Query(i) - Query(it->first-1);
		}
	}
}
int main()
{
	int query, l, r;
	init_factor();
	while(scanf("%d %d", &n, &query) , n || query) {
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		init();
		for(int i = 0; i < query; i++) {
			scanf("%d %d", &l, &r);
			Q[r].push_back( Pii(l, i) );
		}
		solve();
		for(int i = 0;i < query; i++) printf("%d\n", ans[i]);
	}
	return 0;
}
