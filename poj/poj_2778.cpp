/*
	ac自动机 + 矩阵快速幂
	代码风格还是挺好的，直接拿来做模板了
*/
#include <stdio.h>
#include <string.h>
typedef		long long		ll;
const	int 	MOD		=	100000;
int idx;

inline	int	 hash(char ch) {
	switch (ch) {
		case 'A' : return 0; case 'T' : return 1; case 'C' : return 2; case 'G' : return 3;
	}
}
struct Matrix {
	ll mat[105][105];
	void   init() { memset(mat, 0, sizeof(mat)); }
	friend Matrix operator * (const Matrix & a, const Matrix & b) ;
	friend Matrix operator ^ (const Matrix & a, int x) ;
} M;
struct Trie {
	Trie * child[4], * fail;
	int isword, id;
} * root, *Q[100005], t[100005];

Matrix operator * (const Matrix & a, const Matrix & b) {
	Matrix ans;  ans.init();
	for(int i = 0; i < idx; i++)
		for(int k = 0; k < idx; k++) if(a.mat[i][k])
			for(int j = 0; j < idx; j++)
				ans.mat[i][j] = (ans.mat[i][j] + a.mat[i][k] * b.mat[k][j]) % MOD;
	return ans;
}
Matrix operator ^ (const Matrix & a, int x) {
	Matrix ans, tmp = a;  ans.init();
	for(int i = 0; i < idx; i++)
		for(int j = 0; j < idx; j++) ans.mat[i][j] = (i == j);
	while(x) {
		if(x & 1) ans = ans * tmp;
		tmp = tmp * tmp;
		x >>= 1;
	}
	return ans;
}
Trie * NewTrie() 	//静态Trie
{
	Trie * p = &t[idx];
	p->isword = 0, p->fail = NULL, p->id = idx++;
	memset(p->child, 0, sizeof(p->child));
	return p;
}
void Insert(char * str)
{
	Trie * p = root;   int len = strlen(str);
	for(int i = 0; i < len; i++) {
		int idx = hash(str[i]);
		if(!p->child[idx]) p->child[idx] = NewTrie();
		p = p->child[idx];
	}
	p->isword = 1;
}
void Fail()
{
	int car = 0, cdr = 0;
	Q[car++] = root;
	while(cdr < car) {
		Trie * p = Q[cdr++];
		for(int i = 0; i < 4; i++)
			if(p->child[i] == NULL) {								//这部分跟一般ac自动机不一样	//感觉连起来就成无限状态自动机了
				if(p == root) p->child[i] = root;
				else		  p->child[i] = p->fail->child[i];
			} else {
				if(p == root) p->child[i]->fail = root;
				else {
					p->child[i]->fail = p->fail->child[i];
					if(p->child[i]->fail->isword) p->child[i]->isword = 1;		//! 不能改成直接赋值	//label
				}
				Q[car++] = p->child[i];
			}
	}
}

char str[20];
int main()
{
	int n, m;
	while(scanf("%d %d", &m, &n) != EOF) {
		idx = 0;
		root = NewTrie();
		while(m--) {
			scanf("%s", str);
			Insert(str);
		}
		Fail();
		memset(M.mat, 0, sizeof(M.mat));
		for(int i = 0; i < idx; i++)
			for(int j = 0;j < 4; j++) {
				Trie * son = t[i].child[j];
				if(!son->isword && !t[i].isword) M.mat[i][son->id] ++;
			}
		M = M ^ n;
		ll ans = 0;
		for(int i = 0; i < idx; i++) ans = (ans + M.mat[0][i]) % MOD;
		printf("%I64d\n", ans);
	}
	return 0;
}
