#include <stdio.h>

__declspec(dllimport) double sub(double a, double b);

int main(){
    double result=sub(3.0,2.0);
    printf("result = %f\n",result);
    return 0;
}