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

#endif
