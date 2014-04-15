#include <algorithm>
#include <iostream>
using namespace std;
#define		MOD		1000000007

int a[100];
bool check(int n)
{
	for(int i = 0; i < n; i++) if(a[i] == i + 1) return false;
	return true;
}
long long work(int n)
{
	long long ans = 0;
	for(int i = 0; i < n; i++) a[i] = i + 1;
	while(next_permutation(a, a+n)) {
		ans = (ans + check(n)) % MOD;
	}
	return ans;
}
int main()
{
	for(int i = 1; i <= 13; i++) {
		cout << i << " : " << work(i) << endl;
	}
	return 0;
}
