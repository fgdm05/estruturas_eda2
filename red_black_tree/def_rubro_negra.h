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
} Arvore;

No* criarNo(Arvore*, No*, int);
void balancear(Arvore*, No*);
void rotacionarEsquerda(Arvore*, No*);
void rotacionarDireita(Arvore*, No*);

Arvore* criar();
int vazia(Arvore*);
No* adicionar(Arvore*, int);
No* localizar(Arvore* arvore, int valor);

#endif