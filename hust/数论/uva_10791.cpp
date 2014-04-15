/*
	数论  分解质因子  Minimum Sum LCM  好题
	题意：给出最小公倍数n，要求找出至少由两个数组成的数集，该集合的LCM等于n，且该数集的总和最小

	思路：一开始想到了xxx不等式，分析觉得要找的数集大小肯定为2，就想找出符合a*b = n, a与b互质的最小a+b...然后就堕落进了万物罪恶之源...一开始的思路和推断都是不正确的...
		  
		  正解是分解质因子。将最小公倍数n分解成n = a1^p1 * a2^p2 * ... * ak^pk，发现LCM(a1^p1, a2^p2, ..., ak^pk) == n，易知我们找的数集里面肯定两两互质，不然不满足总和最小。所以算法就很明显了，要“两两互质，又总和最小”，那就是各个质因子的相应次方数之和
		  特殊地：n = 1时，ans = 2
		  		  n为素数，ans = n + 1
				  n只有单质因子，ans = n + 1
				  n = 2147483647，它是素数，此时输出2147483648，但超了int，应考虑用long long

		  实现里面分解因子时，每改变一次n的大小，可重新计算一遍sqrt(n)，减少冗余计算量
*/
#include <math.h>
#include <algorithm>
#include <stdio.h>
using namespace std;
typedef long long ll;

ll solve(ll n)
{
	ll flag = 0, sum = 0;
	for(ll oo = (ll)sqrt((double) n), i = 2; i <= oo; i++) if(n % i == 0) {
		ll tmp = 1;
		while(n % i == 0) {
			//sum += i; 
			tmp *= i;
			n /= i;
		}
		sum += tmp;
		flag++;
		oo = (ll)sqrt((double) n);		//加这句快了一倍
	}
	if(n > 1) sum += n, flag ++;
	if(flag == 1)     sum++;
	return sum;
}
int main()
{
	ll n; int Cas = 0;
	while(scanf("%lld", &n), n) {
		if(n == 1) printf("Case %d: %d\n", ++Cas, 2);
		else printf("Case %d: %lld\n", ++Cas, solve(n));
	}
	return 0;
}
