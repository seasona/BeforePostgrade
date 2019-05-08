#include "sort.h"

void QuickSort(int *arr, int left, int right){
    if(left>=right) return;
    int l=left;
    int r=right;
    int key=arr[l];
    while(l<r){
        while(l<r&&arr[r]>=key){
            r--;
        }
        arr[l]=arr[r];
        while(l<r&&arr[l]<=key){
            l++;
        }
        arr[r]=arr[l];
    }
    arr[l]=key;
    QuickSort(arr,left,l-1);
    QuickSort(arr,l+1,right);
}
