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
		if( (R!=B) && (R!=G) && (B!=G) )  //���������ȣ������������������2����������ɸ�����
			cout<<"0"<<endl;
		else if( (R==B)&&(B==G) )			//��������ȣ�����3*2=6������
				cout<<"6"<<endl;
		else if( (R==B)&&((R-G)==1) || (R==G)&&((R-B)==1) || (G==B)&&((G-R)==1) ) //������� ���ڵ�������
			cout<<"2"<<endl;
		else if( (R==B)&&((R-G)==-1) || (R==G)&&((R-B)==-1) || (G==B)&&((G-R)==-1) ) //������� С�ڵ�������
			cout<<"1"<<endl;
    else puts("-1");
	}
	return 0;
}
