

int main()
{
  scanf("%d", &cases);
  while(cases--) {
    scanf("%d%d", &n, &query);
    idx = 0;
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]), b[idx++] = Brick(a[i], i);
    for(int i = 1; i <= query; i++) {
      scanf("%d%d%d", &que[i].l, &que[i].r, &que[i].x); que[i].id = i;
      b[idx++] = Brick(que[i].x, i+n);
    }
    sort(b, b+idx);
    int tmp = 1;
    if(b[0].id <= n) a[ b[0].id ] = 1; else que[ b[0].id-n ].x = 1;
    for(int i = 1; i < idx; i++) {
      if(b[i].x != b[i-1].x) tmp++;
      b[i].id <= n ? a[ b[i].id ] = tmp : que[ b[i].id-n ].x = tmp;
    }

}
