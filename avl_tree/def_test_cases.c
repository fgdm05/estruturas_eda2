#include "def_test_cases.h"

void heavyTest(int n, int* ops_ins, int* ops_rem){
    srand(time(NULL));
    AVL *a0 = criarAVL();
    int v[n];

    for(int i = 0; i < n; i++){
        v[i] = rand() % ((int)1e9);
        adicionar(a0,v[i], ops_ins);
    }
    int h_insert = altura(a0->raiz);
    for(int i = 0; a0->raiz != NULL; i++){
        int j = rand()%n;
        remover(a0,v[j], ops_rem);
    }
    // printf("\nAltura depois do insert: %i\n",h_insert);
    // printf("\nAltura depois do delete: %i\n",altura(a0->raiz));
    // printf("\nArvore vazia: %i\n", a0->raiz==NULL);
    clear(a0);
    free(v);
    return;
}