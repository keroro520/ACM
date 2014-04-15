/*
	还是不会重复序列的康托展开啊...
*/


int main()
{
	fac[0] = 1;
	for(int i = 1; i <= 30; i++) fac[i] = fac[i-1] * i;
	scanf("%d", &cases);
	while(cases--) {
		memset(cnt, 0, sizeof(cnt));
		scanf("%s %d", &str, &need);
		int n = strlen(str);
		for(int i = 0; i < n; i++) a[i] = str[i] - 'a', cnt[ a[i] ] ++;

		bool flag = true;
		for(int i = 0; i < 26; i++) if(a[i] & 1) { flag = false; break; }
		if(!flag || (fac[n/2] > 0 && fac[n/2] < need)) { printf("Case %d: XXX\n", ++Cas); continue; }

		solve(a, n, res);
		for(int i = 0;
	}
	return 0;
}
