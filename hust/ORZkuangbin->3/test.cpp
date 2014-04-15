/*
	果断TLE
*/
#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
using namespace std;
#define		Limit		100
typedef		long long		ll;
struct Num {
	ll Int;
	string Rat;
	void out() {
		cout << Int << "." << Rat << endl;
	}
} ;
ll ans_den, ans_mol;

ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a%b); } 
void analize(char *s, Num &a)
{
	int len = strlen(s), i = 0;
	a.Int = 0; a.Rat = "";
	string str = "";
	for( ;   i < len && s[i] != '.'; i++) a.Int = a.Int * 10 + s[i] - '0';
	for(++i; i < len && s[i] != '['; i++) a.Rat += s[i];
	for(++i; i < len && s[i] != ']'; i++) str += s[i];
	int tt = str.length();
	if(tt == 0) return ;
	for(i = 0; i < Limit; i++) a.Rat += str[i%tt];
}
int  cmp(Num &a, ll mol, ll den)
{
	if(a.Int != mol/den) return a.Int < mol/den ? -1 : 1;

	ll rest = mol % den, y;  int tt = a.Rat.length();
	if(tt == 0) return rest == 0 ? 0 : -1;
	for(int i = 0; i < tt; i++) {
		rest *= 10;
		int x = rest / den;
		if(x != a.Rat[i]-'0') return a.Rat[i]-'0' < x ? -1 : 1;
		rest %= den;
		if(rest == y) return 0; else y = rest;
	}
	return tt == Limit ? 0 : 1;
}
bool solve(ll low, ll sum, Num &a, Num & b)
{
	for(ll den = max(1LL, (ll)(sum*1.0/(b.Int+2))); den <= sum*1.0/(a.Int+1); den++) {
		ll mol = sum - den;
		if(cmp(a, mol, den) >= 0) return false;
		if(cmp(b, mol, den) > 0) {
			ans_mol = mol , ans_den = den;
			return true;
		}
	}
	return false;
}

Num a, b;
char A[20], B[20];
ll fuck;
void Fuck(Num &a)
{
	fuck = 1;  int tt = a.Rat.length();
	for(int i = 0; i < tt; i++) {
		if(a.Rat[i] != '0') break;
		fuck *= 10;
	}
}
int main()
{
	int cases, Cas = 0;
	scanf("%d", &cases);
	while(cases--) {
		scanf("%s %s", A, B);
		analize(A, a), analize(B, b);
		Fuck(a);
		printf("%lld\n", fuck);
		ll j = fuck;
		for(ll i = min(a.Int+1,fuck); ; i += j) if(solve(a.Int, i, a, b)) {
			ll d = gcd(ans_mol,ans_den);
			printf("Case %d: %lld/%lld\n", ++Cas, ans_mol/d, ans_den/d);
			break;
		}
	}
	return 0;
}
