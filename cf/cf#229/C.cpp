// 思路题  偏移量  预处理
// ans[k][i] 表偏移量为k，位置为i的action数，题目给k <= 10
// 预处理出来ans[][]就可以了
#include <stdio.h>
int ans[15][100005];
int n, K;
char str[100005];

int main()
{
	int w, l, r, k;
	scanf("%d %d %d", &n, &K, &w);
	scanf("%s", str+1);
	for(int k = 0; k < K; k++) {
		for(int i = 1; i <= n; i++) {
			if( (str[i] == '0' && (i-k) % K == 0) || (str[i] == '1' && (i-k) % K != 0) ) ans[k][i] = ans[k][i-1] + 1;
			else ans[k][i] = ans[k][i-1];
		}
	}
	while(w--) {
		scanf("%d %d", &l, &r);
		k = ((l - 1) % K + K) % K;
		printf("%d\n", ans[k][r] - ans[k][l-1], k);
	}	
	return 0;
}
