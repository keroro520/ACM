/*

    hdu 4390
    
    等待note
*/
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
using namespace std;
#define     MAXN    1000
#define     MOD     1000000007
vector<int> primes;
vector<long long> num;
long long C[MAXN][MAXN];
int n;

void init()
{
    for(int i = 1; i < MAXN; i++) {
        C[i][0] = C[i][i] = 1;
        for(int j = 1; j < i; j++) 
            C[i][j] = (C[i-1][j] + C[i-1][j-1]) % MOD;
    }
}
int f(int n, int m) { return C[n+m-1][n-1]; }

void divide(int x) {
    int sqrt_tmp = int(sqrt(x));
    for(int i = 2; x != 1 && i <= x; i++) if(x % i == 0)
        while(x % i == 0) {
            primes.push_back(i); 
            x /= i;
        }
}
long long solve() {
    long long ans = 1;
    for(vector<long long > :: iterator it = num.begin(); it != num.end(); it++)
        ans = (ans * f(n, *it)) % MOD;
    for(int i = 1; i <= n; i++) {
        long long tmp = 1;
        tmp = C[n][i] % MOD;    //从n个盒子里选出i个空出来
        for(long long Size = num.size(), j = 0; j < Size; j++) 
            tmp = (tmp * f(n-i, num[j])) % MOD;

        if(i & 1) ans -= tmp;
        else ans += tmp;
        ans = (ans%MOD + MOD) % MOD;
    }
    return ans;
}

int main()
{
    int x;
    init();
    while(scanf("%d", &n) != EOF) {
        
        num.clear();
        primes.clear();
        for(int i = 0; i < n;i++) {
            scanf("%d", &x);
            divide(x);
        }

        if(primes.size() == 0) {
            printf("0\n");
            continue;
        }
        sort(primes.begin(), primes.end());
        int sum = 0;
        int top = 0;
        num.push_back(1);

        for(vector<int> :: iterator it = primes.begin()+1; it != primes.end(); it++) 
            if(*it == *(it-1)) num[top]++;
            else {
                num.push_back(1);
                top++;
            }
        printf("%I64d\n", solve());
    }
    return 0;
}





















