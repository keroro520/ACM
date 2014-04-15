#include <stdio.h>
#include <algorithm>
using namespace std;

const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {-1, 0, 1, 0};
struct Rabit {
	int x, y, v, turn, dir;
	void out() { printf("! (%d %d) %d %d\n", x,y,v,dir); }
} a, b;
int n, K;

int inline hash(char ch) {
	switch (ch) {
		case 'W' : return 0;
		case 'N' : return 1;
		case 'E' : return 2;
		case 'S' : return 3;
	}
}
int turn_left(int x) {
	return ((x - 1) % 4 + 4) % 4;
}
int turn_around(int x) {
	if(x == 0 || x == 2) return x == 0 ? 2 : 0;
	return x == 1 ? 3 : 1;
}
void move(Rabit & a)
{
	//a.out();
	int tx = a.x, ty = a.y;
	if(a.dir == 0 || a.dir == 2) {
		ty += dy[a.dir] * a.v;
		if(ty <= 0)     ty = 1 - ty + 1, a.dir = turn_around(a.dir);
		else if(ty > n) ty = n - (ty - n), a.dir = turn_around(a.dir);
	} else {
		tx += dx[a.dir] * a.v;
	//printf("###  %d\n", tx);
		if(tx <= 0) 	tx = 1 - tx + 1, a.dir = turn_around(a.dir);
		else if(tx > n)	tx = n - (tx - n), a.dir = turn_around(a.dir);
	}
	a.x = tx, a.y = ty;
	//a.out();
}
char str[2];
int main()
{
	while(scanf("%d", &n), n) {
		scanf("%s %d %d", str, &a.v, &a.turn),  a.dir = hash(str[0]), a.x = a.y = 1;
		scanf("%s %d %d", str, &b.v, &b.turn),  b.dir = hash(str[0]), b.x = b.y = n;
		scanf("%d", &K);
		for(int k = 0; k < K; k++) {
			if(a.x == b.x && a.y == b.y) swap(a.dir, b.dir);
			else if(k && (k % a.turn == 0 || k % b.turn == 0)) {
				if(k && k % a.turn == 0) a.dir = turn_left(a.dir);
				if(k && k % b.turn == 0) b.dir = turn_left(b.dir);
			}
			move(a), move(b);
		}
		printf("%d %d\n%d %d\n", a.x, a.y, b.x, b.y);
	}
	return 0;
}
