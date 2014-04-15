#include<stdio.h>  
#include<string.h>  
#include<algorithm>  
using namespace std ;  
  
const int maxn = 55555 ;  
struct Ans  
{  
    int l , r , ans ;  
} p[maxn] ;  
  
int c[maxn] , pre[maxn] ;  
  
int lowbit ( int x ) { return x & ( -x ) ; }  
  
void update ( int pos , int v )  
{  
    while ( pos > 0 )  
    {  
        c[pos] = max ( c[pos] , v ) ;  
        pos -= lowbit ( pos ) ;  
    }  
}  
  
int query ( int pos )  
{  
    int ret = 0 ;  
    while ( pos < maxn - 10 )  
    {  
        ret = max ( ret , c[pos] ) ;  
        pos += lowbit ( pos ) ;  
    }  
    return ret ;  
}  
  
bool cmp ( int i , int j )  
{  
    return p[i].r < p[j].r ;  
}  
int pos[maxn] , num[maxn] ;  
  
int main ()  
{  
    int cas , n , i , j , m ;  
    scanf ( "%d" , &cas ) ;  
    while ( cas -- )  
    {  
        memset ( c , 0 , sizeof ( c ) ) ;  
        memset ( pre , 0 , sizeof ( pre ) ) ;  
        scanf ( "%d" , &n ) ;  
        for ( i = 1 ; i <= n ; i ++ ) scanf ( "%d" , &num[i] ) ;  
        scanf ( "%d" , &m ) ;  
        for ( i = 1 ; i <= m ; i ++ )  
        {  
            scanf ( "%d%d" , &p[i].l , &p[i].r ) ;  
            pos[i] = i ;  
        }  
        sort ( pos + 1 , pos + m + 1 , cmp ) ;  
        int tot = 1 ;  
        for ( i = 1 ; i <= n ; i ++ )  
        {  
            if ( tot > m ) break ;  
            for ( j = 1 ; j * j <= num[i] ; j ++ )  
            {  
                if ( num[i] % j ) continue ;  
                if ( pre[j] != 0 ) update ( pre[j] , j ) ;  
                pre[j] = i ;  
                if ( j * j == num[i] ) continue ;  
                int k = num[i] / j ;  
                if ( pre[k] != 0 ) update ( pre[k] , k ) ;  
                pre[k] = i ;  
            }  
            while ( tot <= m && p[pos[tot]].r == i )  
            {  
                p[pos[tot]].ans = query ( p[pos[tot]].l ) ;  
                tot ++ ;  
            }  
        }  
        for ( i = 1 ; i <= m ; i ++ )  
        {  
            if ( p[i].l == p[i].r )  
            {  
                puts ( "0" ) ;  
                continue ;  
            }  
            printf ( "%d\n" , p[i].ans ) ;  
        }  
    }  
} 
