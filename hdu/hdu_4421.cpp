/*
    2-SAT   
    题意：该题给出操作(AND,OR,XOR)和结果(b[i][j]), 判断是否有解
          2012长春现场赛的题。

    由于不细心，WA了几次。。多是建边的时候粗心
    思路：该题给出操作(AND,OR,XOR)和结果(b[i][j])，只要把元素拆成bit形式来做2-SAT就行了。因为**有解就必须每个位bit都有解**，`且每一位bit不互相影响`。如果一下把31位都给拆来建图的话会ME，所以得一位一位地来，之前我没意识到这一点，原因在没运用到`每一位不互相影响`。

	拆点 : i 拆成x, x', x表示i为false, x'表示i为true
	建图 : 难点是同组元素连边的情况, 如AND->1, 和or->0。
		   “同组元素连边”有什么意义？达神跟我解释：如果只是一组元素连边的话没意义，但是有多组元素连边时就有意义了。举例，A AND B == 1, 连a->a', b->b'. 直观理解为这两组元素一定得选a'和b'。如果有解取了a和b，则建连通图的时候会把a也连上，同理有b/b'，则这个子连通图会包括a和a'，矛盾。（因为由于对称性，a组和b组肯定会有至少两条边相连，所以a/a'/b/b'会在同一环里）

	== 补充: 我根据lrj的解释再改了一下, 对于A AND B == 1连(A,B),(B,A)也AC了. 网上写法我注释掉了, 注释下面的是我理解的写法, 我是这样理解的, 我们的边(u,v)表示你标记了u点就要标记v点, 那对于A AND B = 1就应该是"你选了A为真就要选B为真, 选了B为真就要选A为真", 就变相地给xa和xb赋了"真"值.
	== 啊不对!不对! 我后面的写法好像不太对!! 
	== 只是这道题A和B只有唯一的条件我才碰巧AC而已, 如果有"A OR B == 0且A AND B == 1"这样的条件存在的话我就完蛋了!!
	== 连边(a->a')(b->b')才是变相给A,B赋值 !
	==2-sat不一定是对称的, 白书上有提到

    什么时候同组元素连边？--还没有比较好的理解...
    不知道pre-check有没有必要...
*/
#include <stdio.h>
#include <string.h>
#include <vector>
#include <stack>
using namespace std;
#define     debug       printf("!\n")
#define     MAXN        (500*2+2)
#define     MAXBIT      31
#define     OR          1
#define     AND         2
#define     XOR         3
vector<int> v[MAXN];
stack<int> S;
int dfn[MAXN], low[MAXN];
int b[501][501];
bool in_stack[MAXN];
int n, Index;

int hash(int x) { return x + n; }
bool solve();
void Tarjan(int now);

bool pre_check()
{
    for(int i = 0; i < n; i++) {
        if(b[i][i] != 0) return false;
        for(int j = 0; j < i; j++) 
            if(b[i][j] != b[j][i]) return false;
    }
    return true;
}

int main()
{
    while(scanf("%d", &n) != EOF) {
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++) scanf("%d", &b[i][j]);
        if(!pre_check()) {
            printf("NO\n");
            continue;
        }
        bool flag = true;
        for(int i = 0; i < MAXBIT; i++)
            if(!solve()) {
                flag = false;
                break;
            }
        printf(flag ? "YES\n" : "NO\n");
    }
    return 0;   
}
void init()
{
    Index = 1;
    while(!S.empty()) S.pop();
    memset(dfn, -1, sizeof(dfn));
    memset(low, -1, sizeof(low));
    memset(in_stack, false, sizeof(in_stack));
    for(int N = hash(n), i = 0; i < N; i++)
        v[i].clear();
}
bool solve()
{
    init();
    for(int row = 0; row < n; row++)
        for(int col = 0; col < row; col++) {
            int bit = (b[row][col] & 1);
            int op;
            if((row & 1) && (col & 1)) op = OR;
            else if(!(row & 1) && !(col & 1)) op = AND;
            else op = XOR;
            
            int x = row, y = col, x1 = hash(row), y1 = hash(col);	//x = ai(0,1)   y = aj(0,1)
            if(op == OR) {
                if(bit == 0) {
                    //v[x1].push_back(x);
                    //v[y1].push_back(y);
					v[x1].push_back(y1);
					v[y1].push_back(x1);
                } else {
                    v[x].push_back(y1);
                    v[y].push_back(x1);
                }
            } else if(op == AND) {
                if(bit == 0) {
                    v[x1].push_back(y);
                    v[y1].push_back(x);
                } else {
                    //v[x].push_back(x1);
                    //v[y].push_back(y1);
					v[x].push_back(y);
					v[y].push_back(x);
                }
            } else if(op == XOR) {
                if(bit == 0) {
                    v[x].push_back(y);
                    v[y].push_back(x);
                    v[x1].push_back(y1);
                    v[y1].push_back(x1);
                } else {
                    v[x].push_back(y1);
                    v[y].push_back(x1);
                    v[x1].push_back(y);
                    v[y1].push_back(x);
                }
            }
        }
    for(int row = 0; row < n; row++)
        for(int col = 0; col < row; col++) 
            b[row][col] >>= 1;
    for(int N = hash(n), i = 0; i < N; i++)
        if(dfn[i] == -1) Tarjan(i);
    for(int i = 0; i < n; i++)
        if(low[i] == low[hash(i)]) return false;
    return true;
}
void Tarjan(int now)
{
    in_stack[now] = true;
    S.push(now);
    dfn[now] = low[now] = Index++;
    for(int Size = v[now].size(), i = 0; i < Size; i++) {
        int tmp = v[now][i];
        if(in_stack[tmp]) low[now] = min(low[now], low[tmp]);
        else if(dfn[tmp] == -1) {
            Tarjan(tmp);
            low[now] = min(low[now], low[tmp]);
        }
    }
    if(dfn[now] == low[now]) {
        int tmp ;
        do {
            tmp = S.top();
            S.pop();
            low[tmp] = low[now];
            in_stack[tmp] = false;
        } while(tmp != now);
    }
}
/*
http://acm.hdu.edu.cn/showproblem.php?pid=4421
*/
