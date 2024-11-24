#include <time.h>
#include <sys/timeb.h>
#include "def_rubro_negra.h"
#include "def_test_cases.h"
// Programa principal

int main() {
    printf("\nComecando Rubro Negra");
    int num_nos = (int)1e4;
    heavyTest(num_nos);
    return 0;
}