

/* 判断奇环 ======================================================================================*/
void Find(int u, int c)
{
	if(color[u] != -1) return ;
	color[u] = c;
	for(int k = head[u]; k != -1; k = edge[k].next) Find(edge[k].v, !c);
}
bool dye()
{
	memset(color, -1, sizeof(color));
	for(int i = 1; i <= n; i++) if(color[i] == -1) Find(i, 0);
	for(int i = 0; i < edge_num; i++) if(color[edge[i].u] == color[edge[i].v]) return false;
	return true;
}
/* ===============================================================================================*/

/* 堆优化的SPFA ==================================================================================*/
typedef pair<int, int> PII;
bool SPFA(int s)
{
	memset(times, 0, sizeof(times));
	memset(dis, 127, sizeof(dis));
	memset(inque, false, sizeof(inque));
	dis[s] = 0;
	priority_queue< PII > Q;			//默认pair按first增序
	Q.push(PII(0, s));					//first表示距离，second才表示标号
	while(!Q.empty()) {
		int u = Q.top().second;
		Q.pop();
		inque[u] = false;
		for(int k = head[u]; k != -1; k = edge[k].next) {
			int v = edge[k].v;
			if(dis[v] > dis[u] + edge[k].w) {
				dis[v] = dis[u] + edge[k].w;
				if(!inque[v]) {
					inque[v] = true;
					Q.push(PII(dis[v], v));
					if(++times[v] > n) return false;
				}
			}
		}
	}
	return true;
}
/* ==============================================================================================*/
