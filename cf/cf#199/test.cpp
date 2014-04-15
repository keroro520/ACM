#include <stdio.h>

int main()
{
	int n, query, s, f, l, r;
	scanf("%d%d%d%d", &n, &query, &s, &f);
	char ch = (s < f ? 'R' : 'L');
	int label = (s < f ? 1 : -1);
	int old = 0, now, tmp = query ;
	while(query--) {
		scanf("%d%d%d", &now, &l, &r);
		for(int i = 0; i < now - old - 1; i++) {
			s += label;
			printf("%c", ch);
			if(s == f) {
				puts("");
				return 0;
			}
		}
		if((l <= s && s <= r) || (l <= s + label && s + label <= r)) printf("X");
		else printf("%c", ch), s += label;
		
		if(s == f) {
			puts("");
			return 0;
		}
		old = now;
	}
	return 0;
}
