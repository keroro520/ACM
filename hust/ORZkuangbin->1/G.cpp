/*
	思路题 
	题意：主角攻击力m。有n个怪物来围殴主角，n个怪物生命值hp[i], 攻击力atk[i]
		  每人每秒可以攻击一次，主角也是一样。主角每秒能给对方给予某一个还活着的怪物m点的伤害，当怪物生命值减完就算怪物over了~。所有活着的怪物都会同时攻击主角。如m = 10，某怪物hp = 7, atk = 3，则主角能一秒废了该怪物，但同时也要受到该怪物的3点伤害。
		  问，主角最少耗费多少生命值就能吧n只怪物都消灭掉？

	思路：我X，一开始竟然往网络流那边想，囧=_=

		  未果，看n挺大(10000)，cases数挺大，想可能有什么贪心之类的策略。
		  假设对于怪物a,b，我们要先消灭哪一个比较好呢？   对于a先和b先列个式子比较一下就OK了。
		  所以就想到利用上述性质来排个序搞，敲就A了。没有证明该比较逻辑为何具有可传递性。
*/
#include <math.h>
#include <stdio.h>
#include <algorithm>
using namespace std;
#define		MAXN		10005
typedef		long long ll;
struct Monster {
	int hp, atk;
} a[MAXN];
int n, m;
bool cmp(const Monster & a, const Monster & b) {
	int tmp = a.hp * a.atk - b.hp * b.atk + (a.hp + b.hp) * (b.atk - a.atk);
	return tmp < 0;
}
int main()
{
	int cases, Cas = 0;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d", &n, &m);
		for(int i = 0; i < n; i++) scanf("%d %d", &a[i].hp, &a[i].atk), a[i].hp = (int) ceil(a[i].hp*1.0 / m);
		sort(a, a+n, cmp);
		//for(int i = 0; i < n; i++) printf("! %d %d\n", a[i].hp, a[i].atk);
		ll ans = 0, time = 0;
		for(int i = 0; i < n; i++) {
			time += a[i].hp;
			ans += time * a[i].atk;
		}
		printf("Case #%d: %I64d\n", ++Cas, ans);
	}
	return 0;
}
