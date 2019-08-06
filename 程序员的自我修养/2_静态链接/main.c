#include "test.h"

// void weak_func(void) { printf("custom strong func override!\n"); }

int main() {
    g();
    weak_func();
    return 0;
}