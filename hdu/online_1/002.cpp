#include <stdio.h>
int n;
const char TMP_S[100] = "babbaa";
void solve();
int main()
{
	int cases, Cas = 0, m;
	scanf("%d", &cases);
	while(cases--) {
		printf("Case #%d: ", ++Cas);
		scanf("%d%d", &m, &n);
		if(m == 1) {
			for(int i = 0 ; i < n; i++) printf("a");
			puts("");
			continue;
		} else if(m >= 3) {
			for(int i = 0; i < n; i++) printf("%c", 'a' + (i%3));
			puts("");
		} else {
			if(n <= 8) solve();
			else {
				printf("aaaa");
				int len = (n - 4) / 6 * 6;
				for(int i = 0; i < len ; i++) printf("%c", TMP_S[i%6]);
				if( ((n-4) % 6 <= 2) ) {
					for(int i = 0; i < (n-4)%6; i++) printf("a");
				} else {
					for(int i = 0; i < (n-4)%6; i++) printf("%c", TMP_S[i%6]);
				}
				puts("");
			}
		}
	}
	return 0;
}
void solve()
{
   switch (n) {
   	case 1:printf("a"); break;
   	case 2:printf("ab"); break;
   	case 3:printf("aab"); break;
   	case 4:printf("aabb"); break;
   	case 5:printf("aaaba"); break;
   	case 6:printf("aaabab"); break;
   	case 7:printf("aaababb"); break;
   	case 8:printf("aaababbb"); break;
   };
   puts("");
}
