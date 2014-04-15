/*
	费马定理判定质数  a^n % n == a
*/
// http://acm.hust.edu.cn/vjudge/contest/view.action?cid=33571#problem/B 
#include <stdio.h>
typedef long long ll;
bool boo[65005];
ll  MOD = 7;
ll SQR(ll x) {
	return x * x % MOD;
}
ll myPow(ll a, ll n)
{
	if(n == 0)   return 1;
	if(n & 1LL)  return a * SQR(myPow(a, n/2)) % MOD; 
	else 	     return     SQR(myPow(a, n/2));
}
void init()
{
	for(int i = 2; i <= 65000; i++) if(!boo[i]) {
		int j = i+i;
		while(j <= 65000) boo[j] = true, j += i;
	}
}
bool check(int n)
{
	MOD = n;
	for(int i = 2; i < n; i++) if((int)myPow((ll)i, (ll)n) != i) { return true; }
	return false;
}
int main()
{
	int n;
	init();
	//printf("! %lld\n", myPow(3, 2));
	while(scanf("%d", &n) , n) {
		if(boo[n] == false || check(n)) printf("%d is normal.\n", n);
		else printf("The number %d is a Carmichael number.\n", n);
	}
	return 0;
}
