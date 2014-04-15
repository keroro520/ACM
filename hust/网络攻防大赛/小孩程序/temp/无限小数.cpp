#include <string.h>
#include <iostream>
#include <cstdio>
using namespace std;
int shu[150001];
int wei[150001];
int result[150000];
int main()
{
  freopen("in_7.txt","r",stdin);
	int n,k,j,i,t=1;
	while(~scanf("%d %d",&n,&k))
	{
		int max=-1,geshu;
		memset(result,0,sizeof(result));
		for(i=0;i<n;++i)
		{
			scanf("%1d",&shu[i]);
			if(max<=shu[i])
			{
				if(max<shu[i])
					geshu=0;
				wei[geshu++]=i;
				max=shu[i];
			}
		}
		for(i=0;i<geshu;++i)
		{
			bool flag=false;
			int b=2;
			result[0]=max;
			for(j=1;j<n;++j)
			{
				int a=(wei[i]%n+j*(k%n))%n;
				b%=n;
				if(shu[a]>result[j])
					flag=true;
				if(shu[a]==result[j])
					continue;
				if(flag==true)
				{
					result[j]=shu[a];
					continue;
				}
				break;
			}
		}
		printf("Test #%d\n",t++);
		for(i=0;i<n;++i)
			printf("%d",result[i]);
		printf("\n");
	}
	return 0;
}

