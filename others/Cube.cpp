// 郭婷的面试题
// 问一个魔方转4次，能转出一个面有最多多少种颜色
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;
#define			ROTATENUM			12

int change[ROTATENUM][5][4] = {
	{ {24, 36, 29, 17}, {21, 37, 32, 16}, {18, 38, 35, 15}, {2,   8,  0,  6}, { 1,  5,  7,  3} },
	{ {17, 29, 36, 24}, {16, 32, 37, 21}, {15, 35, 38, 18}, { 6,  0,  8,  2}, { 3,  7,  5,  1} },
	{ { 9, 20, 44, 33}, {10, 23, 43, 30}, {11, 26, 42, 27}, {45, 47, 53, 51}, {46, 50, 52, 48} },
	{ {33, 44, 20,  9}, {30, 43, 23, 10}, {27, 42, 26, 11}, {51, 53, 47, 45}, {48, 52, 50, 46} },
	{ { 2, 11, 47, 38}, { 5, 14, 50, 41}, { 8, 17, 53, 44}, {24, 18, 20, 26}, {21, 19, 23, 25} },
	{ {38, 47, 11,  2}, {41, 50, 14,  5}, {44, 53, 17,  8}, {26, 20, 18, 24}, {25, 23, 19, 21} },
	{ { 0,  9, 45, 36}, { 3, 12, 48, 39}, { 6, 15, 51, 42}, {35, 29, 27, 33}, {32, 28, 30, 34} },
	{ {36, 45,  9,  0}, {39, 48, 12,  3}, {42, 51, 15,  6}, {33, 27, 29, 35}, {34, 30, 28, 32} },
	{ { 0, 27, 53, 18}, { 1, 28, 52, 19}, { 2, 29, 51, 20}, {17, 15,  9, 11}, {14, 16, 12, 10} },
	{ {18, 53, 27,  0}, {19, 52, 28,  1}, {20, 51, 29,  2}, {11,  9, 15, 17}, {10, 12, 16, 14} },
	{ { 6, 33, 47, 24}, { 7, 34, 46, 25}, { 8, 35, 45, 26}, {36, 38, 44, 42}, {37, 41, 43, 39} },
	{ {24, 47, 33,  6}, {25, 46, 34,  7}, {26, 45, 35,  8}, {42, 44, 38, 36}, {39, 43, 41, 37} }
};

class Cube {
	public :
	int p[54] ;
} ;
vector< Cube > T, Q;

inline int color(int x) { return (1 << (x / 9 + 1)); }
void init()
{
	Cube c;
	for(int i = 0; i < 54; i++) c.p[i] = i;
	Q.push_back(c);
}
Cube rotate(Cube c, int x)
{
	for(int i = 0; i < 5; i++) {
		int tmp = c.p[ change[x][i][0] ];
		for(int j = 3; j >= 1; j--)
			c.p[change[x][i][j]] = c.p[change[x][i][j-1]];
		c.p[change[x][i][0]] = tmp;
	}
	return c;
}
int calc(Cube & c)
{
	int ans = 0;
	for(int i = 0; i < 6; i++) {
		int sum = 0, res = 0;
		for(int j = i*9; j < i*9+9; j++)
			sum |= color(c.p[j]);
		for(int j = 0; j < 6; j++) if (sum & (1<<j)) res++;
		ans = max(ans, res);
	}
	return ans;
}
int main()
{
	init();
	for(int times = 0; times < 4; times++) {
		T.clear();
		for(vector<Cube> :: iterator it = Q.begin(); it != Q.end(); it ++) {
			Cube c = *it;
			for(int i = 0; i < ROTATENUM; i++) {
				Cube tmp = rotate(c, i);
				T.push_back( tmp );
			}
		}
		Q = T;
	}
	int ans = 0;
	for(vector<Cube> :: iterator it = Q.begin(); it != Q.end(); it ++) {
		ans = max(ans, calc(*it));
	}
	printf("%d\n", ans);
	return 0;
}
