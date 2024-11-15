#include "def_rubro_negra.h"
#include "percorrer_lib.h"
#include <stdio.h>

void visitar(int valor){
    printf("%d ", valor);
}

int main() {
    Arvore* a = criar();

    adicionar(a,7);
    adicionar(a,6);
    adicionar(a,5);
    adicionar(a,4);
    adicionar(a,3);
    adicionar(a,2);
    adicionar(a,1);

    printf("In-order: ");
    percorrerProfundidadeInOrder(a, a->raiz,visitar);
    printf("\n");
}