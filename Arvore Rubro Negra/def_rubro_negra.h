#ifndef DEF_RUBRO_NEGRA
#define DEF_RUBRO_NEGRA

enum coloracao { Vermelho, Preto };
typedef enum coloracao Cor;

typedef struct no {
	struct no* esquerda;
	struct no* direita;
	struct no* pai;
	Cor cor;
	int valor;
} No;

typedef struct rubro_negra {
	No* raiz;
	No* nulo;
} Rubro_Negra;

#endif
