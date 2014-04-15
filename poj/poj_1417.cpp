/*
	并查集合 分组背包 DP  好题
	题意：p1个好人，p2个坏人。好人只说真话，坏人只说假话。给出一些关系<xi,yi,ai>，表示‘xi说yi是好人/坏人’，ai为‘yes’表示好人，为‘no’表示坏人。判断是否有唯一解，按升序输出好人的id。
		  数据有重复，还有xi = yi的数据，但是不会有矛盾的情况，所以不用担心关系矛盾（虽说我连判断矛盾都写了）。

	思路：枚举目前不明身份的i，设他为好人，则可以根据给出的关系圈出一些人是好人还是坏人。假设圈出好人a个，坏人b个，则我根据之前猜测，如果我再把i设为坏人，圈出来的好人应该是b个，坏人a个，事实证明该猜测是对的。
		  下面就可以把问题变为分组背包了。
		  上述操作就把p1+p2个人分成了一个个分组背包里的组（如果j是由枚举i的身份给圈出来的，则j跟i属于同意组），一个组里有两件物品，第一件物品好人a个，第二件物品好人b个。每个组必须取一个且仅取一个。问取的所有物品的好人总和为p的方案是否唯一？
		  如果解唯一就输出解咯，因为已知是唯一，所以输出解很简单啦~



		  //因为要判唯一，所以DP状态f[][]要表示的是方案数而不是判定性
*/
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>
using namespace std;
typedef		pair<int,int> 		Pii;
typedef		vector< pair<int,int> > :: iterator 		VII;
vector< Pii > A[605], B[605];
vector< int > result;
int color[605], group[605];
int n, top, anc, p1, p2, f[605][605], pre[605][605], divine[605][2], S[605];
void init()
{
	anc = 0;
	result.clear();
	for(int i = 1; i <= n; i++) A[i].clear(), B[i].clear();
	memset(color,  -1, sizeof  color);
}
void output(int anc, int p)
{
	if(anc == 0) return ;
	int next = pre[anc][p];
	int k    = p - next;
	if( k == divine[anc][0] ) {			//如果是选了第一个物品
		for(int i = 1; i <= n; i++) if( group[i] == anc && color[i] == 1 ) result.push_back(i);
	} else {							//选了第二个物品
		for(int i = 1; i <= n; i++) if( group[i] == anc && color[i] == 0 ) result.push_back(i);
	}
	output(anc-1, next);
}
bool dye(int u, int c)
{
	if(color[u] != -1) return c == color[u];
	S[top++] = u;
	color[u] = c;
	for(VII it = A[u].begin(); it != A[u].end(); it++) {
		if(it->second == 1) {
			if(!dye(it->first, c))  return false;
		} else {
			if(!dye(it->first, !c)) return false;
		}
	}
	for(VII it = B[u].begin(); it != B[u].end(); it++) {
		if(it->second == 1) {
			if(!dye(it->first, c))  return false;
		} else {
			if(!dye(it->first, !c)) return false;
		}
	}
	return true;
}
int main()
{
	int query, x, y; char str[5];  bool flag;
	while(scanf("%d %d %d", &query, &p1, &p2) , query || p1 || p2) {
		n = p1 + p2;   flag = true;
		init();
		for(int i = 0; i < query; i++) {
			scanf("%d %d %s", &x, &y, str);
			A[x].push_back( Pii(y,str[0]=='y') );
			B[y].push_back( Pii(x,str[0]=='y') );
		}
		for(int i = 1; i <= n; i++) if(color[i] == -1) {
			anc++;
			top = 0;
			if(!dye(i, 1)) {
				//while(top) color[ S[--top] ] = -1;		//我判了是否矛盾...没必要
				//if(!dye(i, 0)) flag = false;
			}
			divine[anc][0] = 0, divine[anc][1] = top;		//该组第一个物品好人数divine[anc][0]个，第二个物品好人数divine[anc][1]个
			while(top) {
				if(color[ S[--top] ] == 1) divine[anc][0]++;
				group[S[top]] = anc;						//打个标记，是第anc组
			}
			divine[anc][1] -= divine[anc][0];				//事实证明猜测没错
		}

		memset(f,    0, sizeof    f);
		f[0][0] = 1;
		for(int i = 1; i <= anc; i++) {
			for(int j = p1; j >= 0; j--) {
				for(int k = 0; k < 2; k++) 
					if(j >= divine[i][k] && f[i-1][j-divine[i][k]]) 
						f[i][j]++, pre[i][j] = j-divine[i][k];
			}
		}
		if(f[anc][p1] != 1 || !flag) { puts("no"); continue; }
		else {
			output(anc, p1);
			sort(result.begin(), result.end());
			for(vector<int> :: iterator it = result.begin(); it != result.end(); it ++)
				printf("%d\n", *it);
			puts("end");
		}
	}
	return 0;
}
