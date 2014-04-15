/*
	概率论  三门问题  好题   （Monty Hall problem）亦称为蒙提霍尔问题、蒙特霍问题或蒙提霍尔悖论
	
	题意：参赛者会看见三扇关闭了的门，其中一扇的后面有一辆汽车，选中后面有车的那扇门可赢得该汽车，另外两扇门后面则各藏有一只山羊。当参赛者选定了一扇门，但未去开启它的时候，节目主持人开启剩下两扇门的其中一扇，露出其中一只山羊。主持人其后会问参赛者要不要换另一扇仍然关上的门。问题是：换另一扇门会否增加参赛者赢得汽车的概率？

		  现在题目变成了：给你NCOWS只牛，NCARS辆车，NSHOW扇开启的门（ NSHOW < NCOWS） 问：换门后赢得车的概率是？


	思路：题目明确要求“是换门后赢车”的概率，不是“赢车”的概率
		  分类讨论，设A = {最开始选的那扇门是山羊}，B = {第二次选的门后是车}
		  由全概率公式得 P(B) = P(A)P(B|A) + P(A')P(B|A') , A'表A的补

	http://blog.csdn.net/synapse7/article/details/9771107
*/
#include <stdio.h>

int main()
{
	double cow, car, show;
	while(scanf("%lf %lf %lf", &cow, &car, &show) != EOF) {
		double N = cow + car;
		double ans = (N - 1) * car / (N * (N - show - 1));
		printf("%.5f\n", ans);
	}
	return 0;
}
