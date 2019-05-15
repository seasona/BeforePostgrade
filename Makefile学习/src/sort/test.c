#include "sort.h"
#include <stdio.h>

int main(){
    int data[]={10,34,56,678,324,11};
    QuickSort(data,0,5);
    for(int i=0;i<=5;i++){
        printf("%d ",data[i]);
    }
    printf("\n");
    return 0;
}