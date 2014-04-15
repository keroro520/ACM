#include<iostream>
#include<cmath>
#include <stdio.h>
using namespace std;
int main()				//只需关注数列A的前N个即可，以后皆为循环
{
  freopen("in_3.txt","r",stdin);
	int n,k;
	cin>>n>>k; cout << n << " " << k << endl;
	int i,j,d[150000+1000]={0};
	int temp=0,temp2=0;
	for(i=0;i<n;i++)
		scanf("%1d", &d[i]);
	for(i=1;i<=n;i++)
	{
		temp=0;
		for(j=0;j<n;j++)
		{
		//	int aa=pow(2,j-1);
			temp=d[(i+j*2*k)%3]+temp*10;
		}
		if(temp2<temp)
			temp2=temp;
	}
	int ans[150000+1000];
	for(i=1;i<=n;i++)
	{
		ans[n-i]=temp2%10;
		temp2/=10;
	}
	for(i=0;i<n;i++)
	cout<<ans[i];
	cout<<endl;
return 0;
}
