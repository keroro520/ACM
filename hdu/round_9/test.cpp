#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
#define		MAXN	100005
int rec[1000];
char s[MAXN];
void init()
{
	memset(rec, 0, sizeof(rec));
}
int  calc(int tmp)
{
	int sum = 0;
	if(!tmp) return 1;
	while(tmp) {
		sum ++;
		tmp /= 10;
	}
	return sum;
}
int main()
{
	int n, l, r;
	while(scanf("%s", s) != EOF) {
		scanf("%d", &n);
		init();
		long long sum1 = 0, sum2 = 0;
		for(int i = 0; i < n; i++) {
			scanf("%d%d", &l, &r);
			int tmp = rec[s[l]];
			sum1 += r - l + 1;
			sum2 += r - l - tmp + calc(tmp) + 2;
			rec[s[l]] = max(rec[s[l]], r - l);
			printf("#  %d\n", tmp);
		//printf("%lld %lld\n", sum1, sum2);
		}
		printf("%lld %lld\n", sum1, sum2);
	}
	return 0;
}
