#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
struct nvshen      //����ṹ���¼ÿ�������������ߵ�Ů��
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
	for(i=0;i<n;++i)       //����Ů����Ϣ
		scanf("%d %d",&shu[i].left,&shu[i].right);
	sort(shu,shu+n,cmp);   //����ߵ�Ů����������
	for(i=0;i<n-1;++i)       //Ѱ��ÿ��������ߵ�Ů�����Լ�����ұ�Ů�����Լ��õģ������sum��1
	{
		for(j=i+1;j<n;++j)
		{
			if(shu[i].right<shu[j].right)
			{
				++sum;       //��¼�������������
				break;
			}
		}
	}
	printf("%d",sum);
	return 0;
}