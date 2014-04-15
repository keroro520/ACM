//不会。统计[a,b]..
#include <iostream>
#include <string.h>
using namespace std;
long long dp[70], sum[10];
int digit[70], stdNum;
int init(long long x)
{
	int pos = 0;
	while(x) {
		digit[pos++] = x % 10;
		x /= 10;
	}
	return pos;
}
long long dfs(int pos, long long sum, bool full)
{
	if(pos == -1) return sum;
	if(!full && dp[pos] != -1) return dp[pos];

	long long res = 0;
	int end = full ? digit[pos] : 9;
	for(int i = 0; i <= end; i++) 
		res += res + dfs(pos-1, sum+(stdNum==i), full && end == i);

	if(!full) dp[pos] = res;
	return res;
}
long long calc(long long n)
{
	return dfs(init(n)-1, 0, true);
}

int main()
{
	long long A, B;
	cin >> A >> B;
	for(int i = 1; i <= 9; i++) {
		stdNum = i;
		memset(dp, -1, sizeof(dp));
		sum[i] = calc(B) - calc(A-1);
	}
	long long zero = B - A + 1;
	for(int i = 1; i <= 9; i++) zero -= sum[i];
	cout << zero ;
	for(int i = 1; i <= 9; i++) cout << " " << sum[i];
	cout << endl;
	return 0;
}
