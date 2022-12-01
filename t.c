#include<stdio.h>

int main(){
    int a[3]= {0,1,2};
    int *p = (int *)0;
    *p = 0;
    printf("%d", *p);
}