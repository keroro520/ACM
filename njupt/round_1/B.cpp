
long long ans = 
int main()
{
    scanf("%d%d", &n, &c);
    for(int i = 1; i <= n; i++) cin >> a[i].pos >> a[i].w;
    vis[c] = true;
    dfs(c, 1, 0);

    cout << ans << endl;
    return 0;
}
void dfs(int pos, int num, int second, int sum)
{
    if(num == n) {
        if(ans > sum) ans = sum;
        return ;
    }
    if(pos - 1 > 0 && visit[pos-1] == false) {
        visit[pos-1] = true;
        dfs(pos-1, num+1, second+a[pos].pos-a[pos-1].pos, sum+a[pos-1].w*(a[pos].pos-a[pos-1].pos+second));
        visit[pos-1] = false;
    } 
    if(pos + 1 <= n && visit[pos+1] == false) {
        visit[pos+1] = true;
        dfs(pos+1, num+1, second+a[pos+1]-sum+a[pos+1].pos-a[pos].pos);
        visit[pos+1] = false;
    }
}
