#include <algorithm>
#include <stdio.h>
using namespace std;
#define			MID(l,r)		(((l) + (r)) >> 1)

typedef		long long LL;
struct Status {
	LL a, b, c;
	int dep;
	Status() { dep = 0; }
	void sort() {
		if(a > b) swap(a, b);
		if(b > c) swap(b, c);
		if(a > b) swap(a, b);
	}
	friend bool operator == (const Status & S, const Status & T) {
		return S.a == T.a && S.b == T.b && S.c == T.c; 
	}
} ;
Status Root(Status &x)
{
	Status S = x;
	int p = S.c - S.b, q = S.b - S.a, r;
	while(p != q) {
		if(p > q) {
			r = (p-1)/q;
			S.b += r * q, S.a += r * q;
		} else {
			r = (q-1)/p;
			S.c -= r * p, S.b -= r * p;
		}
		S.dep += r;
		S.sort();
		p = S.c - S.b, q = S.b - S.a;
	}
	x.dep = S.dep;
	return S;
}
Status up(Status S, int step)
{
	int p = S.c - S.b, q = S.b - S.a, r;
	while(step) {
		if(p > q) {
			r = (p-1)/q;
			r = min(r, step);
			S.a += r * q, S.b += r * q;
		} else {
			r = (q-1)/p;
			r = min(r, step);
			S.c -= r * q, S.b -= r * q;
		}
		step -= r;
		S.sort();
		p = S.c - S.b, q = S.b - S.a;
	}
	return S;
}
void out(Status s)
{
	printf("(%lld  %lld  %lld  %lld)\n", s.a,s.b,s.c,s.dep);
}
int solve(Status S, Status T)
{
	int sum = abs(S.dep - T.dep);
	out(S), out(T);
	if(S.dep > T.dep) S = up(S, sum);
	else T = up(T, sum);
	int l = 0, r = max(S.dep, T.dep), mid, ans;
	while(l <= r) {
		mid = MID(l, r);
		if(up(S, mid) == up(T, mid)) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	return sum + mid * 2;
}
int main()
{
	Status S, T;
	while(scanf("%lld%lld%lld", &S.a, &S.b, &S.c) != EOF) {
		scanf("%lld%lld%lld", &T.a, &T.b, &T.c);
		S.sort(), T.sort();
		if(!(Root(S) == Root(T))) {
			puts("NO");
			continue;
		} else puts("YES");
		printf("%d\n", solve(S, T));
	}
	return 0;
}
