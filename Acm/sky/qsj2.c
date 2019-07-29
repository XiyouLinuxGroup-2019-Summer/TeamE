#include <stdio.h>
#include <stdlib.h>

#define MAX 4100
int a[MAX], b[MAX], c[MAX], d[MAX],m[MAX*MAX], n[MAX*MAX];
 
int cmp ( const void *a , const void *b ) 
{ 
  return *(int *)a - *(int *)b; 
}

int up_down( int *num,  int l, int r, int key )
{
    int mid;

    while ( l < r ) {
        mid = (l+r)/2;
        if ( num[mid] + key >= 0 )
            r = mid;
        else
            l = mid+1;
    }
    if ( (num[l] + key) == 0 )
        return l;
    else
        return -1;
}

int main()
{
    int N, i, j, k, e, f, ans;
    scanf("%d", &N);

    for ( i = 0; i < N; i++ ) {
        scanf("%d %d %d %d", &a[i], &b[i], &c[i], &d[i]);
    }

    k = 0;
    for ( i = 0; i < N; i++ ) {
        for ( j = 0; j < N; j++ ) {
            m[k] = a[i]+b[j];
            n[k++] = c[i]+d[j];
        }
    }

    qsort(m, k, sizeof(int), cmp);

    ans = 0;
    for ( i = 0; i < k; i++ ) {
        e = up_down(m,0,k-1,n[i]);
        if ( e != -1 ) {
            ans++;
            f = e+1;
            for(int j = e+1;j<N;j++)
            {
                if(m[j] == m[e])
                {
                    ans++;
                }
                else break;
            }
        }
    }
    
    printf("%d\n", ans);

}
