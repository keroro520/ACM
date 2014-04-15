
ll dfs(int pos,
ll calc(ll x)
{
  int len = 0;
  while(x) {
    digit[len++] = x % 10;
    x /= 10;
  }
  return dfs(len-1, true);
}
int main()
{
  ll A, B;
  cin >> A >> B;
  for(int i = 1; i <= 9; i++) _std = i, f[i] = calc(B) - calc(A-1);
  for(int i = 1; i <= 9; i++) cout << f[i] << (i == 9 ? '\n' : ' ');
  return 0;
}
