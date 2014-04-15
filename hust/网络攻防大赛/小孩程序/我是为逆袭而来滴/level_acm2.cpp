#include <iostream>
#include <stdio.h>
using namespace std;
int result[100];
int max(int n,int m)
{
	return n>m?n:m;
}
int min(int n,int m)
{
	return n>m?m:n;
}

void judge(int r,int g,int b,int t)
{
	int x=0,y=0,z=0;
	x=max(r,g);
	y=min(r,g);
	if (y<b)
	{
		z=y;
		y=b;
		if (x<y)
		{
			int temp;
			temp =x;
			x=y;
			y=temp;
		}
	}
	else
		z=b;
	if(z==0)
	{
		if(x==1)
			result[t]=1;
		if(x>=2)
			result[t]=0;
	}

	else if (x==y && y==z)
		result[t]=6;
	else if(x==y && y>z)
		result[t]=2;
	else if(x>y &&x==y)
		result[t]=2;
	else
		result[t]=0;
}

int main()
{
  freopen("ball_out.txt","r",stdin);freopen("222.txt","w",stdout);
	int r=0,g=0,b=0;

	int t=0;
	cin>>t;printf("! %d\n", t);
	int i=t;
	while(t--)
	{
		cin>>r>>g>>b;
		judge(r,g,b,t);

	}
	for(int j=0;j<i;j++)
		cout<<result[i-j-1]<<endl;
	return 0;
}
