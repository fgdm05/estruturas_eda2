#include "def_rubro_negra.h"
#include "def_test_cases.h"
#include <sys/time.h>
void heavyTest_rb(int num_nos, double* t_insert, double* t_remove, int* ops_ins, int* ops_rem) {
    srand(time(NULL));
    Arvore *arv = criar();
    int dados_inseridos[num_nos]; 
    
    struct timespec s0, s1, s2;
    clock_gettime(CLOCK_MONOTONIC, &s0);
    for (int i = 0; i < num_nos; i++) {
        int valor = rand() % (int)(1e9);  
        dados_inseridos[i] = valor;    
        insert(arv, valor, ops_ins);           
    }
    clock_gettime(CLOCK_MONOTONIC, &s1);
    int k=0;
    for (int i = 0; arv->nulo!=arv->raiz; i++) {
        int index = rand() % num_nos;          // Seleciona aleatoriamente um índice do vetor
        int valor = dados_inseridos[index];     // Obtém o valor correspondente ao índice
        No *no = localizar(arv, arv->raiz, valor);
        if (no != arv->nulo) {
            k++;
            deletarNo(arv, no, ops_rem);  // Remove o nó encontrado
        }
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
    (*t_insert) = dif3;
    (*t_remove) = dif4;
    // printf("\nTempo para insercao: %lf (ms)", dif3 * 1000.0);
    // printf("\nTempo para remocao: %lf (ms)", dif4 * 1000.0);
    // printf("\nQuantidade de nos removidos: %i nos\n", k);
    // printf("\nArvore nula: %i\n", arv->nulo==arv->raiz);
    
    // Libera a memória alocada
    free(arv->raiz);
    free(arv->nulo);
    free(arv);
    free(dados_inseridos);
    
}