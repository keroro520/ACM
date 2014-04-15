/*
	欧拉函数
	题意：从1-n里选出两个数x，y，问有多少对(x,y)两两互质
	思路：若已知f(n)为从1-n里两两互质的对数，利用归纳证明容易推出f(n+1) = f(n) + (n+1)的欧拉函数值*2
*/
#include <string.h>
#include <stdio.h>

int euler[50005], f[50005];
void getEuler()		//欧拉函数线性筛
{
	memset(euler,0,sizeof(euler));
	euler[1] = 1;
	for(int i = 2;i <= 50000;i++)
		if(!euler[i])
			for(int j = i;j <= 50000; j += i) {
				if(!euler[j])
				euler[j] = j;
				euler[j] = euler[j]/i*(i-1);
			}
}
void init()
{
	f[1] = 1;
	for(int i = 2; i <= 50000; i++) f[i] = f[i-1] + euler[i]*2;
}
int main()
{
	getEuler();
	init();
	int n;
	while(scanf("%d" , &n) , n) {
		printf("%d\n", f[n]);
	}
	return 0;
}
