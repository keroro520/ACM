/*
	数学  二分  
	题意：给K，输出满足x^z + y^z + x*y*z =  K的(x,y,z)数目，0 < x < y, 1 < z

	思路：枚举z (2 < z < 31)
		  枚举x，x的上界二分算出来
		  二分算出y，再判定

		  其实二分就是对于已知z，K，二分算出x^z = K的x
*/
#include <string.h>
#include <stdio.h>
typedef		long long 		ll;
ll Pow[50005][33];

void get_pow()
{
	ll inf = (1LL << 31);
	memset(Pow, 128, sizeof(Pow));
	for(int i = 1; i <= 50000; i++) {
		Pow[i][0] = 1, Pow[i][1] = i;
		for(int j = 2; j <= 31; j++) {
			Pow[i][j] = Pow[i][j-1] * i;
			if(Pow[i][j] >= inf || Pow[i][j] <= 0) {			//TODO
				memset(&Pow[i][j], 128, sizeof(ll));
				break;
			}
		}
	}
}
int calc_x(int K, int z)			//x^z <= K	//xmax
{
	ll l = 1, r = 50000, ans = 0, mid;
	while(l <= r) {
		mid = (l + r) >> 1;
		if(Pow[mid][z] <= 0 || Pow[mid][z] > K) r = mid - 1;
		else ans = mid, l = mid + 1;
	}
	//printf("%d  %d  %d\n", ans, z, K);
	return (int)ans;
}
int calc_y(int K, int x, int z)
{
	ll l = x+1, r = 50000, ans = 0, mid, tmp = x*z;
	while(l <= r) {
		mid = (l + r) >> 1;
		ll tmp2 = Pow[mid][z] + tmp*mid;
		if(Pow[mid][z] <= 0 || tmp*mid <= 0 || tmp2 <= 0 || tmp2 > K) r = mid - 1;		//TODO
		else ans = mid, l = mid + 1;
	}

	//if(K == 1073741884) printf("%d %d %d %d  %d\n", x, ans, z, tmp, Pow[ans][z] + tmp*ans);
	return (int)ans;
}
int main()
{
	int K;
	get_pow();
	while(scanf("%d", &K), K) {
		int ans = 0;
		for(int z = 2; z <= 31; z++) {
			int oo = calc_x(K, z);
			for(int x = 1; x <= oo; x++) {
				int y = calc_y(K - Pow[x][z], x, z);
	//if(x == 1) printf("%d %d %d %d\n", x, y, z, oo);
				if(y > x && x*y*z > 0 && Pow[y][z] > 0 && Pow[x][z] + Pow[y][z] + x * y * z == K) {		//TODO
					ans++;
					//printf("%d %d %d\n", x, y, z);
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
