/*
	康托展开/康托展开逆

	不会处理重复元素的康托展开...貌似不简单，不搞了...=_=

	http://hi.baidu.com/snowingforest/item/fc73eaf972531b6a3c148583
*/
#include <string.h>
#include <stdio.h>
#define		MAXN		1000
int a[MAXN], fac[MAXN];
bool boo[MAXN];

void init_fac()
{
	fac[0] = 1;
	for(int i = 1; i < 30; i++) fac[i] = fac[i-1] * i;
}
int contor(int *a, int n)
{
	int ans = 0;
	memset(boo, false, sizeof(bool) * (n + 1));
	for(int i = 0; i < n; i++) {	
		int tot = 0;
		for(int j = 1; j < a[i]; j++) if(!boo[j]) tot++;
		ans += fac[n-1-i] * tot;
		boo[ a[i] ] = true;
	}
	ans ++;
	return ans;
}
void contor_inv(int x, int n, int *a)
{
	x --;
	memset(a, 0, sizeof(int) * n);
	memset(boo, false, sizeof(bool) * (n + 1));
	for(int i = n-1; i >= 0; i--) {
		a[n-1-i] = x / fac[i];
		x %= fac[i];
	}
	for(int i = 0; i < n; i++) {
		int j, tot = a[i];
		for(j = 1; tot >= 0; j++) if(!boo[j]) tot--;
		boo[--j] = true;
		a[i] = j;
	}
}
int main()
{
	init_fac();
	int n, x;
	scanf("%d", &n);
	scanf("%d", &x);
	contor_inv(x, n, a);
	for(int i = 0; i < n; i++) printf("%d ", a[i]);   puts("");
	//for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	//printf("%d\n", contor( a, n ));
	return 0;
}
