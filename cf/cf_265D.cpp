/*
	数论  DP
	题意：在一个递增序列{Ai}里面找出最长的good sequence，输出长度
	      good sequence {Xi}要满足：(1)xi < xi+1   (2)gcd(xi,xi+1) > 1   (3)xi是{A}里面的数

	思路：预处理出所有x的所有约数
		  无后效性，最优性什么容易知道。f[i]表示前i个数能够到达的最长good seq长度，则要更新f[i]的话就是要找之前出现过的能与ai约分的数
		  怎样快速地找到之前出现的能与ai约分的数呢？这里就用到了之前预处理出来的vector p[x]表x的约束集合啦~
		  用map M[x]记录目前为止，最近能够被x整除的数的位置。这样，我们对于ai，扫一边它的约数集合，发现M[x]不为空的话就更新f[i]
		  搞完后要记得更新M[x]~
*/
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <map>
using namespace std;
#define		MAXN	100005
map<int,int> M;
vector<int> p[MAXN];
int a[MAXN], f[MAXN];
bool boo[MAXN];
void init()
{
	memset(boo, false, sizeof(boo));
	for(int i = 2; i <= 100000; i++) if(!boo[i]) {
		int j = i + i;
		while(j <= 100000) {
			boo[j] = true;
			p[j].push_back(i);
			j += i;
		}
	}
}
int main()
{
	int ans = 1, n;
	init();
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) f[i] = 1;
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
		for(vector<int> :: iterator it = p[a[i]].begin(); it != p[a[i]].end(); it ++) {
			if(M[ *it ]) {
				f[i] = max(f[i], f[ M[*it] ] + 1);
			}
			M[ *it ] = i;			//记录能被*it整除的数的最后位置
		}
		M[ a[i] ] = i;
		ans = max(ans, f[i]);
	}
	printf("%d\n", ans);
	return 0;
}
