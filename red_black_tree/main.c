#include "def_rubro_negra.h"
#include "percorrer_lib.h"
#include <stdio.h>

void visitar(int valor){
    printf("%d ", valor);
}

void dfs(No* raiz, No* nulo) {
	if(raiz != nulo) {
		printf("%d ", raiz->valor);
		dfs(raiz->esquerda, nulo);
		dfs(raiz->direita, nulo);
	}
}
#include <time.h>
#include <stdlib.h>
void heavy_test(int n) {
    int at = time(NULL);

    Arvore* a0 = criar();
    int v[n];
    srand(time(NULL));
    for(int i = 0; i < n; i++) {
        v[i] = rand() % ((int)1e9);
        adicionar(a0, v[i]);
    }

    printf("\nACABOU, durou %i\n", time(NULL)-at);

}

int main() {

    heavy_test((int)5e5);


    // Arvore* a = criar();
    // No* nulo = a->nulo;
    
    // adicionar(a,7);
    // adicionar(a,6);
    // adicionar(a,5);
    // adicionar(a,4);
    // adicionar(a,3);
    // adicionar(a,2);
    // adicionar(a,1);

    // dfs(a->raiz, nulo);

    // // printf("In-order: ");
    // // percorrerProfundidadeInOrder(a, a->raiz,visitar);
    // // printf("\n");
}