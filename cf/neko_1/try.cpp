#include<iostream>  
#include<cstdio>  
#include<map>  
#include<cstring>  
#include<cmath>  
#include<vector>  
#include<algorithm>  
#include<set>  
#include<string>  
#include<queue>  
#define inf 1600005  
#define M 40  
#define N 100005
#define maxn 300005  
#define eps 1e-12
#define zero(a) fabs(a)<eps  
#define Min(a,b) ((a)<(b)?(a):(b))  
#define Max(a,b) ((a)>(b)?(a):(b))  
#define pb(a) push_back(a)  
#define mp(a,b) make_pair(a,b)  
#define mem(a,b) memset(a,b,sizeof(a))  
#define LL long long  
#define MOD 1000000007
#define lson step<<1
#define rson step<<1|1
#define sqr(a) ((a)*(a))  
#define Key_value ch[ch[root][1]][0]  
#define test puts("OK");  
#define pi acos(-1.0)
#define lowbit(x) ((-(x))&(x))
#pragma comment(linker, "/STACK:1024000000,1024000000")  
using namespace std;
struct Seg_tree{
    int left,right;
    int cnt,lazy;
    int length(){
        return right-left+1;
    }
}L[N*4];
int s[N],e[N],tot;
int n,m;
int ans[N];
vector<int>edge[N],que[N];
void Bulid(int step,int l,int r){
    L[step].left=l;
    L[step].right=r;
    L[step].cnt=L[step].lazy=0;
    if(l==r)
        return ;
    int m=(l+r)>>1;
    Bulid(lson,l,m);
    Bulid(rson,m+1,r);
}
void Push_Up(int step){
    if(L[step].lazy) L[step].cnt=L[step].length();
    else {
        if(L[step].left==L[step].right) L[step].cnt=0;
        else L[step].cnt=L[lson].cnt+L[rson].cnt;
    }
}
void Update(int step,int l,int r,int val){
    if(L[step].left==l&&r==L[step].right){
        L[step].lazy+=val;
        Push_Up(step);
        return ;
    }
    int m=(L[step].left+L[step].right)>>1;
    if(r<=m) Update(lson,l,r,val);
    else if(l>m) Update(rson,l,r,val);
    else{
        Update(lson,l,m,val);
        Update(rson,m+1,r,val);
    }
    Push_Up(step);
}
void dfs(int u,int pre){
    s[u]=++tot;
    for(int i=edge[u].size()-1;i>=0;i--){
        int v=edge[u][i];
        if(v==pre) continue;
        dfs(v,u);
    }
    e[u]=tot;
}
void Init(){
    for(int i=1;i<=n;i++){
        edge[i].clear();
        que[i].clear();
    }
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].pb(v);edge[v].pb(u);
    }
    for(int i=0;i<m;i++){
        int a,b;
        scanf("%d%d",&a,&b);
        que[a].pb(b);que[a].pb(a);
        que[b].pb(a);que[b].pb(b);
    }
    tot=0;
    dfs(1,-1);
    Bulid(1,1,n);
}
void Slove(int u,int pre){
    for(int i=0;i<que[u].size();i++){
        int v=que[u][i];
        Update(1,s[v],e[v],1);
    }
    ans[u]=L[1].cnt;
    if(ans[u])
        ans[u]--;
    for(int i=0;i<edge[u].size();i++){
        int v=edge[u][i];
        if(v==pre) 
            continue;
        Slove(v,u);
    }
    for(int i=0;i<que[u].size();i++){
        int v=que[u][i];
        Update(1,s[v],e[v],-1);
    }
}
void Output(){
    for(int i=1;i<n;i++)
        printf("%d ",ans[i]);
    printf("%d \n",ans[n]);
	for(int i = 1; i <= n; i++) printf("# %d : %d %d\n", i, s[i], e[i]);
}
int main(){
    //freopen("input.txt","r",stdin);
    scanf("%d%d",&n,&m);
        Init();
        Slove(1,-1);
        Output();
    return 0;
}
