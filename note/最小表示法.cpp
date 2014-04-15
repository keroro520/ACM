/*
	串的最小表示法


	令i=0,j=1
	如果S[i] > S[j] i=j, j=i+1
	如果S[i] < S[j] j++
	如果S[i]==S[j] 设指针k，分别从i和j位置向下比较，直到S[i] != S[j]
	         如果S[i+k] > S[j+k] i=i+k
	         否则j++
	返回i和j的小者
	
	注意到上面两个算法唯一的区别是粗体的一行。这一行就把复杂度降到O(n)了。
	值得一提的是，与KMP类似，最小表示法处理的是一个字符串S的性质，而不是看论文时给人感觉的处理两个字符串。
	应用最小表示法判断两个字符串同构，只要将两个串的最小表示求出来，然后从最小表示开始比较。剩下的工作就不用多说了。
*/
int min_Presentation(char *s, int len)
{
	int i = 0, j = 1, k = 0;
	while(i < len && j < len && k < len) {
		int res = s[(i+k)%len] - s[(j+k)%len];
		if(res == 0) k++;
		else {
			if(res > 0) i = i + k + 1;
			else j = j + k + 1;
			if(i == j) j++;
			k = 0;
		}
	}
	return min(i,j);
}

//树的最小表示   树的同构
string min_Presentation(int u, int pre)			//树的最小表示
{
	vector<string> sub;
	string res = "(";
	for(int k = head[u]; k != -1; k = edge[k].next) {
		int v = edge[k].v;
		if(v == pre || !vis[v]) continue;
		sub.push_back( min_Presentation(v, u) );
	}
	sort(sub.begin(), sub.end());
	for(int Size = sub.size(), i = 0; i < Size; i++) 
		res += sub[i];
	res += ")";
	return res;
}
