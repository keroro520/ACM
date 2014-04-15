#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
// 13C
#define DBG 1
#define sz(c) ((int)(c).size())
#define   forl(i, a, b) for(int i = (a); i <  (b); ++i)
#define  forle(i, a, b) for(int i = (a); i <= (b); ++i)
#define   forg(i, a, b) for(int i = (a); i >  (b); --i)
#define  forge(i, a, b) for(int i = (a); i >= (b); --i)
#define  forlc(i, a, b) for(int i##_b = (b), i = (a); i <  i##_b; ++i)
#define forlec(i, a, b) for(int i##_b = (b), i = (a); i <= i##_b; ++i)
#define  forgc(i, a, b) for(int i##_b = (b), i = (a); i >  i##_b; --i)
#define forgec(i, a, b) for(int i##_b = (b), i = (a); i >= i##_b; --i)
#define  forls(i, n, a, b) for(int i = a; i != b; i = n[i])
#define rep(n)  for(int               repp = 0; repp <    (n); ++repp)
#define repc(n) for(int repp_b = (n), repp = 0; repp < repp_b; ++repp)
#define rst(a, v) memset(a, v, sizeof a)
#define cpy(a, b) memcpy(a, b, sizeof a)
#define rstn(a, v, n) memset(a, v, (n)*sizeof((a)[0]))
#define cpyn(a, b, n) memcpy(a, b, (n)*sizeof((a)[0]))
#define ast(b) if(DBG && !(b)) { printf("%d!!|\n", __LINE__); while(1) getchar(); }
#define dout DBG && cout << __LINE__ << ">>| "
#define pr(x) #x"=" << (x) << " | "
#define mk(x) DBG && cout << __LINE__ << "**| "#x << endl
#define pra(arr, a, b) if(DBG) { \
    dout<<#arr"[] | "; \
    forlec(i, a, b) cout<<"["<<i<<"]="<<arr[i]<<" |"<<((i-(a)+1)%13?" ":"\n"); \
    if(((b)-(a)+1)%13) puts(""); \
  }
#define rd(type, x) type x; cin >> x
inline int     rdi() { int d; scanf("%d", &d); return d; }
inline char    rdc() { scanf(" "); return getchar(); }
inline string  rds() { rd(string, s); return s; }
inline double rddb() { double d; scanf("%lf", &d); return d; }
template<class T> inline bool updateMin(T& a, T b) { return a>b? a=b, true: false; }
template<class T> inline bool updateMax(T& a, T b) { return a<b? a=b, true: false; }

const int M = 128, N = 11, inf = 0x3f3f3f3f;

int m, n, x[N], y[N], dp[M][N][N][N][N];

int dfs(int s, int a, int b, int c, int d) {
  int& f = dp[s][a][b][c][d];
  if(~f) return f;
  if(s >= m) return f=0;
  f = inf, updateMin(f, 1+dfs(s, 0, a, b, c));
  forle(i, 1, n) if(x[i]) {
    if(i==a && y[i]>0) continue;
    if(i==b && y[i]>1) continue;
    if(i==c && y[i]>2) continue;
    if(i==d && y[i]>3) continue;
    updateMin(f, 1+dfs(s+x[i], i, a, b, c));
  }
  return f;
}

int main() {
  scanf("%d %d", &m, &n);
  forle(i, 1, n) scanf("%d %d", x+i, y+i);
  rst(dp, -1);
  printf("%d\n", dfs(0, 0, 0, 0, 0));
  return 0;
}
