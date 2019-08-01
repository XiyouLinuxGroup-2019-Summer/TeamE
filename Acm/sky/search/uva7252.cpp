#include <cstdio>
#include <memory.h>
using namespace std;
int a[15];        //存储每个数字出现的次数 

bool check(int c,int d){
    memset(a,0,sizeof(a));
    //判断是不是大于5位数
    if(d > 98765) return false;
    //判断是否出现过重复
    for(int i = 0;i < 5;i++){       //需要循环5次,判断每一位 
        a[c % 10]++;a[d % 10]++;
        c /= 10;d /= 10;
    }

    for(int i = 0;i < 10;i++){
        if(a[i] != 1) return false;
    }
    return true;
}

int main(void){
    int n,kase = 0;
    while(scanf("%d",&n) == 1 && n){
        if(kase++ > 0) printf("\n");

        bool flag = false;
        for(int i = 1234;i < 99999;i++){
            if(check(i,n * i)){
                printf("%05d / %05d = %d\n",n*i,i,n);
                flag = true;
            }
        }

        if(flag == false){
            printf("There are no solutions for %d.\n",n);
        }
    }   
    return 0;
}
