#include "def_test_cases.h"
#include <stdio.h>

int main() {
    
    printf("\nTestes\n");
    // test_case_rse();
    // test_case_rsd();
    // test_case_rde();
    // test_case_rdd();
    int at = time(NULL);
    heavyTest((int)5e5);
    printf("ACABOU, durou %i\n", at-time(NULL));
    return 0;
}