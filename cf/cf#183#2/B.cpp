#include <stdio.h>
#include <map>
#include <iostream>
using namespace std;


bool is_leap(int year) {
    if (year % 100 == 0) 
        return year % 400 == 0;
    else return year % 4 == 0;
}
void swap(int * a, int * b) {
    int tmp ;
    tmp = *a;
    *a = *b;
    *b = tmp;
}
int year[2];
int month[2];
int day[2];
map<int, int> month_days;
void init() {
    month_days[1]   =   31;
    month_days[2]   =   28;
    month_days[3]   =   31;
    month_days[4]   =   30;
    month_days[5]   =   31;
    month_days[6]   =   30;
    month_days[7]   =   31;
    month_days[8]   =   31;
    month_days[9]   =   30;
    month_days[10]  =   31;
    month_days[11]  =   30;
    month_days[12]  =   31;
}
int main()
{
    init();
    scanf("%d:%d:%d", &year[0], &month[0], &day[0]);
    scanf("%d:%d:%d", &year[1], &month[1], &day[1]);
    if((year[0] > year[1]) 
    || (year[0] == year[1] && month[0] > month[1]) 
    || (year[0] == year[1] && month[0] == month[1] && day[0] > day[1])) {
        swap( year+0, year+1 );
        swap(month+0, month+1);
        swap(  day+0, day+1  );
    }

    long long ans = 0;
    for(int i = 1; i < month[1]; i++) ans += month_days[i];
    ans += (month[1] > 2) && is_leap(year[1]);
    for(int i = 1; i < month[0]; i++) ans -= month_days[i];
    ans -= (month[0] > 2) && is_leap(year[0]);
    ans = ans + day[1] - day[0];

    ans += (year[1] - year[0]) * 365;
    for(int i = year[0]; i < year[1]; i++)
        ans += is_leap(i);

    cout << ans << endl;
    return 0;
}
