#include<stdio.h>
 typedef struct GYG
 {
	 int L;
	 int R;
	 int sum;
 } GYG;
int main()
{
	int  num,i,j;
	int total=0;
	scanf("%d",&num);
	GYG  *p= new GYG[num];
	for( i=0;i<num;i++)
	{
		scanf("%d%d",&p[i].L,&p[i].R);
		p[i].sum=0;
	}
	for(i=0;i<num;i++)
		for(j=i+1;j<num;j++)
		{
			if((p[j].R>p[i].R)&&(p[j].L<p[i].L))
		{
			p[i].sum++;  
		}
			else
			{
				if((p[j].R<p[i].R)&&(p[j].L>p[i].L))
					p[j].sum++;
			}
		}
			for(i=0;i<num;i++)
				if(p[i].sum>0)
					total++;
				printf("%d\n",total);
				return 0;
}
