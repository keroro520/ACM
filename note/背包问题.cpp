
/*
	多重背包二进制优化
*/
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
