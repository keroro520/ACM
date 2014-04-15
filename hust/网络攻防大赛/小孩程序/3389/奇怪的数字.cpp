#include<iostream>
#include<cmath>
#include <stdio.h>
using namespace std;
#define MAX 10+5
#define hello 10485//76
	int ans[hello][hello]={0};		//存矩阵
#define CHANGE_BIT(x) x=( (x) == true ? false : true)
bool digit[MAX];
int main()						//由于格雷码相邻两数之间只改变一个位元，此题目构造格雷码后放入矩阵，即可
{
  freopen("1_out.txt","w",stdout);

	int gray[hello]={0};				//gray 存放格雷码
	int	flag=0,tp=0;

	int n,m,i,j;
	cin>>n>>m;
	int bits=n+m;

	bool odd = true;
	for( i = 0; i < bits; i++)
	{
		digit[i] = false;
	}
	gray[flag++]=0;

	while(true)
	{
		if(odd)
			CHANGE_BIT(digit[0]);
		else
		{

			for(j = 0; j < bits && digit[j] == false; j++)
				;
			if(j == bits - 1)
				break;
            CHANGE_BIT(digit[j + 1]);
		}
		tp=0;
		for( j = bits - 1; j >= 0; j--)
			{
				if(digit[j])
					tp+=pow(2,j);
			}
		gray[flag++]=tp;
		CHANGE_BIT(odd);
	}
	int ff=0;
	int jj=pow(2,m);
	int	ii=pow(2,n);
	for(j=0;j<jj;j++)
		for(i=0;i<ii;i++)
			if(j%2==0)
				ans[i][j]=gray[ff++];
			else
				ans[ii-1-i][j]=gray[ff++];
	for(i=0;i<ii;i++)
	{
		for(j=0;j<jj;j++)
			cout<<ans[i][j]<<" ";
		cout<<endl;
	}
	return 0;
}
