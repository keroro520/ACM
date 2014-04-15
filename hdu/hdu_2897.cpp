/*
	博弈 Bash博弈扩展 启发题
	题意：一堆石子，一次至少取p个，最多取q个，取走最后一颗的输。

	思路：bash博弈由(1-m)变到(p-q).
		  
		  若n % (p+q) == 0，先手可以先取q个，然后对方取k个的话我再取(q+p-k)个，这样，维持剩余的石子数mod(p+q) == p
		  其实到了这里可以看出，取石子是以(p+q)为循环节继续下去的。所以找规律时候可以直接考虑p+q >= n >= 0
		  若n % (p+q) == r, 且r > p，则先手取p~r-1颗都可以，这样，可以同<1>的方法，维持剩余石子数mod(p+q) <=p
		  若n % (p+q) == r, 且r <= p，则无论先手取多少，后手总是可以利用<1><2>的方法来对付先手。

	收获：这种类型的bash取石子，好像都可以先在一个区间内先找出规律，然后再找出他们的循环节，就可以容易地推出规律。如下面的打表方法。
*/
//hdu 2897
#include <stdio.h>

int main()
{
	int n, p, q;
	while(scanf("%d%d%d", &n, &p, &q) != EOF) {
		int win = 1;
		if(n % (p + q) == 0) win = 0;
		if(n % (p + q) > p) win = 0;
		puts(!win ? "WIN" : "LOST");
	}
	return 0;
}

/*  某人用sg来打表找出规律，ORZ...
我也想了个找规律的办法，只要打n = 1..(p+q+1)*2 说不定规律就看出来了。因为目测答案更(p+q)或者(p+q+1)有关，bash博弈升级版嘛。
#include <stdio.h>
#include <string.h>
#define		MAXN		65538
int sg[MAXN];
int n, p, q;
int SG(int u)
{
	if(u <= p) return 0;
	if(sg[u] != -1) return sg[u];
	bool vis[MAXN];
	memset(vis, false, sizeof(bool) * (n+1));
	for(int i = p; i <= q; i++) vis[SG(u - i)] = true;
	for(int i = 0; ; i++) if(!vis[i]) return sg[u] = i;
}
int main()
{
	while(scanf("%d%d%d", &n, &p, &q) != EOF) {
		memset(sg, -1, sizeof(sg));
		puts(SG(n) ? "WIN" : "LOST");
	}
	return 0;
}
*/
