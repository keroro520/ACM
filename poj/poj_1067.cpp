/*
	威尔夫博弈  简单
*/
#define		gold_cut		((sqrt((double)5.0) + 1) / 2)
#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

bool judge(long long A, long long B)
{
	double k = B - A;
	return (long long)(k * gold_cut)  != A;
}
int main()
{
	long long A, B;
	while(scanf("%I64d%I64d", &A, &B) != EOF) {
		puts(judge(min(A, B), max(A, B)) ? "1" : "0");
	}
	return 0;
}
