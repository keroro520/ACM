

int main()
{
    scanf("%d", &cases);
    while(cases--) {
        scanf("%d", &n);
        init();
        for(int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            b[a[i]] ++;
        }
        p = q = 0;
        dfs(0);
    }
}
void init()
{
    memset(num, 0, sizeof(num));
    memset(b,   0, sizeof(b));
}
bool dfs(int index)
{
    for( ; index < n; index++) {
        int x = a[index];
        if(b[x] != 2) break;
        if(used[x] == 0) pos[index] = 0, used[x]++;
        else pos[index] = 1;
        if(num[0][p]
    }

    if(index == n) return true;
    int x = a[index];
    if(used[x] == 0) 
}

