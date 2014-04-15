
#include<cstdio>
#include<cstring>
#include<cmath>
#include<cctype>
#include<cstdlib>
#include<functional>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<set>
#include<map>
using namespace std;


//// TYPE DEFINE ////
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pdd;

//// DEFINE ////
#define INF 2000000000;
#define MAX 2000000000;
#define loop(i,a,b) for(int i=a;i<b;i++)
#define rep(i,n) loop(i,0,n)
#define rev(i,a,b) for(int i=a;i>=b;i--)
#define pb(a) push_back(a)
#define ppb(a) pop_back(a)
#define vsort(a,func) sort(a.begin(),a.end(),func)
//// GLOBAL VARIABLE ////
struct heap
{
	int t,l,r;
	bool operator <(const heap &o)const{
		if(t!=o.t) return o.t<t;
		else return -1;
	}
};
int n,m,s,f,time,up,cur;
char ans;
int t,l,r,tt,lr,rr;
struct heap tmp;
priority_queue<heap> h;
//// CODE ////
int main(){
	scanf("%d %d %d %d",&n,&m,&s,&f);
	cur=s;
	if(s<f) {ans='R';up=1;}
	else {ans='L';up=-1;}
	rep(i,m){
		scanf("%d %d %d",&t,&l,&r);
		tmp.t=t-1;tmp.l=l;tmp.r=r;
		h.push(tmp);
	}time=1;
	rep(i,h.top().t) {printf("%c",ans);cur+=up;if(cur==f) break;}
	tt=h.top().t;
	lr=h.top().l;
	rr=h.top().r;
	h.pop();
	//printf("111\n");
	while(!h.empty()){
		//printf("%d %d %d\n",cur,lr,rr);
		if((cur<lr||cur>rr)&&(cur+up<lr||cur+up>rr)) {printf("%c",ans);cur+=up;if(cur==f) break;}
		else printf("X");
		if(cur==f) break;
		rep(i,h.top().t-tt-1) {printf("%c",ans);cur+=up;if(cur==f) break;}
		if(cur==f) break;
		tt=h.top().t;
		lr=h.top().l;
		rr=h.top().r;
		h.pop();
	}
	printf("\n");
	return 0;
}
