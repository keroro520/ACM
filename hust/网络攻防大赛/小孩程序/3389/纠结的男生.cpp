#include<iostream>
using namespace std;
int main()
{
	int l[1600+100]={0},r[1600+100]={0};
	int n;
	cin>>n;
	int i,j;
	int count=0;
	for(i=0;i<n;i++)
		cin>>l[i]>>r[i];
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			if(i!=j)
				if(  (l[i]<l[j]) && (r[i]<r[j])  )
				{
					count++;
					break;
				}
		}
	cout<<count<<endl;
	return 0;
}
