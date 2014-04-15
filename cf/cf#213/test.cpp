

int solve(int n)
{
	int sum = 0;
	for(int i = 0; i < n; i++) {
		if(sum + d >= after[i]) work(i);
		else {
			for(i ; i < n; i++) if(sum+d >= a[i]
		}
	}
}
int main()
{
	scanf("%d %d", &n, &d);
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	sort(a, a+n);
	int sum = 0;
	for(int i = 0; i < n; i++) {
		if(sum + d < a[i]) { n = i; break; }
	}
	printf("%d ", sum);
	
	for(int i = n-1; i >= 0; i--) after[i] = after[i+1] + a[i];

	sum = solve(n);
	printf("%d\n", sum);
	return 0;
}
