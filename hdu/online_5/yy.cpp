#include <string.h>
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
#define	MAXN	1005

string A, B, X, Y;
int n;
int c[MAXN], d[MAXN];
int  add_ (string a, string b, int *c);
int main()
{
	int cases, Cas = 0;
	scanf("%d", &cases);
	while(cases--) {
		printf("Case %d: ", ++Cas);
		cin >> n >> A >> X >> B >> Y;

		int len1 = add_(X, Y, c);
		int len2 = add_(A, B, d);
		if(len1 != len2 ) {
			puts("No");
			continue;
		}
		bool flag = true;
		for(int i = 0; i < len1; i++) if(c[i] != d[i]) flag = false;
		puts(flag ? "Yes" : "No");
	}
	return 0;
}

int  add_ (string a, string b, int *c)
{
	int len = a.length();
	for(int i = 0; i <= len/2; i++) swap(a[i], a[len-i]);
	len = b.length();
	for(int i = 0; i <= len/2; i++) swap(b[i], b[len-i]);
	len = max(a.length(), b.length());
	if(len != a.length()) {
		for(int i = len - a.length(); i > 0; i--) a += '0';
	} else {
		for(int i = len - b.length(); i > 0; i--) b += '0';
	}

	for(int i = 0 ; i < len; i++) a[i] = a[i] - '0', b[i] -= '0';
	memset(c, 0, sizeof(c));
	for(int i = 0; i <= len; i++) {
		c[i] = a[i] + b[i];
		c[i+1] += c[i] / 10;
		c[i] %= 10;
	}
	if(c[len] != 0) len++;
	return len;
}
