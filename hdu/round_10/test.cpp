#include <string.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
#define		MAXN		100005
#define		MOD		1000000007
#define		CON		1024
long long mm[MAXN];
long long Bit[MAXN];
int a[MAXN];
string s;
#define		SQR(x)	((x) * (x))
long long calc_mm(int x)
{
	if(x == 1) return mm[x] = CON;
	if(mm[x] != -1) return mm[x];
	if(x & 1) return mm[x] = CON * calc_mm(x-1) % MOD;
	else return mm[x] = SQR(calc_mm(x/2)) % MOD;
}
void init()
{
	int tmp = 1;
	Bit[0] = 1;
	for(int i = 1; i < MAXN; i++) Bit[i] = (Bit[i-1] << 1) % MOD;
	memset(mm, -1, sizeof(mm));
	mm[0] = 1;
	for(int i = 100000; i > 0; i--) if(mm[i] == -1) calc_mm(i);
}

int main()
{
	init();
	cin >> s;
	int len = s.length();
	int k = len -1 ;
	while(s[k] == '0') k--;
	s[k]--;
	k++;
	for(k; k < len; k++) s[k] = '9';
	for(int i = 0; i < len; i++) a[i] = s[i] - '0';
	long long ans = 1;
	for(int i = 0; i < len; i++) 
		ans = (ans * Bit[a[i]]) % MOD;
	cout << ans << endl;
	for(int i = 0; i < len-1; i++) {
		if(i < len-1 && len > 1) ans = (ans * mm[len-i-1]) % MOD;
		cout << "# " << ans << endl;
	}
		// ans = (ans * Bit[len-i-1]) % MOD;
	cout << ans << endl;
	return 0;
}
