//#include "test.h"

// static void __attribute__((weakref("test"))) weak_func();

/**
 * @brief 如果是使用weak，则必须是外部函数，不能为static
 *
 */
__attribute__((weak)) void weak_func() {
    printf("default weak func is running!\n");
}


__attribute__((weak)) void weak_func2() {
    printf("default weak func is running!\n");
}


int f(){

    weak_func();
}

int g(){

     printf("default g is running!\n");
}