#define     debug   printf("!\n")

#include<iostream>  
#include<cstdio>  
#include<cstring>  
  
using namespace std;  
const int N=1000005;  
int ans[N],f[30];  
  
int getlen(int n)//得到十进制数n化为二进制数后的长度  
{  
    int len=0;  
    while(n)  
    {  
        len++;  
        n/=2;  
    }  
    return len;  
}  
  
int main()  
{  
    int n,i,j;  
    f[0]=1;  
    for(i=1;i<30;i++)  
        f[i]=f[i-1]*2;  
    while(~scanf("%d",&n))  
    {  
        memset(ans,-1,sizeof(int)*(n+1));  
        for(i=n;i>=0;i--)  
        {  
            if(ans[i]!=-1)  
                continue;  
            j=f[getlen(i)]-1-i;//j与i互补  
            if(i == 0) debug, printf("! %d  %d  %d ! \n", :i, j);
            ans[i]=j;  
            ans[j]=i;  
        }  
        printf("%lld\n",(n+1)*n);  
        for(i=0;i<n;i++)  
            printf("%d ",ans[i]);  
        printf("%d\n",ans[n]);  
    }  
    return 0;  
}  
