/*
    树状数组    模板题

    下面是去年写，
        昨天刚看树状数组，今天想着道题的时候没思路，因为昨天看的是树状数组用来求和sum[i][j]的应用，然后今天想题的时候就想往那儿靠，
        对照着昨天的模式写了一会儿，发现不对，各个点的下标根本没有什么直接的关系，如果就以下标作为节点来建树不知道怎么查找维护。
        然后实在没想出来就看题解了。果然是经典题，这题不是拿下标来做节点，因为下标没有直接关系，它是拿x坐标当节点。拿x当节点的好处
        是x坐标是连续的，递增的，小x和大x有直接关系，可以直接计算。


    很多人是直接x++来搞，可以避免x == 0的情况。我的第二种写法是特判了x == 0的情况，即Query求和的时候sum初始值为c[0]
*/
#include<stdio.h>
int n,c[32019],         //c[x]就像模板里的sum[x]一样
    ans[32019];
int lowbit(int i)
{
    return i & (-i);
}
int sum(int x)
{
    int sum = 0;
    while(x > 0)
    {
        sum += c[x];
        x -= lowbit(x);
    }
    return sum;
}
void modify(int x)
{
    while(x < 32010)
    {
        c[x]++;
        x += lowbit(x);
    }
}
int main()
{
//  freopen("in.txt","r",stdin);
    int x,i;
    scanf("%d",&n);
    for(i = 0;i < n;i++)
    {
        scanf("%d%*d",&x);
        x++;        //因为树状数组是从1开始的，所以为了避免x=0的情况，就统一加1
        ans[sum(x)]++;
        modify(x);
    }
    for(i = 0;i < n;i++)printf("%d\n",ans[i]);
    return 0;
}
