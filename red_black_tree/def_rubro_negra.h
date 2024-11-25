#ifndef DEF_RUBRO_NEGRA
#define DEF_RUBRO_NEGRA

#include <stdlib.h>
#include <stdio.h>

typedef enum { Vermelho, Preto } Cor;

typedef struct No {
    int valor;
    Cor cor;
    struct No *esquerda, *direita, *pai;
} No;

typedef struct Arvore {
    No *raiz;
    No *nulo;
} Arvore;

Arvore* criar();
void insert(Arvore *arv, int valor, int*);
void deletarNo(Arvore *arv, No *z, int*);
No *localizar(Arvore *arv, No *no, int valor);
#endif