/*
	打表找规律题
	应该是可以AC的，但是打表的时候打错了，唉
	。。。
	
*/
#include <string.h>
#include <stdio.h>
#include <math.h>

#define			MAXN		500005
int euler[MAXN];
bool boo[MAXN];
void getEuler()     //欧拉函数线性筛
{

	for(int i = 2; i <= 50000; i++) if(!boo[i]) {
		int j = i+i;
		//if(i < 500) printf("%lld ", (long long)i * i);
		while(j <= 50000) {
			boo[j] = true;
			j += i;
		}
	}

    memset(euler,0,sizeof(euler));
    euler[1] = 1;
    for(int i = 2;i <= 50000;i++)
        if(!euler[i])
            for(int j = i;j <= 50000; j += i) {
                if(!euler[j])
                euler[j] = j;
                euler[j] = euler[j]/i*(i-1);
            }
}

int factor(int x)
{
	int sum = 0;
	for(int oo = (int) sqrt(x+0.5), i = 2; i <= oo; i++) //if(!boo[i])
		if(x % i == 0) {
			sum ++;
			if(x / i != i) sum++;
		}
	return sum;
}
void hello()
{
	for(int i = 1; i <= 31*31 ; i++)  {
		int phi = euler[ i ], pri = factor(i);
		int f   = i-1 - phi - pri;
		if( (f & 1) ) printf("%d : %d\n", i, f);
	}
	printf("!  %d  %d %d\n", 81, factor(81), euler[81]);
}
int main()
{	
	getEuler();
	hello();
	return 0;
}
