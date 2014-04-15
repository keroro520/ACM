#include<iostream>
#include <stdio.h>
using namespace std;
int main()
{freopen("ball_in.txt","r",stdin);freopen("ball_out.txt","w",stdout);
	int T;
	cin>>T;
	while(T--)
	{//printf("!!%d  ", T);
		int R,B,G;
		cin>>R>>B>>G;
		if( (R!=B) && (R!=G) && (B!=G) )  //三个数不等，即有两个数至少相差2，不可能组成该排列
			cout<<"0"<<endl;
		else if( (R==B)&&(B==G) )			//三个数相等，既有3*2=6种排列
				cout<<"6"<<endl;
		else if( (R==B)&&((R-G)==1) || (R==G)&&((R-B)==1) || (G==B)&&((G-R)==1) ) //两个相等 大于第三个数
			cout<<"2"<<endl;
		else if( (R==B)&&((R-G)==-1) || (R==G)&&((R-B)==-1) || (G==B)&&((G-R)==-1) ) //两个相等 小于第三个数
			cout<<"1"<<endl;
    else puts("-1");
	}
	return 0;
}
