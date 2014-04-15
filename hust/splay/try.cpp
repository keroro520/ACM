#include<iostream>
#include<cstring>
#include<algorithm>
#include<string>
#include<cstdio>

using namespace std;

#define MAXN 1000000

int next[MAXN];
struct nodes
{
    int ch[2],f;
    int key,size,col,w;
}node[MAXN];

void init()
{
    for(int i=0;i<MAXN-10;i++)
        next[i]=i+1;
}

int newnode(int key)
{
    int p=next[0];
    next[0]=next[p];
    node[p].key=key;
    node[p].ch[0]=node[p].ch[1]=node[p].f=0;
    node[p].size=node[p].w=1;
    return p;
}

void delnode(int p)
{
    next[p]=next[0];
    next[0]=p;
}

struct spt
{
    int root,sizes;

    void clear()
    {
        root=0;
    }
    void rotate(int x,int c)
    {
        int y=node[x].f;
        node[y].ch[!c]=node[x].ch[c];
        if(node[x].ch[c])
                node[node[x].ch[c]].f=y;
        node[x].f=node[y].f;
        if(node[y].f)
        {
            if(node[node[y].f].ch[0]==y)
                node[node[y].f].ch[0]=x;
            else
                node[node[y].f].ch[1]=x;
        }
        node[x].ch[c]=y;
        node[y].f=x;
        push_up(y);
        if(y==root) root=x;
    }
    void splay(int x,int f)
    {
        for(;node[x].f!=f;)
        {
            if(node[node[x].f].f==f)
            {
                if(node[node[x].f].ch[0]==x)
                    rotate(x,1);
                else
                    rotate(x,0);
            }
            else
            {
                int y=node[x].f;
                int z=node[y].f;
                if(node[z].ch[0]==y)
                {
                    if(node[y].ch[0]==x)
                        rotate(y,1),rotate(x,1);
                    else
                        rotate(x,0),rotate(x,1);
                }
                else
                {
                    if(node[y].ch[1]==x)
                        rotate(y,0),rotate(x,0);
                    else
                        rotate(x,1),rotate(x,0);
                }
            }
        }
        push_up(x);
        if(!f) root=x;
    }
    void insert(int key,int rt)
    {
        int p=rt,y=0;
        while(1)
        {
            if(!p)
            {
                p=newnode(key);
                node[p].f=y;
                if(y)
                    node[y].ch[key>node[y].key]=p;
                splay(p,0);
                break;
            }
            y=p;
            if(key==node[p].key)
            {
                node[p].w++;
                splay(p,0);
                break;
            }
            if(key<node[p].key)
                p=node[p].ch[0];
            else
                p=node[p].ch[1];
        }
    }
    int select(int k,int rt)
    {
        int tmp,t=rt;
        for(;;)
        {
            int l=node[node[t].ch[0]].size;
            if(k>l && k<=l+node[t].w) break;
            if(k<=l)
                t=node[t].ch[0];
            else
                k-=(l+node[t].w),t=node[t].ch[1];
        }
        splay(t,0);
        return t;
    }
    void push_up(int rt)
    {
        if(!rt)return;
        int l=node[rt].ch[0];
        int r=node[rt].ch[1];
        int ret=node[rt].w;
        if(l) ret+=node[l].size;
        if(r) ret+=node[r].size;
        node[rt].size=ret;
    }
    int find(int x,int p)
    {
        while(1)
        {
            if(!p)
                return 0;
            else
            {
                if(x==node[p].key)
                {
                    splay(p,0);
                    return p;
                }
                else
                {
                    if(x<node[p].key)
                        p=node[p].ch[0];
                    else
                        p=node[p].ch[1];
                }
            }
        }
        return 0;
    }
    int search(int a,int rt)
    {
        int p=rt,x=0x3FFFFFF;
        while(p)
        {
            if(node[p].key==a) return a;
            if(node[p].key>=a) x=min(x,node[p].key);
            p=node[p].ch[a>node[p].key];
         }
         return x;
    }

    int DelLift(int x)
    {
       int p=find(x,root),q=0;
       if(p)
       {
           if(node[p].ch[0])
              q=node[node[p].ch[0]].size;
           node[p].ch[0]=0;
           push_up(p);
       }
       else
       {
           q=node[root].size;
           root=0;
       }
       return q;
    }
};


void debug(int rt)
{
    if(!rt) return;
    debug(node[rt].ch[0]);
    printf("key:%d  size:%d col:%d\n",node[rt].key,node[rt].size,node[rt].col);
    debug(node[rt].ch[1]);
}


spt s1;

int main()
{
    char q[5];
    int n,m,ans,t,l;
    init();
    while(~scanf("%d%d",&n,&m))
    {
        s1.clear();
        l=m;ans=0;
        for(int i=0;i<n;i++)
        {
            scanf("%s%d",q,&t);
            if(q[0]=='I')
            {
                if(t>=m)
                    s1.insert(t+l-m,s1.root);
            }
            if(q[0]=='S')
            {
                l+=t;
                ans+=s1.DelLift(s1.search(l,s1.root));
            }
            if(q[0]=='A')
                l-=t;
            if(q[0]=='F')
            {
                int p=-1;
                if(t<=node[s1.root].size)
                {
                    s1.select(node[s1.root].size-t+1,s1.root);
                    p=node[s1.root].key;
                    p=p-l+m;
                }
                printf("%d\n",p);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}




