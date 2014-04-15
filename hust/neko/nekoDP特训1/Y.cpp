/*
    传纸条 好题

    没写
    抄了一下关键代码
*/
//lightoj 1071


itn dfs(int step, int r1, int r2)
{
    if(step == n + m - 2) return maze[n-1][m-1];
    if(dp[step][r1][r2] != -1) return dp[step][r1][r2];
    int c1 = step - r1, c2 = step - r2;
    if(c1 < m && c2 < m) {
        int ans = dfs(step+1, r1, r2);
        if(r1 + 1 < n) ans = max(ans, dfs(step+1, r1+1, r2));
        if(r2 + 1 < n) ans = max(ans, dfs(step+1, r1, r2+1));
        if(r1 + 1 < n && r2 + 1 < n) ans = max(ans, dfs(step+1, r1+1, r2+1));
        if(ans != -1) {
            ans += maze[r1][c1];
            if(r1 != r2) ans += maze[r2][c2];
            return dp[step][r1][r2] = ans;
        }
    }
    return -1;
}
