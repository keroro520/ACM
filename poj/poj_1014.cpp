/*
	多重背包模板题  二进制优化
	题意：有分别价值为1,2,3,4,5,6的6种物品，输入6个数字，表示相应价值的物品的数量，问一下能不能将物品分成两份，是两份的总价值相等，其中一个物品不能切开

	思路：dfs或多重背包+二进制优化
		void Multiple_Pack()
		{
			for(int i = 1; i <= 6; i++) {
				int j;
				for(j = 0; num[i] >= (1 << (j+1)) - 1; j++)		//拆成1,2,2^2,...,2^(k-1),M-2^k+1，且k是满足M-2^k+1 > 0的最大整数
					One_Pack(i*(1 << j));
				One_Pack(i*(num[i] - (1<<j) + 1));
			}
		}
*/
#include <string.h>
#include <stdio.h>
int num[7], f[20005*6], m;

void One_Pack(int val)
{
	for(int j = m; j >= val; j--) f[j] = f[j] || f[j-val];
}
void Multiple_Pack()
{
	for(int i = 1; i <= 6; i++) {
		int j;
		for(j = 0; num[i] >= (1 << (j+1)) - 1; j++)		//拆成1,2,2^2,...,2^(k-1),M-2^k+1，且k是满足M-2^k+1 > 0的最大整数
			One_Pack(i*(1 << j));
		One_Pack(i*(num[i] - (1<<j) + 1));
	}
}
int main()
{
	for(int Cas = 1; ;Cas++) {
		memset(f, false, sizeof(f));
		f[0] = true;
		m = 0;
		for(int i = 1; i <= 6; i++) scanf("%d", &num[i]), m += num[i] * i;
		if(m == 0) break;
		printf("Collection #%d:\n", Cas);
		if(m & 1) {
			puts("Can't be divided.\n");
			continue;
		}
		m >>= 1;
		Multiple_Pack();
		puts(f[m] ? "Can be divided.\n" : "Can't be divided.\n");
	}
	return 0;
}
