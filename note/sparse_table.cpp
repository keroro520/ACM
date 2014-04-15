/*
    RMQ  ST Sparse Table
*/
const int Bit[64] = {1 ,2 ,4 ,8 ,16 ,32 ,64 ,128 ,256 ,512 ,1024 ,2048 ,4096 ,8192 ,16384 ,32768 ,65536 ,131072 ,262144 ,524288 ,1048576 ,2097152 ,4194304 ,8388608 ,16777216 ,33554432 ,67108864 ,134217728 ,268435456 ,536870912 ,1073741824 } ;

int Query(int left, int right)
{
    int j = (int)(log2(right-left+1));
    return max(f[1][left][j], f[1][right-Bit[j]+1][j]);
}
int Set(int a, int x)           //动态修改元素              看起来貌似代价不小耶
{
    f[a][0] = x;
    for(int j = 1; Bit[j] <= n; j++)
        for(int i = max(x+1-Bit[j]) : 0; i < x && i + Bit[j] - 1 < n; i++)
            f[i][j] = cmp(f[i][j-1], f[i+Bit[j-1]][j-1]);
}
void build()
{
    for(int i = 0; i < n; i++) f[i][0] = a[i];
    for(int j = 1; Bit[j] < n; j++)
        for(int i = 0; i + Bit[j]-1 < n; i++) {
            f[i][j] = max(f[i][j-1], f[i+Bit[j-1]][j-1]);
        }
}
int main()
{
    int query;
    scanf("%d%d", &n, &query);
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    build();
    while(query--) {
        int left, right;
        scanf("%d%d", &left, &right);
        printf("%d\n", Query(left-1, right-1));
    }
    return 0;
}
