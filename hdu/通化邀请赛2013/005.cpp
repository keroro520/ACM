#include <stdio.h>
#include <algorithm>
using namespace std;
int n;

int gcd(int a, int b)
{
	if(b == 0) return a;
	else return gcd(b, a%b);
}
bool check(int x, int y, int z)
{
	if(x < y) swap(x, y);
	int g = gcd(x,y);

	int l = x*y/g;
	if(g > z) g = gcd(g, z);
	else g = gcd(z, g);

	int tmp = gcd(max(l, z) , min(l, z));

	l = l * z  / tmp;
	if(g != 1) return false;
	if(l != n) return false;
	return true;
}
int  work()
{
	int ans = 0;
	for(int i = 1; i <= n; i++) if(n % i == 0)
		for(int j = i; j <= n; j++) if(n % j == 0)
			for(int k = j; k <= n; k++) if(n % k == 0)
				if(check(i,j,k)) {
					if(i != j && i != k && j != k) ans += 6;
					else ans += 3;
					printf("%d %d %d \n", i,j,k);
				}
	return ans;
}
int main()
{	
	n = 8*3;   ;
	printf("%d  ans=%d\n", n, work());
	return 0;
}
