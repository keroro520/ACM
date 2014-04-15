#include <cstring>
#include <iostream>
#include <cstdio>
using namespace std;
int shu[150001];      //用于存储整数数列D
int wei[150001];      //用于存储D数列里面最大值的位置
int result[150000];  //用于存储最有结果
int main()
{
  freopen("in_6.txt","r",stdin);
	int n,k,j,i,t=1;
	while(~scanf("%d %d",&n,&k))    //输入N和K
	{
		int max=-1,geshu;
		memset(result,0,sizeof(result));
		for(i=0;i<n;++i)          //输入D数列，找出D中最大值，并记录位置
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
		for(i=0;i<geshu;++i)      //遍历每一个最大值，找出最优结果
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
