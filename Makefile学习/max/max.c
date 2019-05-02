#include "max.h"

int FindMax(int *arr,int num){
    QuickSort(arr,0,num-1);
    return arr[num-1];
}