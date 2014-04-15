#include <iostream>
#include <cstdio>
#include <string.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <map>
#include <ctype.h>
#include <time.h>



#define abs(x) ((x)>=0?(x):-(x))
#define i64 long long
#define u32 unsigned int
#define u64 unsigned long long
#define clr(x,y) memset(x,y,sizeof(x))
#define CLR(x) x.clear()
#define ph(x) push(x)
#define pb(x) push_back(x)
#define Len(x) x.length()
#define SZ(x) x.size()
#define PI acos(-1.0)
#define sqr(x) ((x)*(x))
#define MP(x,y) make_pair(x,y)
#define EPS 1e-10


#define FOR0(i,x) for(i=0;i<x;i++)
#define FOR1(i,x) for(i=1;i<=x;i++)
#define FOR(i,a,b) for(i=a;i<=b;i++)
#define FORL0(i,a) for(i=a;i>=0;i--)
#define FORL1(i,a) for(i=a;i>=1;i--)
#define FORL(i,a,b)for(i=a;i>=b;i--)


#define rush() int CC;for(scanf("%d",&CC);CC--;)
#define Rush(n)  while(scanf("%d",&n)!=-1)
using namespace std;


void RD(int &x){scanf("%d",&x);}
void RD(i64 &x){scanf("%I64d",&x);}
void RD(u64 &x){scanf("%I64u",&x);}
void RD(u32 &x){scanf("%u",&x);}
void RD(double &x){scanf("%lf",&x);}
void RD(int &x,int &y){scanf("%d%d",&x,&y);}
void RD(u32 &x,u32 &y){scanf("%u%u",&x,&y);}
void RD(double &x,double &y){scanf("%lf%lf",&x,&y);}
void RD(double &x,double &y,double &z){scanf("%lf%lf%lf",&x,&y,&z);}
void RD(int &x,int &y,int &z){scanf("%d%d%d",&x,&y,&z);}
void RD(u32 &x,u32 &y,u32 &z){scanf("%u%u%u",&x,&y,&z);}
void RD(char &x){x=getchar();}
void RD(char *s){scanf("%s",s);}
void RD(string &s){cin>>s;}


void PR(int x) {printf("%d\n",x);}
void PR(int x,int y) {printf("%d %d\n",x,y);}
void PR(i64 x) {printf("%I64d\n",x);}
void PR(u32 x) {printf("%u\n",x);}
void PR(double x) {printf("%.10lf\n",x);}
void PR(double x,double y) {printf("%.5lf %.5lf\n",x,y);}
void PR(char x) {printf("%c\n",x);}
void PR(char *x) {printf("%s\n",x);}
void PR(string x) {cout<<x<<endl;}


void upMin(int &x,int y) {if(x>y) x=y;}
void upMin(i64 &x,i64 y) {if(x>y) x=y;}
void upMin(double &x,double y) {if(x>y) x=y;}
void upMax(int &x,int y) {if(x<y) x=y;}
void upMax(i64 &x,i64 y) {if(x<y) x=y;}
void upMax(double &x,double y) {if(x<y) x=y;}


const i64 inf=((i64)1)<<60;
const double dinf=1e10;
const int INF=100000000;
const int N=5005;


struct node
{
    int v,L,R,next;
};


node edges[N*10];
int head[N],e;

void add(int u,int v,int L,int R)
{
    edges[e].v=v;
    edges[e].L=L;
    edges[e].R=R;
    edges[e].next=head[u];
    head[u]=e++;
}

int n,m;

struct Node
{
    vector<int> L,R;

    int insert(int l,int r)
    {
        int i;
        FOR0(i,SZ(L))
        {
            int ll=L[i],rr=R[i];
            if(ll<=l&&rr>=r) return 0;
        }
        L.pb(l);
        R.pb(r);
        return 1;
    }
};

Node f[N];
queue<int> Q;


int main()
{
    Rush(n)
    {
        RD(m);
        clr(head,-1); e=0;
        int u,v,L,R,i;
        FOR1(i,m)
        {
            RD(u,v);
            RD(L,R);
            add(u,v,L,R);
            add(v,u,L,R);
        }
        FOR1(i,n)
        {
            f[i].L.clear();
            f[i].R.clear();
        }
        f[1].insert(1,1000000);
        Q.push(1);
        int inq[N]={0};
        while(!Q.empty())
        {
            int u=Q.front();
            Q.pop();

            if(u==n) continue;
            inq[u]=0;
            int i,v;
            for(i=head[u];i!=-1;i=edges[i].next)
            {
                int v=edges[i].v;
                int L=edges[i].L;
                int R=edges[i].R;
                int j,flag=0;
                FOR0(j,SZ(f[u].L))
                {
                    int ll=f[u].L[j];
                    int rr=f[u].R[j];
                    upMax(ll,L);
                    upMin(rr,R);
                    if(ll<=rr) flag|=f[v].insert(ll,rr);
                }
                if(flag&&!inq[v]) Q.push(v),inq[v]=1;
            }
        }
        int ans=0;
        FOR0(i,SZ(f[n].L))
        {
            upMax(ans,f[n].R[i]-f[n].L[i]+1);
        }
        if(ans) PR(ans);
        else puts("Nice work, Dima!");

    }
}
