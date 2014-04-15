

int main()
{
  scanf("%d%d%d", &n, &K, &P);
  for(int i = 1; i <= K; i++) scanf("%d", &gum[i]);
  for(int i = 1; i <= n; i++) {
    scanf("%d%d", &c, &belong);
    v[ belong ].push_back(c);
  }
  for(int i = 1; i <= K; i++) sort(v[i].begin(), v[i].end());

  for(int i = 1; i <= K; i++) {
    int sum = gum[i];
    for(vector<int> :: it = v[i].begin(); it != v[i].end(); it++) {
      sum += *it;
      vs[i].push_back( pair<int,int>( (int)(it-v[i].begin()) + 1, sum ) );
    }
  }
  memset(f, 127, sizeof(f));
  for(int i = 1; i <= K; i++)
    for(int j = n; j >= 0; j--) {
      f[i][j] = min(f[i][j], f[i-1][j]);
      for(vector< pair<int,int> > :: it = vs[i].begin(); it != vs[i].end(); it++) {
        if(j >= it->first) f[i][j] = min(f[i][j], f[i-1][j-it->first] + it->second);
      }
    }

  int max_tooth = -1, min_cost, gg;
  for(int i = 1; i <= K; i++)
    for(int j = 0; j <= n; j++)
      if(f[i][j] <= P) {
        if(j > max_tooth) max_tooth = j, gg = i, min_cost = f[i][j];
      }

  return 0;
}
