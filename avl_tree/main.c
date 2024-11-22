#include "def_test_cases.h"
#include <stdio.h>

int main() {
    
    printf("\nTestes\n");
    // test_case_rse();
    // test_case_rsd();
    // test_case_rde();
    // test_case_rdd();
    int at = (int)time(NULL);
    heavyTest((int)1e6);
    printf("ACABOU, durou %i\n", (int)time(NULL)-at);
    return 0;
}