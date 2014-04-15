

int main()
{
	while(scnaf("%d %d", &n, &m) != EOF) {
		init();
		for(int i = 0; i < m; i++) {
			scanf("%d %d %d", &u, &v, &w);
			add_edge(u, v, w), add_edge(v, u, w);
		}
		int _max = -inf, _i;
		dijstra(1);
		for(int i = 2; i <= n; i++) if(_max < dis[i]) _max = dis[i], _i = i;
		dijstra(_i);
		for(
		
	}
	return 0;
}
