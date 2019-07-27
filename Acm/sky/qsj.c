#include <stdio.h>
#include <string.h>

char a[200000], b[200000];

int main()
{
    int t, n, k, left, right, mid, i, m, ans, l;

    scanf("%d", &t);
    while ( t-- ) {
        
        scanf("%d %d", &n, &k);
        scanf("%s", a);
        right = n;
        left = 1;
        ans = 0;

        while ( left < right ) {
            strcpy(b, a);
            mid = (left+right)/2;
            i = l = 0;
            while ( b[i] == '0' ) {
                i++;
            }
            for ( ; i < n;   ) {
                if ( b[i] == '0' ) {
                    i++;
                    continue;
                }
                m = mid;
                while ( m-- ) {
                    b[i] = '0';
                    i++;
                }
                printf("%s\n", b);
                l++;
            }
            if ( l <= k ) {
                right = mid;
                ans = mid;
            }
            else
                left = mid+1;
        }
        
        printf("%d\n", ans);

    }

    return 0;
}
