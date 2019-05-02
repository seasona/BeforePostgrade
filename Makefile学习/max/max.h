#ifndef _MAX_H_
#define _MAX_H_

//直接编译需要指定头文件目录
#include "../sort/sort.h"

//如果调用gcc -c max.c -I ../sort就不用在文件中指定头文件目录
//#include "sort.h"

int FindMax(int *arr,int num);

#endif 