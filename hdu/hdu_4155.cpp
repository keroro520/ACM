/*
	博弈  SG   
	题意：Nim单游戏，取数只能从有限集合数集S里面取。

	思路：dfs，这道题又是什么SG性质的，就是败态后面都是胜态，胜态后面都是败态的。
*/
//hdu 4155
#include <stdio.h>
#include <string.h>
int cards[10];

void init()
{
	for(int i = 1; i <= 6; i++) cards[i] = 4;
}
int dfs(int sum)
{
	if(sum == 0) return 0;	
	for(int i = 1; i <= 6&& sum >= i; i++) if(cards[i]) {
		cards[i]--;
		if(!dfs(sum - i)) {
			cards[i]++;
			return 1;
		}
		cards[i]++;
	}
	return 0;
}
int main()
{
	char s[1000];
	while(scanf("%s", s) != EOF) {
		init();
		int sum = 0, ans = -1;
		for(int i = 0; s[i]; i++) {
			sum += s[i] - '0';
			if(sum > 31) ans = !(i&1);
			else if(sum == 31) ans = (i&1);
			cards[s[i] - '0'] --;
		}
		sum = 31 - sum;
		if(ans != -1) {
			printf("%s %c\n", s, ans + 'A');
			continue;
		}
		if(dfs(sum)) ans = !(strlen(s) % 2);
		else ans = strlen(s) % 2;
		if(strlen(s) % 2 == 0) printf("%s %c\n", s, 'A' + !dfs(sum));
		else printf("%s %c\n", s, dfs(sum) ? 'B' : 'A');
	}
	return 0;
}
