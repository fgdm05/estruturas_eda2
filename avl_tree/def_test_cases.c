#include "def_test_cases.h"

void heavyTest(int n, double* t_insert, double* t_delete, int* ops_ins, int* ops_rem){
    srand(time(NULL));
    AVL *a0 = criarAVL();
    int v[n];

    struct timespec s0, s1, s2;
    clock_gettime(CLOCK_MONOTONIC, &s0);

    for(int i = 0; i < n; i++){
        v[i] = rand() % ((int)1e9);
        adicionar(a0,v[i], ops_ins);
    }
    // t2 = clock();
    clock_gettime(CLOCK_MONOTONIC, &s1);
    int h_insert = altura(a0->raiz);
    
    for(int i = 0; a0->raiz != NULL; i++){
        int j = rand()%n;
        remover(a0,v[j], ops_rem);
    }
    clock_gettime(CLOCK_MONOTONIC, &s2);

    double dif3 = 
    (s1.tv_sec - s0.tv_sec) * 1e9;
    dif3 = dif3 + (s1.tv_nsec - s0.tv_nsec) * 1e-9;
    double dif4 =
    (s2.tv_sec - s1.tv_sec) * 1e9;
    dif4 = dif4 + (s2.tv_nsec - s1.tv_nsec) * 1e-9;

    dif3 *= 1000.0;
    dif4 *= 1000.0;

    *t_insert = dif3;
    *t_delete = dif4;
    // printf("\nTempo de insert: %lf (ms)", dif3 * 1000.0);
    // printf("\nTempo de delete: %lf (ms)", dif4 * 1000.0);
    // printf("\nAltura depois do insert: %i\n",h_insert);
    // printf("\nAltura depois do delete: %i\n",altura(a0->raiz));
    // printf("\nArvore vazia: %i\n", a0->raiz==NULL);
    clear(a0);
    free(v);
    return;
}