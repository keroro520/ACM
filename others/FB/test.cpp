
struct Player {
	int height, shot;
	string name;
} a[MAXN];
bool cmp(const Player & a, const Player & b) {
	if(a.shot != b.shot) return a.shot > b.shot;
	return a.height > b.height;
}
int main()
{
	scanf("%d", &cases);
	while(cases--) {
		scanf("%d %d %d", &n, &M, &p);
		for(int i = 1; i <= n; i++) scanf("%s %d %d", str, &a[i].shot, &a[i].height), a[i].name = (string) str;
		sort(a+1, a+n+1, cmp);
		
	}
	return 0;
}
