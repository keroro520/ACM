#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int shu[3];
int main()
{
  freopen("ball_in.txt","r",stdin);
  freopen("ball_out.txt","w",stdout);
	int t,i;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d %d %d",&shu[0],&shu[1],&shu[2]);      //输入3种球的个数
		sort(shu,shu+3);       //升序排序
		if(shu[0]!=0){    //如果最少的颜色的球的个数不是0
			for(i=2;i>=0;--i)
				shu[i]-=shu[0];
			if(shu[0]==shu[1] && shu[0]==shu[2])     //3种球的个数一样
				printf("6\n");
			else if(shu[0]==shu[1] && shu[1]+1==shu[2])    //两多一少或两少一多，相差1
				printf("2\n");
			else if(shu[0]+1==shu[1] && shu[1]==shu[2])
				printf("2\n");
			else          //无法满足条件
				printf("0\n");
		}
		else{    //如果最少的颜色的球的个数是0
			if(shu[0]==shu[1] && shu[1]+1==shu[2])   //两多一少或两少一多，相差1
				printf("1\n");
			else if(shu[0]+1==shu[1] && shu[1]==shu[2])
				printf("1\n");
			else          //无法满足条件
				printf("0\n");
		}
	}
	return 0;
}
