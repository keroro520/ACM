#include <stdio.h>
typedef	long long ll;
ll K, x, n, m, n1, n2, n12, n21;
ll tmp[1000];

bool solve1()
{
	for(ll i = 0; i <= n/2; i++)
		for(ll j = 0; j <= m/2; j++)
			if(i*n1 + j*n2 == x) {
				for(ll k = 0; k < n-i*2; k++) putchar('O');
				while(i--) printf("AC");
				puts("");
				for(ll k = 0; k < m-j*2; k++) putchar('O');
				while(j--) printf("AC");
				puts("");
				return true;
			}
	return false;
}
bool solve2()
{
	
	for(ll i = 0; i <= (n-1)/2; i++)
		for(ll j = 0; j <= (m-1)/2; j++)
			if(i*n1 + j*n2 + n12 == x) {
				for(ll k = 0; k < (n-1)-i*2; k++) putchar('O');
				while(i--) printf("AC");
				puts("A");
				putchar('C');
				while(j--) printf("AC");
				for(ll k = 0; k < (m-1)-i*2; k++) putchar('O');
				puts("");
				return true;
			}
	return false;
}
bool solve3()
{
	for(ll i = 0; i <= (n-1)/2; i++)
		for(ll j = 0; j <= (m-1)/2; j++)
			if(i*n1 + j*n2 + n21 == x) {
				putchar('C');
				while(i--) printf("AC");
				for(ll k = 0; k < (n-1)-i*2; k++) putchar('O');
				puts("");
				while(j--) printf("AC");
				for(ll k = 0; k < (m-1)-j*2; k++) putchar('O');
				puts("A");
				return true;
			}
	return false;
}
bool solve4()
{
	for(ll i = 0; i <= (n-2)/2; i++)
		for(ll j = 0; j <= (m-2)/2; j++)
			if(i*n1 + j*n2 + n12 + n21 == x) {
				printf("%lld %lld || (%lld %lld  %lld %lld)\n", i, j, n1, n2, n12, n21);
				putchar('C');
				while(i--) printf("AC");
				for(ll k = 0; k < (n-2)-i*2; k++) putchar('O');
				puts("A");
				putchar('C');
				while(j--) printf("AC");
				for(ll k = 0; k < (m-2)-j*2; k++) putchar('O');
				puts("A");
				return true;
			}
	return false;
}
void precalc()
{	
	tmp[1] = 1, tmp[2] = 0, tmp[3] = 1, tmp[4] = 1;
	for(int i = 5; i <= K; i++) tmp[i] = tmp[i-2] + tmp[i-1];
	n1 = tmp[K];
	tmp[1] = 0, tmp[2] = 1;
	for(int i = 3; i <= K; i++) tmp[i] = tmp[i-2] + tmp[i-1];
	n2 = tmp[K];
	tmp[1] = tmp[2] = 0, tmp[3] = 1;
	for(int i = 4; i <= K; i++) tmp[i] = tmp[i-2] + tmp[i-1];
	n12 = tmp[K];
	tmp[1] = tmp[2] = tmp[3] = 0, tmp[4] = 1;
	for(int i = 5; i <= K; i++) tmp[i] = tmp[i-2] + tmp[i-1];
	n21 = tmp[K];
}
int main()
{
	scanf("%lld %lld %lld %lld", &K, &x, &n, &m);
	precalc();
	if(!solve1()) 
		if(!solve2())
			if(!solve3())
				if(!solve4())
					puts("Happy new year!");
	return 0;
}
