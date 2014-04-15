#include<iostream>
using namespace std;
int L[2000],R[2000],N;
int main()
{
    cin>>N;
    int i,j;
    for(i=0;i<N;i++)
        cin>>L[i]>>R[i];
    int ans=0;
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
        {
            if(L[j]<L[i]&&R[i]<R[j])
                ans++;
        }
    cout<<ans/2<<endl;
    return 0;
}