#include <algorithm>
#include <string.h>
#include <stdio.h>
using namespace std;
#define			inf		999999999
int down[10][10], up[10][10], d[2][5], step[1000][1000];

int  T1(int s, int t)		//x->y
{
	int ans = 0;
	for(int i = s; i <= t; i++) ans += min(  down[ d[0][i] ][ d[1][i] ], up[ d[0][i] ][ d[1][i] ] );
	return ans;
}

inline	int	hash(int x) { return ((x % 10) + 10) % 10; }
int  T2(int s, int t)
{
	int ans = inf, sum = 0;
	int k   = min(down[ d[0][s] ][ d[1][s] ], down[ d[0][t] ][ d[1][t] ]);
	sum += k + min(
					max(up[ hash(d[0][s] - k) ][ d[1][s] ], up[ hash(d[0][t] - k) ][ d[1][t] ]),
					max(down[ hash(d[0][s] - k) ][ d[1][s] ], down[ hash(d[0][t] - k) ][ d[1][t] ]) );
	ans = min(ans, sum);
	
	sum = 0;
	k       = min(up[ d[0][s] ][ d[1][s] ], up[ d[0][t] ][ d[1][t] ]);
	sum += k + min(
					max(down[ hash(k + d[0][s]) ][ d[1][s] ], down[ hash(k + d[0][t]) ][ d[1][t] ]),
					max(up[ hash(k + d[0][s]) ][ d[1][s] ],     up[ hash(k + d[0][t]) ][ d[1][t] ]));
	ans = min(ans, sum);
	return ans;
}
int calc(int x, int y)			//x -> y
{
	int ans = inf, idx = 0;
	int tx = x, ty = y;
	while(idx < 3) { d[0][idx++] = x % 10; x /= 10; }
	idx = 0;
	while(idx < 3) { d[1][idx++] = y % 10; y /= 10; }

	ans = min(ans, T1(0, 2));
	ans = min(ans, min(T1(0, 0) + T2(1, 2), T1(2, 2) + T2(0, 1)));
	{
		int sum = 0;
		int t = up[ d[0][0] ][ d[1][0] ];
		for(int i = 1; i <= 2; i++) d[0][i] = ((d[0][i] + t) % 10 + 10) % 10;
		sum += t + T2(1, 2);
		ans = min(ans, sum);
		for(int i = 1; i <= 2; i++) d[0][i] = ((d[0][i] - t) % 10 + 10) % 10;

		sum = 0;
		t = down[ d[0][0] ][ d[1][0] ];
		for(int i = 1; i <= 2; i++) d[0][i] = ((d[0][i] - t) % 10 + 10) % 10;
		sum += t + T2(1, 2);
		ans = min(ans, sum);
		for(int i = 1; i <= 2; i++) d[0][i] = ((d[0][i] + t) % 10 + 10) % 10;

		sum = 0;
		t = up[ d[0][2] ][ d[1][2] ];
		for(int i = 0; i <= 1; i++) d[0][i] = ((d[0][i] + t) % 10 + 10) % 10;
		sum += t + T2(0, 1);
		ans = min(ans, sum);
		for(int i = 0; i <= 1; i++) d[0][i] = ((d[0][i] - t) % 10 + 10) % 10;

		sum = 0;
		t = down[ d[0][2] ][ d[1][2] ];
		for(int i = 0; i <= 1; i++) d[0][i] = ((d[0][i] - t) % 10 + 10) % 10;
		sum += t + T2(0, 1);
		ans = min(ans, sum);
		for(int i = 0; i <= 1; i++) d[0][i] = ((d[0][i] + t) % 10 + 10) % 10;


		sum = 0;
		t = up[ d[0][1] ][ d[1][1] ];
		for(int i = 0; i <= 2; i += 2) d[0][i] = ((d[0][i] + t) % 10 + 10) % 10;
		sum += t + T1(0, 0) + T1(2,2);
		ans = min(ans, sum);
		for(int i = 0; i <= 2; i += 2) d[0][i] = ((d[0][i] - t) % 10 + 10) % 10;

		sum = 0;
		t = down[ d[0][1] ][ d[1][1] ];
		for(int i = 0; i <= 2; i += 2) d[0][i] = ((d[0][i] - t) % 10 + 10) % 10;
		sum += t + T1(0, 0) + T1(2, 2);
		ans = min(ans, sum);
		for(int i = 0; i <= 2; i += 2) d[0][i] = ((d[0][i] + t) % 10 + 10) % 10;
	}

	return ans;
}
void init()
{
	for(int i = 0; i < 10; i++) for(int j = 0; j < 10; j++) {
		up[i][j] = ((j - i) % 10 + 10 ) % 10;
		down[i][j] = ((i - j) % 10 + 10) % 10;
	}
	for(int i = 0; i < 1000; i++) for(int j = 0; j < 1000; j++) step[i][j] = calc(i,j);
}
char a[1005], b[1005], dp[1005], len;
int main()
{
	init();
	while(scanf("%s %s", a, b) != EOF) {
		len = strlen(a);
		if(len > 0) dp[0] = step[a[0]-'0'][b[0]-'0'];
		if(len > 1) dp[1] = step[(a[1]-'0')*10+a[0]-'0'][(b[1]-'0')*10+b[0]-'0'];
		if(len > 2) dp[2] = step[(a[2]-'0')*100+(a[1]-'0')*10+a[0]-'0'][(b[2]-'0')*100+(b[1]-'0')*10+b[0]-'0'];
		for(int i = 3; i < len; i++) 
			dp[i] = min(dp[i-1] + step[a[i]-'0'][b[i]-'0'],
						min(dp[i-2] + step[(a[i]-'0')*10+a[i-1]-'0'][(b[i]-'0')*10+b[i-1]-'0'],
						    dp[i-3] + step[(a[i]-'0')*100+(a[i-1]-'0')*10+a[i-2]-'0'][(b[i]-'0')*100+(b[i-1]-'0')*10+b[i-2]-'0']));
	
	}
	return 0;
}
