#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
struct nvshen      //定义结构体记录每个男生左右两边的女生
{
	int left,right;
}shu[1601];
bool cmp(struct nvshen a,struct nvshen b)
{
	return a.left>b.left;
}
int main()
{
	int n,i,j,sum=0;
	scanf("%d",&n);
	for(i=0;i<n;++i)       //输入女生信息
		scanf("%d %d",&shu[i].left,&shu[i].right);
	sort(shu,shu+n,cmp);   //对左边的女生降序排序
	for(i=0;i<n-1;++i)       //寻找每个男生左边的女生比自己差，但右边女生比自己好的，如果有sum加1
	{
		for(j=i+1;j<n;++j)
		{
			if(shu[i].right<shu[j].right)
			{
				++sum;       //记录纠结的男生个数
				break;
			}
		}
	}
	printf("%d",sum);
	return 0;
}