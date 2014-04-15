/*
	简单题
	一道水题因为搞挫了x0 = A，而写成了x0 = A % M而WA了好久，草，不细心。
*/
#include <string.h>
#include <stdio.h>
int n, start, A, a, b, c, M, K;
int x[10005], pos[1005];
int main()
{
	memset(pos, -1, sizeof pos);
	scanf("%d %d %d %d %d %d", &A, &a, &b, &c, &M, &K);
	n = 0;
	x[n] = A;
	pos[A] = 0;
	while(true) {
		++n;
		x[n] = ((long long)a*x[n-1]*x[n-1] + b*x[n-1] + c) % M;
		if(-1 != pos[x[n]]) { start = pos[x[n]]; break; } else pos[x[n]] = n;
	}

	if(K < n)     printf("%d\n", x[K]);
	else 		  printf("%d\n", x[start + (K-start) % (n-start)]);
	return 0;
}
