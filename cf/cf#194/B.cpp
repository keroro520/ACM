#include<iostream>
#include<cstdlib>
#include<cstdio>
using namespace std;
int m[11100];
void init()
{
for(int i=0;i<11100;i++)
m[i]=0;
}
int n;
int main()
{
while(scanf("%d",&n)!=EOF)
{
int k=1;
for(int i=1,j=n*n;i<j;i++,j--)
{
if(k==n+1) k=1;
m[i]=k;m[j]=k;k++;
}
for(int i=1;i<=n;i++){
int flag=0;
for(int j=1;j<=n*n;j++)
{
if(m[j]==i)
{
if(flag==0){ cout<<j;flag=1;}
else cout<<" "<<j;
}

}
cout<<endl;

}

}
return 0;

}
