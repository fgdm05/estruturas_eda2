#include "def_test_cases.h"
#include <stdio.h>
#include <sys/timeb.h>

int main() {
    
    printf("\nTestes\n");
    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    heavyTest((int)1e4);
    clock_gettime(CLOCK_MONOTONIC, &t1);

    double dif = (t1.tv_sec - t0.tv_sec) *1e9;
    dif = dif + (t1.tv_nsec - t0.tv_nsec) *1e-9;

    printf("ACABOU, durou %lf\n", dif * 1000.0);
    return 0;
}