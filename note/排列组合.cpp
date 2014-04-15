



P[0]=1;
for(i=0;i<=100;i++)
{
    if(i>0)P[i]=P[i-1]*i;
    C[i][0]=1;
}
for(i=1;i<=100;i++)
    for(j=1;j<=i;j++)
        C[i][j]=C[i-1][j-1]+C[i-1][j];

P(m,n) = P(m,m) * C(m,n)        貌似是这样的。。
