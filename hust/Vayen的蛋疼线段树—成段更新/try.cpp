#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

#define LL(x) (x<<1)
#define RR(x) (x<<1|1)
#define MID(a,b) (a+((b-a)>>1))
const int N=100005;

struct node
{
    int lft,rht;
    int mi,mx,sum;
    int flag_set,flag_rev;
    int mid(){return MID(lft,rht);}
    int len(){return rht-lft+1;}
    void init(){ flag_set=flag_rev=mi=mx=sum=0; }
    void fun(int valu)
    {
        if(valu)
        {
            mi=min(valu,valu*len());
            mx=max(valu,valu*len());
            sum=valu*len();
            flag_set=valu; flag_rev=0;
        }
        else
        {
            sum=-sum; 
            swap(mi,mx); mi=-mi; mx=-mx;
            flag_rev^=1;
        }
    }
};

int y[N],n,m;

struct Segtree
{
    node tree[N*4];
    void down(int ind)
    {
        if(tree[ind].flag_set)
        {
            tree[LL(ind)].fun(tree[ind].flag_set);
            tree[RR(ind)].fun(tree[ind].flag_set);
            tree[ind].flag_set=0;
        }
        if(tree[ind].flag_rev)
        {
            tree[LL(ind)].fun(0);
            tree[RR(ind)].fun(0);
            tree[ind].flag_rev=0;
        }
    }
    void up(int ind)
    {
        tree[ind].sum=tree[LL(ind)].sum+tree[RR(ind)].sum;
        tree[ind].mx=max(tree[LL(ind)].mx,tree[LL(ind)].sum+tree[RR(ind)].mx);
        tree[ind].mi=min(tree[LL(ind)].mi,tree[LL(ind)].sum+tree[RR(ind)].mi);
    }
    void build(int lft,int rht,int ind)
    {
        tree[ind].lft=lft;  tree[ind].rht=rht;
        tree[ind].init();
        if(lft==rht) tree[ind].mi=tree[ind].mx=tree[ind].sum=y[lft];
        else 
        {
            int mid=tree[ind].mid();
            build(lft,mid,LL(ind));
            build(mid+1,rht,RR(ind));
            up(ind);
        }
    }
    void updata(int st,int ed,int ind,int valu)
    {
        int lft=tree[ind].lft,rht=tree[ind].rht;
        if(st<=lft&&rht<=ed) tree[ind].fun(valu);
        else 
        {
            down(ind);
            int mid=tree[ind].mid();
            if(st<=mid) updata(st,ed,LL(ind),valu);
            if(ed> mid) updata(st,ed,RR(ind),valu);
            up(ind);
        }
    }
    void query(int st,int ed,int ind,int &mx,int &sum)
    {
        int lft=tree[ind].lft,rht=tree[ind].rht;
        if(st<=lft&&rht<=ed)
        {
            mx=tree[ind].mx;
            sum=tree[ind].sum;
        }
        else 
        {
            down(ind);
            int mid=tree[ind].mid();
            if(ed<=mid) query(st,ed,LL(ind),mx,sum);
            else if(st>mid) query(st,ed,RR(ind),mx,sum);
            else 
            {
                int mx1,mx2,sum1,sum2;
                query(st,ed,LL(ind),mx1,sum1);
                query(st,ed,RR(ind),mx2,sum2);
                mx=max(mx1,sum1+mx2); sum=sum1+sum2;
            }
            up(ind);
        }
    }
}seg;
int main()
{
    int t,t_cnt=0;
    scanf("%d",&t);
    while(t--)
    {
        char str[N];
        scanf("%d%s",&n,str);
        for(int i=0;i<n;i++)
        {
            if(str[i]=='(') y[i]=-1;
            else y[i]=1;
        }
        seg.build(0,n-1,1);

        scanf("%d",&m);

        printf("Case %d:\n",++t_cnt);
        while(m--)
        {
            int a,b;
            char cmd[10],chr[10];
            scanf("%s",cmd);
            if(cmd[0]=='s')
            {
                scanf("%d%d%s",&a,&b,chr);
                seg.updata(a,b,1,(chr[0]=='('?-1:1));
            }
            else if(cmd[0]=='r')
            {
                scanf("%d%d",&a,&b);
                seg.updata(a,b,1,0);
            }
            else
            {
                int mx,sum;
                scanf("%d%d",&a,&b);
                seg.query(a,b,1,mx,sum);
                if(mx<=0&&sum==0) puts("YES");
                else puts("NO");
            }
        }
        puts("");
    }
    return 0;
}

