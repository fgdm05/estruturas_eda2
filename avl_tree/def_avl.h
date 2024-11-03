#ifndef DEF_AVL
#define DEF_AVL

typedef struct no {
	struct no* esquerda;
	struct no* direita;
	struct no* pai;
	int valor;
} No;

typedef struct avl {
	No* raiz;
} AVL;

#include <stdlib.h>

AVL* criar();
No* criarNo(No* pai, int valor);
void adicionarNo(AVL* avl, int valor);

#endif
