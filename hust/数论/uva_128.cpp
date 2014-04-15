/*
	循环冗余校验  Cyclic reduandancy check(CRC)

	题意：给一字符串，求CRC。   题意挺难读懂的，我是看题解的。

	思路：我只想记录一下实现上的问题：
		  "
		  我们一般写程序和编译的机器环境（包括OJ系统运行的环境）都是x86架构的，也就意味着字节序是little-endian， 即在存储器中的所有整型数值都是高位在前低位在后。比如32位16进制数：AF045Bh，在内存中的顺序应该是：

		  5B 04 AF 00

		  如果我们直接将字符串的指针转为int型指针进行计算就会算错。必须先对每一组字节（整型变量大小的一组）先进行反转再作运算。
		  "
		  一开始我是直接反转到unsigned int数组里面，但这样做是错的，错因归于我还是不理解little-endian。必须得先反转到char数组，然后再转为int，反转可以直接reverse_copy。还要注意要copy过去以后，因为是char->unsigned int，字节由1->4，我们要把末尾后一位赋为0，直接a[len] = 0有可能会错，还是那个问题，a是char*，字长1字节，我们计算的时候是用unsigned int的4字节扫，所以得应该要*((unsigned int*)(&a[len])) = 0，或者用我的笨办法，直接把后面几位都赋为0，更安全memset(a+len, 0, sizeof(unsigned int))


		  要求输出两位16进制，直接printf("%02X");
	参考资料：http://zh.wikipedia.org/zh-cn/%E5%BE%AA%E7%92%B0%E5%86%97%E9%A4%98%E6%A0%A1%E9%A9%97
		      http://www.cnblogs.com/devymex/archive/2010/08/28/1810480.html
*/
//uva 128
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>
#include <algorithm>
using namespace std;
#define		MOD			34943
typedef 	long long ll;
string str;
char a[2048];
int main()
{
	while(getline( cin, str ), str != "#") {
		int len = str.length();
		reverse_copy(str.begin(), str.end(), a);		//NB

		//a[len] = '\0';
		//*((unsigned int *)(&a[len])) = 0;
		memset(a+len, 0, sizeof(unsigned int));


		unsigned int * p = (unsigned int *)a;
		len = len / 4 + (len % 4 != 0);

		ll rmder = 0;
		for(int i = len-1; i >= 0; i--) 
			rmder = ((rmder << 32) + p[i]) % MOD;
		int ans = 0; 
		if(rmder) ans = (int) (MOD - (rmder << 16) % MOD);
		printf("%02X %02X\n", ans >> 8, ans % (1<<8));
	}
	return 0;
}
