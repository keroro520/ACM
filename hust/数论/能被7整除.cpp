/*
	判断n能否被7/11/13整除

	正整数n能被7/11/13整除，充要条件是n = ak*1000^k + ak-1 * 1000^(k-1) + ... + a0，7/11/13能整除(a0+a2+a4) - (a1+a3+..)的总和
	证明是用同余的性质证明的，《初等数论》P51
*/	

#include <string.h>
#include <string>
#include <stdio.h>
#include <algorithm>
#define				MOD				7
using namespace std;

char str[10000000];
int s2i( string &s, int &i, int size )
{
	size = min(size, (int)s.length() - i);
	int x = 0;
	i = i + size;
	for( int j = i - 1; size ; j--,size-- ) x = x * 10 + s[j] - '0';
	return x;
}
int main()
{
	while( scanf("%s", str) != EOF ) {
		string s = (string) str;
		int len = s.length();
		reverse(s.begin(), s.end());
		int flag = 1, i = 0, sum = 0;
		while(i < len) {
			int x = s2i( s, i, 3 );
			sum += flag * x;
			flag = -flag;
		}
		puts( sum % MOD == 0 ? "YES" : "NO" );
	}
	return 0;
}
