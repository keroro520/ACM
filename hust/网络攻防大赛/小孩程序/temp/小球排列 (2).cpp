#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int shu[3];
int main()
{
  freopen("ball_in.txt","r",stdin);freopen("ball_out.txt","w",stdout);
	int t,i;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d %d %d",&shu[0],&shu[1],&shu[2]);
		sort(shu,shu+3);
		if(shu[0]!=0){
			for(i=2;i>=0;--i)
				shu[i]-=shu[0];
			if(shu[0]==shu[1] && shu[0]==shu[2])
				printf("6\n");
			else if(shu[0]==shu[1] && shu[1]+1==shu[2])
				printf("2\n");
			else if(shu[0]+1==shu[1] && shu[1]==shu[2])
				printf("2\n");
			else
				printf("0\n");
		}
		else{
			if(shu[0]==shu[1] && shu[1]+1==shu[2])
				printf("1\n");
			else if(shu[0]+1==shu[1] && shu[1]==shu[2])
				printf("1\n");
			else
				printf("0\n");
		}
	}
	return 0;
}
