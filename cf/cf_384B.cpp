// 趣题
// 直接搞很麻烦
// 后来发现其实m*(m-1)/2是sort一个数组的交换次数最大上限
// 然后...
#include <stdio.h>
int n, m, K;
int main()
{
	scanf("%d %d %d", &n, &m, &K);
	//for(int i = 0; i < n; i++) 
	//	for(int j = 0; j < m; j++) scanf("%d", &a[i][j]);
	printf("%d\n", m * (m-1) / 2);
	for(int i = 1; i < m; i++) {
		for(int j = i+1; j <= m; j++)
			if(K == 0) printf("%d %d\n", i, j);
			else	   printf("%d %d\n", j, i);
	}
	return 0;
}
