
const int n = 14;
void init()
{
	string s = "0m";
	for(int i = 1; i < 10; i++) {
		s[0] = s[0] + 1;
		M[ s ] = i;
		tile.push_back( s );
	}
	s = "0s";
	for(int i = 21; i < 30; i++) {
		s[0] = s[0] + 1;
		M[ s ] = i;
		tile.push_back( s );
	}
	s = "0p";
	for(int i = 41; i < 50; i++) {
		s[0] = s[0] + 1;
		M[ s ] = i;
		tile.push_back( s );
	}
	s = "0c";
	for(int i = 61; i < 61+7; i++) {
		s[0] = s[0] + 1;
		M[ s ] = i;
		tile.push_back( s );
	}
}
bool cmp(string &a, string &b)
{
	if(a[1] == b[1]) return a[0] <= b[0];
	if(a[1] == 'm' || b[1] == 'm') return a[1] == 'm';
	if(a[1] == 's' || b[1] == 's') return a[1] == 's';
	if(a[1] == 'p' || b[1] == 'p') return a[1] == 'p';
}
string b[n] = {"1m", "9m", "1p", "9p", "1s" , "9s" , "1c", "2c", "3c", "4c", "5c", "6c", "7c"};

bool situation1()
{
	bool flag = true;
	for(int i = 0; i < n; i+= 2) if(a[i] != a[i+1]) { flag = false; break; }
	return flag;
}
int check()
{
	sort(a, a+n, cmp);
	if(situation1()) return -1;
	
}
void output()
{
	if(ans.size() == 0) puts("Nooten");
	else {
		printf("%d", ans.size());
		for(vector<string> :: iterator it = ans.begin(); it != ans.end(); it++) printf(" %s", ans[i].c_str());
		puts("");
	}
}
int main()
{
	char str[5];  int cases;
	init();
	scanf("%d", &cases);
	while(cases--) {
		for(int i = 0; i < 13; i++) scanf("%s", str), a[i] = (string) str;
	
		if(situation2()) {
			for(int i = 0; i < 13; i++) ans.push_back( b[i] );
			output();
			continue;
		}
		ans.clear();
		for(vector<string> :: iterator it = tile.begin(); it != tile.end(); it++) {
			a[13] = *it;
			int res = check();
			if(res) ans.push_back( *it );
			if(res == -1) break;
		}
		output();
	}
	return 0;
}
