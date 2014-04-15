/*
	贪心
	题意：给出若干个正方形(0,0,ai,ai), ai>0, 要求输出一个点的座标，这个点被k个正方形包含（在边上也算）

	思路：每个正方形都是以(0,0)和(ai,ai)为顶点的，因此将输入的数据按照ai进行排序，输出a[k],a[k]即满足要求
*/
#include <stdio.h>
#include <functional>
#include <algorithm>
using namespace std;

int a[100];
int main()
{
	int n, k;
	scanf("%d%d", &n, &k);
	if(k > n) {
		puts("-1")
		; return 0;
	}
	for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
	sort(a+1, a+n+1, greater<int>() );
	printf("%d %d\n", a[k], a[k]);
	return 0;
}
