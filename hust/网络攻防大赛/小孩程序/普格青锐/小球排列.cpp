#include<cstdio>

using namespace std;

int ju (int x){
	if (x < 0)
		return -x;
	return x;
}
int main(){
  freopen("ball_in.txt","r",stdin);
  freopen("ball_out.txt","w",stdout);
	int t,a,b,c;
	scanf("%d",&t);
	for (int i = 0; i < t; ++i){
		scanf("%d%d%d",&a,&b,&c);
		if (a > 0 && b > 0 && c > 0){
			if (a == b && b == c)
				printf("6\n");
			else if (a != b && b != c && c != a)
				printf("0\n");
			else if (ju(a - b) == 1)
				printf("2\n");
			else if (a == b && ju(a - c) == 1)
				printf("2\n");
			else
				printf("0\n");
		}
		else if (a > 1 || b > 1 || c > 1 || (a == 0 && b == 0 && c == 0))
			printf("0\n");
		else if (a ^ b ^ c == 0)
			printf("2\n");
		else
			printf("1\n");
	}
	return 0;
}
