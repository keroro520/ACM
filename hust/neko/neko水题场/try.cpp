/**
* @author neko13
*/
#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
#define all(c) c.begin(), c.end()
// 13C
#define DBG 0
#define sz(c) ((int)(c).size())
#define forl(i, a, b) for(int i = (a); i < (b); ++i)
#define forle(i, a, b) for(int i = (a); i <= (b); ++i)
#define forg(i, a, b) for(int i = (a); i > (b); --i)
#define forge(i, a, b) for(int i = (a); i >= (b); --i)
#define forlc(i, a, b) for(int i##_b = (b), i = (a); i < i##_b; ++i)
#define forlec(i, a, b) for(int i##_b = (b), i = (a); i <= i##_b; ++i)
#define forgc(i, a, b) for(int i##_b = (b), i = (a); i > i##_b; --i)
#define forgec(i, a, b) for(int i##_b = (b), i = (a); i >= i##_b; --i)
#define forall(i, v ) forl(i, 0, sz(v))
#define forallc(i, v ) forlc(i, 0, sz(v))
#define forlla(i, v ) forge(i, sz(v)-1, 0)
#define forls(i, n, a, b) for(int i = a; i != b; i = n[i])
#define rep(n) for(int repp = 0; repp < (n); ++repp)
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
inline int rdi() { int d; scanf("%d", &d); return d; }
inline char rdc() { scanf(" "); return getchar(); }
inline string rds() { rd(string, s); return s; }
inline double rddb() { double d; scanf("%lf", &d); return d; }
template<class T> inline bool updateMin(T& a, T b) { return a>b? a=b, true: false; }
template<class T> inline bool updateMax(T& a, T b) { return a<b? a=b, true: false; }

int toInt(const string& s) {
int sum = 0;
forallc(i, s) sum = sum<<1|s[i]=='1';
return sum;
}

string toStr(int x) {
string str;
for( ; x; x >>= 1)
str += (char)('0'+(x&1));
reverse(all(str));
return str;
}

int main() {
forlec(cas, 1, rdi()) {
string str = toStr(rdi());
if(!next_permutation(all(str))) str = "10"+str.substr(0, sz(str)-1);
printf("Case %d: %d\n", cas, toInt(str));
}
return 0;
}
