/*
	博弈 简单 SG

	自己懒得写，以下摘自http://blog.csdn.net/liwen_7/article/details/7948305 
	题意：

	从当前日期，在他/她转的玩家可以移动到下一个历日或下月的同一天。当在之后的一个月中没有在同一天，播放器只能移动到下一个的日历日期。例如，从1924年12月19日，你可以移动到1924年12月20日，下一个日期，或一月19日，1925年，在同一天在下个月。然而，2001年1月31日，你可以只移动2001年2月1日，因为2001年2月31日是无效的。一个球员赢得比赛时，他/她到底到达的日期2001年11月4日。如果一个玩家移动到日期2001年11月4号之后，他/她输了比赛。

	思路:

	(2001 , 11 , 4)是个必败点，能到(2001, 11 , 4)的是必胜点，由时间从后向前推。

	最后若输入的sg[] = 0即为必败点，输出 NO
*/
//hdu 1079
#include <string.h>
#include <stdio.h>
int sg[2010][14][33];

bool leap_year(int yy)
{
	if(yy % 400 == 0) return true;
	else if(yy % 100 == 0) return false;
	else return yy % 4 == 0;
}
int calc_by_month(int yy, int mm)
{
	if(mm == 2) {
		return leap_year(yy)? 29 : 28;
	} else if(mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12) {
		return 31;
	} else return 30;
}
bool check(int &yy, int &mm, int &dd)
{
	if(dd > calc_by_month(yy, mm)) dd = 1, mm++;
	if(mm > 12) mm = 1, yy++;
	return true;
}
int SG(int yy, int mm, int dd)
{
	if(yy > 2001) return 1;
	if(yy == 2001 && mm > 11) return 1;
	if(yy >= 2001 && mm >= 11 && dd > 4) return 1;
	if(yy == 2001 && mm == 11 && dd == 4) return 0;

	if(sg[yy][mm][dd] != -1) return sg[yy][mm][dd];
	bool vis[5];			//	其实只要2就行了
	memset(vis, false, sizeof(vis));
	int ty = yy, tm = mm, td = dd;
	dd++;
	if(check(yy, mm, dd)) vis[SG(yy, mm, dd)] = true;

	yy = ty, mm = tm, dd = td;
	mm++;
	if(mm == 13) mm = 1, yy++;						//这部分没考虑到WA了好多次 
	if(dd <= calc_by_month(yy, mm)) {
		if(check(yy, mm, dd)) vis[SG(yy, mm, dd)] = true;
	}

	for(int i = 0; ; i++) {
	//	if(i >= 4) printf("on!\n");
		if(!vis[i]) return sg[ty][tm][td] = i;
	}
}
int main()
{
	int cases, yy, mm, dd;
	scanf("%d", &cases);
	memset(sg, -1, sizeof(sg));
	while(cases--) {
		scanf("%d%d%d", &yy, &mm, &dd);
		if(yy > 2001 || (yy == 2001 && mm > 11) || (yy == 2001 && mm == 11 && dd >= 4)) {puts("NO"); continue; }	//特判
		check(yy, mm, dd);
		puts(SG(yy, mm, dd) ? "YES" : "NO");
	}
	return 0;
}
