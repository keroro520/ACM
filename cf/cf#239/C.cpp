#include <math.h>
#include <stdio.h>
#include <vector>
using namespace std;;
typedef		pair<int,int>		Pii;
bool ok[10005];
vector<Pii> fac[10005];
void init()
{
	for(int i = 1; i <= 1000; i++)
		for(int j = i; j <= 1000; j++) {
			int c = (int)sqrt(1.0*i*i+j*j);
			if(c <= 10000 && c*c == i*i+j*j) {
				int t = (int) c;
				//if(ok[t]) printf("%d   %d %d | %d %d\n", t, i,j,  fac[t][0].first, fac[t][0].second);
				ok[t] = true;
				fac[t].push_back( Pii(i,j) );
				fac[t].push_back( Pii(j,i) );
			}
		}
}
int _dist(int a, int b, int c, int d)
{
	return (a-c)*(a-c) + (b-d)*(b-d);
}
bool check(int len1, int len2, int a, int b, int c, int d)
{
	//printf("! %d %d %d %d   %lf\n", a, b, c, d, _dist(a,b,c,d));
	return _dist(a,b, c,d)  == len1*len1+len2*len2 && b != d && a != c;		//TODO
}
void solve(int a, int b)
{
	for(vector<Pii> :: iterator it1 = fac[a].begin(); it1 != fac[a].end(); it1++)
		for(vector<Pii> :: iterator it2 = fac[b].begin(); it2 != fac[b].end(); it2++)
			if(check(a, b, it1->first, it1->second, -it2->second, it2->first)) {
				puts("YES");
				printf("0 0\n");
				printf("%d %d\n", it1->first, it1->second);
				printf("%d %d\n", -it2->second, it2->first);
				return ;
			}
	printf("NO\n");
}
int main()
{
	init();
	int a, b;
	scanf("%d %d", &a, &b);
	if(!ok[a] || !ok[b]) { puts("NO"); return 0; }
	solve(a, b);
	return 0;
}
