#include <stdio.h>

//结构体直接p就行，就能全显示
typedef struct node{
    int a;
    char b;
}node;

//backtrace,frame
int LookStack(int a,int b){
    int c=a*b;
    return c;
}

int main(){
    int a=1;
    int b=2;
    int c=0;
    c=a+b;
    printf("c=%d\n",c);

    int d=LookStack(a,b);

    node tmp;
    tmp.a=10;
    tmp.b='c';

    int *p=&a;
    
    return 0;
}