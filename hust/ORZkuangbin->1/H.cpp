/*
	博弈 sg函数
    题意：一个长度为n的珍珠环，每次只能选连续的m个未染色的珍珠染色，轮到谁不能染就输。

	思路：

    问题很容易变为，一条长度为n-m的珍珠链，轮流选连续m个未染色的珍珠染上色。
    假设长度为n的链，我们染上i,i+1,..,i+m-1，则原链n就变成两条子链(i-1),(n-(i+m-1))
    也就是说，当前链n可以变成两个后继状态(i-1),(n-i-m+1)，利用sg函数性质抑或之.
    for(i = 1; i < n-m; i++) vis[ sg(i-1) ^ (n-i-m+1) ] = true;

    sg函数只会用，不会证明啊...还是在wuyiqi的提示下想到用sg的，之前跟gyy虽然想到了递归分治，但是每想到sg，而是想了用类似dp状态转移那样搞，当热是错的。。不说了。。
*/
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
#define		MAXN		1005
int sg[MAXN];
int m;
int  SG( int n )
{
	if(n < m) return 0;
	if(sg[n] != -1) return sg[n];

	bool vis[MAXN];
	memset(vis, false, sizeof(vis));
	for(int i = 1; i <= n-m+1; i++) {
		vis[ SG(n - (i+m-1)) ^ SG(i-1) ] = true;
	}
	for(int i = 0; ; i++) if(!vis[i]) return sg[n] = i;
}
int main()
{
	int cases, Cas = 0, n;
	scanf("%d", &cases);
	while(cases--) {
		memset(sg, -1, sizeof(sg));
		scanf("%d %d", &n, &m);
		printf("Case #%d: ", ++Cas);
		if(n < m) puts("abcdxyzk");
		else      puts( !SG(n-m) ? "aekdycoin" : "abcdxyzk" );
	}
	return 0;
}
