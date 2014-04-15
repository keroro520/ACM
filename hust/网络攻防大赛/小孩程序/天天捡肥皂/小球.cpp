#include<stdio.h>
#include<math.h>
int  Result(int a,int b,int c)
{
           if((a==b&&b==c)&&a>0)
			   return 6;
		   if((a==b&&(a-c==1))||(a==c&&(a-b==1))||((b==c)&&(b-a==1)))
			   return 2;
		   if(((a==b&&(a-c==-1))||(a==c&&(a-b==-1))||((b==c)&&(b-a==-1))))
			   return  1;
		   if(fabs(a-b)>1||fabs(a-c)>1||fabs(b-c)>1)
			   return 0;
}
int main()
{
   freopen("ball_in.txt","r",stdin);freopen("ball_out.txt","w",stdout);
	int n;
	scanf("%d",& n);
    int a,b,c,i;
	int j=0;
	int *r=new int[n];
	for( i=0;i<n;i++)
	{   scanf("%d%d%d",&a,&b,&c);
     	r[j++]=Result(a,b,c);
	}
	for( i=0;i<n;i++)
		printf("%d\n",r[i]);
	delete []r;
	return 0;
}



