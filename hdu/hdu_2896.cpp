/*
	AC自动机模板题
	题意：n个单词，m个句子，问m个句子包含了哪个单词，分别按字典序输出。
	思路：题目保证单词不重复，所以只要每个单词尾节点存个id表示该单词的编号即可。

		  Kind开到256会MLE
*/
#include <algorithm>
#include <vector>
#include <string.h>
#include <stdio.h>
using namespace std;
#define			Kind		128
struct Trie {
	Trie * child[Kind], * fail;
	int id;
	Trie() {
		fail = NULL, id = -1;
		memset(child, 0, sizeof(child));
	}
} ;
Trie * root, *Q[205 * 505];
vector<int> ans, web[1005];

void Insert(char * str, int id)
{
	Trie * p = root;  int len = strlen(str);
	for(int i = 0; i < len; i++) {
		int idx = str[i];
		if(!p->child[idx]) p->child[idx] = new Trie;
		p = p->child[idx];
	}
	p->id = id;
}
void Fail()
{
	int car = 0, cdr = 0;
	Q[car++] = root;
	while(cdr < car) {
		Trie * p = Q[cdr++] ;
		for(int i = 0; i < Kind; i++) if(p->child[i]) {
			if(p == root) p->child[i]->fail = root;
			else {
				Trie * tmp = p;
				while(tmp->fail) {
					if(tmp->fail->child[i]) { 
						p->child[i]->fail = tmp->fail->child[i];
						break;
					}
					tmp = tmp->fail;
				}
				if(tmp->fail == NULL) p->child[i]->fail = root;
			}
			Q[car++] = p->child[i];
		}
	}
}

void Query(char * str)
{
	Trie * p = root;    int len = strlen(str);
	for(int i = 0; i < len; i++) {
		int idx = str[i];
		while(p != root && p->child[idx] == NULL) p = p->fail;
		if(p->child[idx]) {
			p = p->child[idx];
			Trie * tmp = p;
			while(tmp != root && tmp->id != -1) {			//TODO
				ans.push_back(tmp->id);
				tmp = tmp->fail;
			}
		}
	}
}
void Delete()
{
	int car = 0, cdr = 0;
	Q[car++] = root;
	while(cdr < car) {
		Trie * p = Q[cdr++];
		for(int i = 0; i < Kind; i++) if(p->child[i]) Q[car++] = p->child[i];
		delete p;
	}
}
char str[10005];
int main()
{
	int n, m;
	while(scanf("%d", &n) != EOF) {
		root = new Trie;
		for(int i = 1; i <= n; i++) {
			scanf("%s", str);
			Insert(str, i);
		}
		Fail();

		scanf("%d", &m);
		for(int i = 1; i <= m; i++) {
			scanf("%s", str);
			ans.clear();
			Query(str);
			web[i] = ans;
		}
		Delete();

		int tot = 0;
		for(int i = 1; i <= m; i++) if(web[i].size() > 0) {
			tot ++;
			printf("web %d:", i);
			sort(web[i].begin(), web[i].end());
			for(vector<int> :: iterator it = web[i].begin(); it != web[i].end(); it++)
				printf(" %d", *it);
			puts("");
		}
		printf("total: %d\n", tot);
	}
	return 0;
}
