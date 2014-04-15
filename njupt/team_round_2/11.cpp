#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int qimo,ceping,lunwen;
char ganbu,xibu;
char name[30];
void work(int n);
int main()
{
    //freopen("text.in","r",stdin);
    int n;
	while(scanf("%d", &n) != EOF) {
		work(n);
	}
    return 0;
}
void work(int n)
{
    int max=0;
    char maxn[30];
    long long ans=0;
    for(int i=0;i<n;i++)
    {
        int sum=0;
        cin>>name>>qimo>>ceping>>ganbu>>xibu>>lunwen;
        if(qimo>80 && lunwen>=1)  sum+=8000;
        if(qimo>85 && ceping>80)   sum+=4000;
        if(qimo>90)  sum+=2000;
        if(qimo>85 && xibu=='Y')    sum+=1000;
        if(ceping>80 && ganbu=='Y')  sum+=850;
        if(sum>max)
        {
            max=sum;
            strcpy(maxn,name);
        }
        ans+=sum;
    }
    cout<<maxn<<endl<<max<<endl<<ans<<endl;
}
