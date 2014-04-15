//n m要手工调，囧 =_= 要是在linux下就方便了=_=
/*
  1 1
  2 2
  4 4
  6 6
  11 8
*/
#include <stdio.h>
int n ,m;     //在windows上要手工改，蛋疼
int a[10300][10300];
bool boo[(1 << 25)];
int ones(int x)
{
  if(x == 0) return 0;
  x = x & (x-1);
  if(x == 0) return 1;
  return -1;
}
bool check(int x, int y)
{
  int z = ( x ^ y );
  return ones(z) == 1;
}
int main(int argv, char **arg)
{
  scanf("%d %d", &n, &m);
  freopen("1_out.txt","r",stdin);
  n = (1 << n), m = (1 << m);
  for(int i = 0; i < n; i++)
    for(int j = 0; j < m; j++) scanf("%d", &a[i][j]), boo[a[i][j]] = true;
  bool flag = true;
  for(int i = 0; i < n*m && flag; i++) if(!boo[i]) flag = false, printf("! %d\n", i);

  for(int i = 0; i < n && flag; i++)
    for(int j = 0; j < m && flag; j++) {
      if(!check(a[i][j], a[i][(j+1)%m])) flag = false, printf("! %d %d\n", i+1, j+1);
      if(!check(a[i][j], a[(i+1)%n][j])) flag = false, printf("! %d %d\n", i+1, j+1);
    }
  puts(flag ? "Accepted" : "Wrong Answer");
  return 0;
}
