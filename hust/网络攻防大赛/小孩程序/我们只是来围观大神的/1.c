#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void main()
{
  freopen("ball_in.txt","r",stdin); freopen("output.txt","w",stdout);
    int a[3];
    int b[100]={0};
	int n;
	int i,j;
	int cha1,cha2,cha3;
	scanf("%d",&n);

	for(i=0;i<n;i++)

		{
		scanf("%d %d %d",&a[0],&a[1],&a[2]);
	     cha1=labs(a[0]-a[1]);
         cha2=labs(a[1]-a[2]);
         cha3=labs(a[0]-a[2]);
    if(a[0]>0 && a[1]>0 && a[2]>0)
	{
  	   if(cha1>=2||cha2>=2||cha3>=2)
	        b[i]=0;
       else if(cha1==1||cha2==1||cha3==1)
	        b[i]=2;
       else if(cha1==cha2==cha3==0)
	        b[i]=6;

	}



	else if(a[0]==0)
	{
  	   if(a[1]==0)
	   {
  		if(a[2]==1)
  		   b[i]=1;
  		else
  		   b[i]=0;
	   }
  	else if(a[2]==0)
  	{
  		if(a[1]==1)
  		   b[i]=1;
  		else
  		   b[i]=0;
  	}

  }
    else if(a[1]==0)
	{
	    if(a[2]==0)
		{
		  if(a[0]==1)
		    b[i]=1;
		  else
		    b[i]=0;
		}
	    else if(a[0]==1&&a[2]==1)
	        b[i]=2;
	    else if(cha3>=1)
	        b[i]=0;

	}
    else if(a[2]==0)
	{
  	    if(a[0]==1&&a[1]==1)
  	       b[i]=2;
  	    else
  	       b[i]=0;
  	}


		}

	//printf("%d %d %d\n",a[0],a[1],a[2]);
	//printf("%d %d %d\n",cha1,cha2,cha3);

for(j=0;j<n;j++)
	{
		printf("%d\n",b[j]);
	}

system("pause");
}
