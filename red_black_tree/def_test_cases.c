#include "def_rubro_negra.h"
#include "def_test_cases.h"
#include <sys/time.h>
void heavyTest_rb(int num_nos, int* ops_ins, int* ops_rem) {
    srand(time(NULL));
    Arvore *arv = criar();
    int dados_inseridos[num_nos]; 
    
    for (int i = 0; i < num_nos; i++) {
        int valor = rand() % (int)(1e9);  
        dados_inseridos[i] = valor;    
        insert(arv, valor, ops_ins);           
    }
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
    // printf("\nQuantidade de nos removidos: %i nos\n", k);
    // printf("\nArvore nula: %i\n", arv->nulo==arv->raiz);
    
    // Libera a memória alocada
    free(arv->raiz);
    free(arv->nulo);
    free(arv);
    free(dados_inseridos);
    
}