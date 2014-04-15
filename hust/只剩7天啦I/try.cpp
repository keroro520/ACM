
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=20005;

char str[maxn];
int n,k;

int main()
{
    int i,j,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);
        scanf("%s",str);
        char temp=str[n-1];
        int ans=1,Max=0;
        j=1;
        for(i=1;i<n;i++)
        {
            if(str[i]!=str[i-1]||j==k)
            {
                ans++;
                Max=max(Max,j);
                j=1;
            }
            else
            {
                j++;
            }
        }
        Max=max(Max,j);
        if(Max<k) printf("-1\n");
        else printf("%d\n",ans);
    }
    return 0;
}
