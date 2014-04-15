/*
	AC自动机 模板
	题意：句子包含多少个单词，不重复计数
*/
#include <stdio.h>
#include <string.h>
#define			MAXN		10005

struct Trie {
	Trie * child[26];
	Trie * fail;
	int cnt ;
	Trie () {
		cnt = 0, fail = NULL, memset(child, 0, sizeof(child));
	}
};

Trie *root, * Q[MAXN * 50];

void Insert(char *str)
{
	Trie *p = root; int len = strlen(str);
	for(int i = 0; i < len; i++) {
		int idx = str[i] - 'a' ;
		if(p->child[idx] == NULL) p->child[idx] = new Trie;
		p = p->child[idx];
	}
	p->cnt++;
}
void Fail()						//自顶向下，一个节点一个节点找fail指针
{
	int car = 0, cdr = 0;
	Q[car++] = root;
	while(cdr < car) {
		Trie * p = Q[cdr++];
		for(int i = 0; i < 26; i++)
			if(p->child[i]) {							//p有孩子节点i，则找i的fail指针
				if(p == root) p->child[i]->fail = root; //与根节点相连的fail指针都指向根节点
				else {
					Trie * tmp = p;
					while(tmp->fail) {					//父节点fail指针非空
						if(tmp->fail->child[i]) { 
							p->child[i]->fail = tmp->fail->child[i]; //父节点的fail指针指向的节点有孩子i，则可以作为p的i孩子的fail指针
							break; 
						}
						tmp = tmp->fail;				//到了这一步，说明现在的fail指针指向的节点没有孩子i，则fail指针继续往上跳
					}
					if(tmp->fail == NULL) p->child[i]->fail = root;
				}
				Q[car++] = p->child[i];
			}
	}
}

int  Query(char * str)
{
	Trie * p = root, * tmp = NULL; 
	int len = strlen(str), ans = 0;
	for(int i = 0; i < len; i++) {
		int idx = str[i] - 'a';
		while(p != root && p->child[idx] == NULL) p = p->fail;
		if(p->child[idx]) {						// p 记录当前位置最长后缀匹配，下次从该支继续匹配
			p = p->child[idx], tmp = p;			//用tmp继续找当前位置较短的后缀匹配
			while(tmp != root && tmp->cnt) {
				ans += tmp->cnt;
				tmp->cnt = 0;					//
				tmp = tmp->fail;				//因为可能有多次匹配是吧~
			}
		}
	}
	return ans;
}
void Delete()
{
	int car = 0, cdr = 0;
	Q[car++] = root;
	while(cdr < car) {
		Trie * p = Q[cdr++];
		for(int i = 0; i < 26; i++) if(p->child[i]) Q[car++] = p->child[i];
		delete p;
	}
}
char str[1000005];
int main()
{
	int cases, n;
	scanf("%d", &cases);
	while(cases--) {
		root = new Trie;
		scanf("%d", &n);
		while(n--) {
			scanf("%s", str);
			Insert(str);
		}
		Fail();
		scanf("%s", str);
		printf("%d\n", Query(str));
		Delete();
	}
	return 0;
}
