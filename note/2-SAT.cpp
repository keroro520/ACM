/*  LRJ 的 2-SAT  模板  */
bool dfs(int u)
{
	if(color[hash(u)]) return false;
	if(color[u])   return true;
	color[u] = 1;
	S[S_top++] = u;
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(!dfs(v)) return false;
	}
	return true;
}
bool solve()
{
	for(int i = 0; i < 2*n; i += 2)			// i += 2 ???
		if(!color[i] && !color[hash(i)]) {
			S_top = 0;
			if(!dfs(i)) {
				while(S_top > 0) color[S[--S_top]] = 0;
				if(!dfs(hash(i))) return false;
			}
		}
	return true;
}

/*
（1)2-SAT模型：存在n组元素，每组两个元素，且这两个元素互斥。
           某些组存在一些“关系”，可以证明，这些关系是对称的，且对称是可传递的。
           要求在满足给定关系的情况下在每组元素中选出一个元素的问题称为2-SAT问题。问是否存在即2-SAT判定问题，当然也可以求出一组可行解。
           一般有3种题目：判定是否有可行解；最优解（二分）；输出一组可行解



（2) 构图：构图的关键是找“冲突关系”，若a与b冲突，则可以连边a->b',b->a'.  
    每组2个元素，所以要把多于2个元素的情况压缩，如hdu 1824


（3)是否有可行解判定很简单，缩点后看xi与xi’有没有在同一个强连通子图里就可以了，有则return false。

（4)hdu 1814输出最小字典序

关于输出解，有两种方法，一种是逆向topsort输出任意解（hdu_1814_3.cpp)，另一种是暴力dfs，可以输出最小字典序解（hdu_1814.cpp）。
逆向topsort法：
    (0)建立图G的补图G'，下面的讨论都是针对G'的。
    (1)开队列Q1，Q2，遇到未染色点，加到Q1里，来一论topsort染色。
    (2)topsort-enter: 
            从Q1里取出元素i，若它此时还是未染色，则染red，把~i加到Q2里
            (3)不断地以Q2种的元素~i扩展开来，把~i的所有后继节点都进Q2，并染black
    (4)对于之前加到Q1的i点的子节点都入度减1，若入度为0则加到Q1
*/
