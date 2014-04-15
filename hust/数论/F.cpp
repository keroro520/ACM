
void init()
{
	b[0] = 1;   top = 64;
	for(int i = 1; i < top; i++) b[i] = (1LL << i) * ((i & 1) ? -1 : 1);
}
bool dfs(ll n, int deep)
{
	if(deep >
}
int main()
{
	init();
	scanf("%d", &cases);
	while(cases--) {
		scanf("%lld", &n);
		S_top = 0;
		dfs(n, 0);
		printf("Case #%d: ", ++Cas);
		for(int i = 0; i < S_top; i++) printf("%d", S[i]);
		puts("");
	}
	return 0;
}
