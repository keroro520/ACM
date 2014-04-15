#include "data.h"
void SearchPath(int *prev,int v, int u)
{

    int que[N];
    int tot = 1;
    que[tot] = u;
    tot++;
    int tmp = prev[u];
    while(tmp != v)
    {
        que[tot] = tmp;
        tot++;
        tmp = prev[tmp];
    }
    que[tot] = v;
    for(int i=tot; i>=1; --i)
    if(i != 1)
        printf("[%d] ---$%d--->",que[i], cost[que[i]][que[i-1]]);
    else
        printf("[%d] \n",que[i]);

}


void PrintCity(char s[])
{

}
void GetData(int & a,int& b)
{

printf("请输入起始城市编号：\n");
scanf("%d" ,&a);
printf("请输入目的城市编号：\n");
scanf("%d" ,&b);
printf("\n");

if(a==b||a<0||a>N||b<0||b>N)
    {
    printf("输入错误！\n");
    }
else 
{
    printf("正在计算最便宜路径.......\n\n");


    return;
}
}
