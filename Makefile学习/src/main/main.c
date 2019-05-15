#include "sort.h"
#include "max.h"
#include <stdio.h>

int main(){
    int arr[]={34,334,656,1,3,78};
    QuickSort(arr,0,5);
    for(int i=0;i<=5;i++){
        printf("%d ",arr[i]);
    }
    printf("\n%d\n",FindMax(arr,6));
    return 0;
}