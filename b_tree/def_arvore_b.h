#ifndef DEF_ARVORE_B
#define DEF_ARVORE_B

#include <stdlib.h>

typedef struct no {
	int total;
	int* chaves;
	struct no** filhos;
	struct no* pai;
} No;

typedef struct arvoreB {
	No* raiz;
	int ordem;
} ArvoreB;

ArvoreB* criaArvore(int ordem);

#endif