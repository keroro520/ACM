
include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define N 110
#define INF 10000000
#define pb push_back
#define cl(xx,yy) memset((xx),(yy),sizeof((xx)))
 
struct peo{
	int from,to,cost;
	peo(){}
	peo(int f,int t,int c){
		from = f; to = t; cost = c;
	}
	bool operator < (const peo &temp)const{
		return cost < temp.cost;
	}
};
vector<peo>a[N];
int n,To[N],Cost[N],vote[N],ans[N],p[N];
 
void solve(){
	fill(ans,ans+n+5,INF);
	for(int v = vote[1]; v <= n-1; v++){
		int s = 0;
		for(int i = 2; i <= n; i++)
			if(vote[i] >= v) s += (vote[i]-(v-1));
		if(vote[1] + s > v) continue;
		int sum = 0;
		for(int i = 2; i <= n; i++){
			if(vote[i] <= v-1){ p[i] = 0; continue; }
			p[i] = vote[i]-(v-1);
			for(int k = 0; k < p[i]; k++)
				sum += a[i][k].cost;
		}
		while(vote[1] + s < v){
			int id,Min = INF;
			for(int i = 2; i <= n; i++){
				if(p[i] == a[i].size()) continue;
				if(a[i][p[i]].cost < Min){
					Min = a[i][p[i]].cost; id = i;
				}
			}
			sum += Min; s++; p[id]++;
		}
		ans[v] = sum;
	}
	int res = INF;
	for(int v = vote[1]; v <= n; v++)
		res = min(res,ans[v]);
	printf("%d\n",res);
}
 
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i = 1; i <= n; i++)
			a[i].clear();
		cl(vote,0);
		for(int i = 2; i <= n; i++){
			scanf("%d",&To[i]);
			vote[To[i]]++;
		}
		for(int i = 2; i <= n; i++)
			scanf("%d",&Cost[i]);
		for(int i = 2; i <= n; i++)
			a[To[i]].pb(peo(i,To[i],Cost[i]));
 
		//将1号的票投给现在票最少的人
		int id,temp = INF;
		for(int i = 2; i <= n; i++)
			if(vote[i] < temp) id = i;
		a[id].pb(peo(1,id,INF));
		//将1号的票投给现在票最少的人
 
		for(int i = 1; i <= n; i++)
			sort(a[i].begin(),a[i].end());
 
		solve();
	}
	return 0;
}

