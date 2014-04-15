#include <cstdio>

int n,ans,i,j,a[2000][5];
int main(){
	scanf("%d",&n);
	for (i=1;i<=n;i++)
		scanf("%d%d",&a[i][1],&a[i][2]);
	ans=0;
	for (i=1;i<=n;i++)
	for (j=1;j<=n;j++)
		if ((a[j][1]<a[i][1])&&(a[i][2]<a[j][2])){
			ans++;
			break;
		}
	printf("%d\n",ans);
	return 0;
}