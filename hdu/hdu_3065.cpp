/*
	ac自动机 模板题
*/
#include <stdio.h>
#include <string.h>
#define			Kind		26
int times[1005];

struct Trie {
	Trie *fail, * child[Kind];
	int id;
	Trie () {
		id = -1, fail = NULL;
		memset(child, 0, sizeof(child));
	}
} ;
Trie * root, * Q[1005 * 55];

void Insert(char * str, int id)
{
	Trie * p = root;   int len = strlen(str);
	for(int i = 0; i < len; i++) {
		int idx = str[i] - 'A';
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
	Trie * p = root;   int len = strlen(str);
	for(int i = 0; i < len; i++) {
		int idx = str[i] - 'A';
		if(! ('A' <= str[i] && str[i] <= 'Z') ) { p = root; continue ; }		//有非大写字母的，直接p = root~
		while(p != root && p->child[idx] == NULL) p = p->fail;
		if(p->child[idx]) {
			p = p->child[idx];
			Trie * tmp = p;
			while(tmp != root && tmp->id != -1) {
				times[tmp->id] ++;
				tmp = tmp->fail;
			}
		}
	}
}

char str[2000005], word[1005][55];
int main()
{
	int n;
	while(scanf("%d", &n) != EOF) {
		root = new Trie ;
		memset(times, 0, sizeof(times));
		for(int i = 0; i < n; i++) {
			scanf("%s", word[i]);
			Insert(word[i], i);
		}
		Fail();
		scanf("%s", str);
		Query(str);
		Delete();
		for(int i = 0; i < n; i++) if(times[i]) printf("%s: %d\n", word[i], times[i]);
	}
	return 0;
}
